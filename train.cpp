#include "train.h"
#include "common.h"
#include <iostream>
#include <mutex>
#include <string>
#include <functional>

Train::Train
(
    int ID,
    TrainTrack * startingTrack,
    ControlTowerFunctor * control,
    std::mutex * inmut
)
{
    inmut_ = inmut;
    ID_ = ID;
    control_ = control;

    trainFunctor_ = TrainFunctor(ID_);
    currentTrack_ = startingTrack;
}

Train::~Train()
{
    isNotDeleted_ = false;
}

int Train::startDriveLoop()
{
    std::cout << "Train " << ID_ << " has been boomed into existence. Say hi! " << std::endl;

    boost::asio::io_context io;
    boost::asio::steady_timer t(io);

    bool first_round = true;

    std::unique_lock<std::mutex> ulock(*inmut_, std::defer_lock);

    // Drive loop
    while(isNotDeleted_)
    {
        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        ulock.lock();

        // Get current track ID
        int currentTrackID = currentTrack_->GetID();

        // Occupied flag
        bool isNextTrainTrackOccupied;

        // Prepare to start drive loop
        if (first_round)        
        {
            // Feed trainTracker to control tower
            TrainTracker trainTracker;

            trainTracker.isTrainTrackOccupiedSignal_ = &isTrainTrackOccupiedSignal_;

            TrainCommunicationAndRoute ctOutput = (*control_)(currentTrack_->GetID(), ID_, &trainFunctor_, trainTracker);

            // Signals
            isTrainTrackOccupiedSignal_ = std::move(ctOutput.isTrainTrackOccupiedSignal_);

            // Functor
            trainFunctor_(); // Clear reservation

            // Route
            route_ = ctOutput.route_;

            // Now we wait.
            isNextTrainTrackOccupied = true;
            while (isNextTrainTrackOccupied)
            {
                try
                {    
                    isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(currentTrackID);
                }
                catch (...)
                {
                    std::cout << "ERROR: isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(currentTrackID);" << std::endl;
                    return 0;
                }

                if (!isNextTrainTrackOccupied)
                {
                    std::cout << "Train " << ID_ << " has been allowed to drive into first track " << currentTrackID << ". Reserving." << std::endl;

                    try
                    {
                        // Reserve new track                
                        trainFunctor_(currentTrackID);
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: trainFunctor_(nextTrackID);" << std::endl;
                        return 0;
                    }

                    if (trainFunctor_(true, currentTrackID))
                    {
                        std::cout << "Train " << ID_ << " has reserved track " << currentTrackID << std::endl;
                    }

                    try
                    {
                        // Tell track we're entering
                        // Train may get deleted here if TrainTrack is a TrainInput
                        if (currentTrack_->EnterTrainTracks(this))
                        {      
                            std::cout << "Train " << ID_ << " has entered Track " << currentTrack_->GetID() << std::endl;
                        }
                    }
                    catch (std::string err)
                    {
                        std::cout << "ERROR: " << err << std::endl;
                        std::cout << "Train " << ID_ << " tried to swim in lava." << std::endl;
                        return 0;
                    }

                    try
                    {
                        // Remove original track from list
                        route_.erase(route_.begin());
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: route_.erase(route_.begin());" << std::endl;
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
        if (route_.size() > 0)
        {
            nextTrackID = route_.at(0);
        }
        else
        {
            nextTrackID = 0;            
        }

        TrainTrack * nextTrack = currentTrack_->GetNextTrainTrack(nextTrackID);

        if (route_.size() > 0)
        {
            route_.erase(route_.begin());
        }
        
        // Wait for permission
        isNextTrainTrackOccupied = true;
        while(true)
        {
            try
            {    
                isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(nextTrackID);
            }
            catch (...)
            {
                std::cout << "ERROR: isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(nextTrackID);" << std::endl;
                return 0;
            }

            if (!isNextTrainTrackOccupied)
            {
                try
                {                
                    // Tell track we're leaving
                    currentTrack_->LeaveTrainTrack();
                    std::cout << "Train " << ID_ << " left track " << currentTrackID << std::endl;
                }
                catch (...)
                {
                    std::cout << "ERROR: currentTrack_->LeaveTrainTrack();" << std::endl;
                    return 0;
                }

                try
                {
                    // Tell our own functor that we're leaving
                    trainFunctor_();
                }
                catch (...)
                {
                    std::cout << "ERROR: trainFunctor_();" << std::endl;
                    return 0;
                }        

                try
                {
                    // Reserve new track                
                    trainFunctor_(nextTrackID);
                }
                catch (...)
                {
                    std::cout << "ERROR: trainFunctor_(nextTrackID);" << std::endl;
                    return 0;
                }

                try
                {      
                    // Tell control tower we're leaving and entering a new track
                    (*control_)(ID_);
                }
                catch (...)
                {
                    std::cout << "ERROR: (*control_)(ID_);" << std::endl;
                    return 0;
                }  
                
                try
                {
                    // Tell track we're entering
                    // Train may get deleted here if TrainTrack is a TrainInput
                    if (!nextTrack->EnterTrainTracks(this))
                    {
                        std::cout << "Train " << ID_ << " has reached its final destination and was blown up by a Creeper. What a cruel fate." << std::endl;
                    }
                    else
                    {      
                        std::cout << "Train " << ID_ << " has entered Track " << nextTrack->GetID() << std::endl;
                        currentTrack_ = nextTrack;
                    }
                }
                catch (std::string err)
                {
                    std::cout << "ERROR: " << err << std::endl;
                    std::cout << "Train " << ID_ << " tried to swim in lava." << std::endl;
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