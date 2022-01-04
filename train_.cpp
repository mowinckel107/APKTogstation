#include "train.h"
#include "common.h"
#include <iostream>
#include <mutex>
#include <string>

Train::Train
(
    int ID,
    TrainTrack * startingTrack,
    ControlTowerFunctor * control
)
{
    ID_ = ID;
    control_ = control;
    TrainFunctor trainFunctor_(ID_);

    if (trainFunctor_(true, true))
    {
        std::cout << "Train" << ID_ << " constructor: Owner set" << std::endl;
    }

    currentTrack_ = startingTrack;
}

Train::~Train()
{
    isNotDeleted_ = false;
}

std::thread Train::start(std::mutex * inmut)
{
    inmut_ = inmut;
    std::thread t1(&Train::startDriveLoop, this);
    return std::move(t1);
}

int Train::startDriveLoop(Train *dis)
{
    // Stuff that needs dis:
    // trainFunctor_                 (dis->trainFunctor_)
    // ID_                           (dis->ID_)
    // this                          dis
    // inmut_                        (dis->inmut_)
    // isNotDeleted__                 (dis->isNotDeleted)
    // leavingSignal_                (dis->leavingSignal_)
    // isTrainTrackOccupiedSignal_   (dis->isTrainTrackOccupiedSignal_)
    // birthSignal_                  (dis->birthSignal_)
    // currentTrack_                 (dis->currentTrack_)
    // route_                        (dis->route_)
    // control_                      manuel...


    std::cout << "Train " << (dis->ID_) << " has been boomed into existence. Say hi! " << std::endl;

    if (!(dis->trainFunctor_)(true, true))
    {
        std::cout << "Error in TrainFunctor " << (dis->ID_) << " : Owner not set" << std::endl;
        return 0;
    }

    boost::asio::io_context io;
    boost::asio::steady_timer t(io);
    bool first_round = true;

    std::unique_lock<std::mutex> ulock(*(dis->inmut_), std::defer_lock);

    // Drive loop
    while((dis->isNotDeleted_))
    {
        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        ulock.lock();

        // Get current track ID
        int currentTrackID = (dis->currentTrack_)->GetID();

        // Occupied flag
        bool isNextTrainTrackOccupied;

        // Prepare to start drive loop
        if (first_round)        
        {
            // Feed trainTracker to control tower
            TrainTracker trainTracker;

            trainTracker.leavingSignal_ = &(dis->leavingSignal_);
            trainTracker.isTrainTrackOccupiedSignal_ = &(dis->isTrainTrackOccupiedSignal_);

            TrainCommunicationAndRoute ctOutput = (*(dis->control_))((dis->currentTrack_)->GetID(), (dis->ID_), &(dis->trainFunctor_), trainTracker);

            // Signals
            dis->leavingSignal_ = std::move(ctOutput.leavingSignal_);
            dis->isTrainTrackOccupiedSignal_ = std::move(ctOutput.isTrainTrackOccupiedSignal_);
            dis->birthSignal_ = std::move(ctOutput.birthSignal_);

            // Functor
            (dis->trainFunctor_)(); // Clear reservation
            (dis->trainFunctor_)(std::move(ctOutput.trainTrackConnections_)); // Configure connection map

            // Route
            (dis->route_) = ctOutput.route_;

            // Now we wait.
            isNextTrainTrackOccupied = true;
            while (isNextTrainTrackOccupied)
            {
                try
                {    
                    isNextTrainTrackOccupied = (dis->isTrainTrackOccupiedSignal_)(currentTrackID);
                }
                catch (...)
                {
                    std::cout << "ERROR: isNextTrainTrackOccupied = (dis->isTrainTrackOccupiedSignal_)(currentTrackID);" << std::endl;
                    return 0;
                }

                if (!isNextTrainTrackOccupied)
                {
                    std::cout << "Train " << (dis->ID_) << " has been allowed to drive into track " << currentTrackID << ". Reserving." << std::endl;

                    try
                    {
                        // Reserve new track                
                        (dis->trainFunctor_)(currentTrackID);
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: (dis->trainFunctor_)(nextTrackID);" << std::endl;
                        return 0;
                    }

                    std::cout << "Train " << (dis->ID_) << " has reserved track " << currentTrackID << std::endl;

                    try
                    {
                        // Tell track we're entering
                        // Train may get deleted here if TrainTrack is a TrainInput
                        if ((dis->currentTrack_)->EnterTrainTracks(dis))
                        {      
                            std::cout << "Train " << (dis->ID_) << " has entered Track " << (dis->currentTrack_)->GetID() << std::endl;
                        }
                    }
                    catch (std::string err)
                    {
                        std::cout << "xERROR: " << err << std::endl;
                        std::cout << "Train " << (dis->ID_) << " tried to swim in lava." << std::endl;
                        return 0;
                    }

                    try
                    {
                        // Remove original track from list
                        (dis->route_).erase(route_.begin());
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: (dis->route_).erase(route_.begin());" << std::endl;
                        return 0;                        
                    }

                    break;
                }
                
                ulock.unlock();

                t.expires_after(boost::asio::chrono::milliseconds(100));
                t.wait();

                ulock.lock();
            }

            ulock.unlock();
            t.expires_after(boost::asio::chrono::seconds(1));
            t.wait();
            ulock.lock();

            first_round = false;
        }

        // Get next track
        int nextTrackID;
        if ((dis->route_).size() > 0)
        {
            nextTrackID = (dis->route_).at(0);
        }
        else
        {
            nextTrackID = 0;            
        }

        TrainTrack * nextTrack = (dis->currentTrack_)->GetNextTrainTrack(nextTrackID);

        if ((dis->route_).size() > 0)
        {
            (dis->route_).erase((dis->route_).begin());
        }
        
        // Wait for permission
        isNextTrainTrackOccupied = true;
        while(true)
        {
            try
            {    
                isNextTrainTrackOccupied = (dis->isTrainTrackOccupiedSignal_)(nextTrackID);
            }
            catch (...)
            {
                std::cout << "ERROR: isNextTrainTrackOccupied = (dis->isTrainTrackOccupiedSignal_)(nextTrackID);" << std::endl;
                return 0;
            }

            if (!isNextTrainTrackOccupied)
            {
                try
                {                
                    // Tell track we're leaving
                    (dis->currentTrack_)->LeaveTrainTrack();
                    std::cout << "Train " << (dis->ID_) << " left track " << currentTrackID << std::endl;
                }
                catch (...)
                {
                    std::cout << "ERROR: (dis->currentTrack_)->LeaveTrainTrack();" << std::endl;
                    return 0;
                }

                try
                {
                    // Tell our own functor that we're leaving
                    (dis->trainFunctor_)();
                }
                catch (...)
                {
                    std::cout << "ERROR: (dis->trainFunctor_)();" << std::endl;
                    return 0;
                }        

                try
                {      
                    // Tell control tower we're leaving and entering a new track
                    (*(dis->control_))((dis->ID_));
                }
                catch (...)
                {
                    std::cout << "ERROR: (*(dis->control_))((dis->ID_));" << std::endl;
                    return 0;
                }  

                try
                {
                    // Reserve new track                
                    (dis->trainFunctor_)(nextTrackID);
                }
                catch (...)
                {
                    std::cout << "ERROR: (dis->trainFunctor_)(nextTrackID);" << std::endl;
                    return 0;
                }
                
                try
                {
                    // Tell relevant trains that we're leaving
                    // segfaulter ...
                    //(dis->leavingSignal_)(currentTrackID);
                }
                catch (...)
                {
                    std::cout << "ERROR: (dis->leavingSignal_)(currentTrackID);" << std::endl;
                    return 0;
                }

                try
                {
                    // Tell track we're entering
                    // Train may get deleted here if TrainTrack is a TrainInput
                    if (!nextTrack->EnterTrainTracks(dis))
                    {
                        std::cout << "Train " << (dis->ID_) << " has reached its final destination and was blown up by a Creeper. What a cruel fate." << std::endl;
                    }
                    else
                    {      
                        std::cout << "Train " << (dis->ID_) << " has entered Track " << nextTrack->GetID() << std::endl;
                        (dis->currentTrack_) = nextTrack;
                    }
                }
                catch (std::string err)
                {
                    std::cout << "ERROR: " << err << std::endl;
                    std::cout << "Train " << (dis->ID_) << " tried to swim in lava." << std::endl;
                    return 0;
                }                

                break;
            }

            ulock.unlock();

            t.expires_after(boost::asio::chrono::milliseconds(100));
            t.wait();

            ulock.lock();

        }

        ulock.unlock();
    }

    return 1;
}

int Train::getID(void)
{
    return ID_;
}