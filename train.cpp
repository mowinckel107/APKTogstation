#include "train.h"
#include "common.h"
#include <iostream>
#include <mutex>
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

        if (first_round)
        {
            // Feed trainTracker to control tower
            TrainTracker trainTracker;

            trainTracker.isTrainTrackOccupiedSignal_ = &isTrainTrackOccupiedSignal_;

            // Prepare to enter first track
            TrainCommunicationAndRoute ctOutput = (*control_)(currentTrackID, ID_, &trainFunctor_, trainTracker);

            // Clear reservation on our functor. We haven't entered a track yet.
            trainFunctor_();

            // Get our route from control tower
            route_ = ctOutput.route_;
        }

        TrainTrack * trackThatWeAreTryingToEnter;
        int trackThatWeAreTryingToEnterID;

        // Now we wait.       
        isNextTrainTrackOccupied = true;
        while (isNextTrainTrackOccupied)
        {
            if (first_round)
            {
                // Track that we are trying to enter
                trackThatWeAreTryingToEnter = currentTrack_;
                trackThatWeAreTryingToEnterID = currentTrackID;
            }
            else
            {                   
                // Make sure that we still have tracks
                if (route_.size() < 1)
                {
                    std::cout << "ERROR: No more tracks for Train " << ID_ << std::endl;
                    throw "";
                }

                // Track that we are trying to enter
                trackThatWeAreTryingToEnterID = route_.at(0);
                trackThatWeAreTryingToEnter = currentTrack_->GetNextTrainTrack(trackThatWeAreTryingToEnterID);
            }

            // Make sure that our signals are up to date
            try
            {
                (*control_)(ID_, 0); // 0 = checking
            }
            catch (...)
            {
                std::cout << "ERROR: (*control_)(ID_, 0);" << std::endl;
                return 0;
            }

            // Try to get permission
            try
            {    
                isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(trackThatWeAreTryingToEnterID);
            }
            catch (...)
            {
                std::cout << "ERROR: isNextTrainTrackOccupied = isTrainTrackOccupiedSignal_(trackThatWeAreTryingToEnterID);" << std::endl;
                return 0;
            }

            // Action !
            if (!isNextTrainTrackOccupied)
            {
                if (!first_round)
                {
                    // Tell our own functor that we're leaving
                    try
                    {
                        trainFunctor_();
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: trainFunctor_();" << std::endl;
                        return 0;
                    }

                    // Tell control tower that we're leaving. This may update our signal
                    try
                    {      
                        (*control_)(ID_, 1); // 1 = entering
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: (*control_)(ID_, 1);" << std::endl;
                        return 0;
                    }
                    
                    // Tell track that we're leaving
                    try
                    {                
                        currentTrack_->LeaveTrainTrack();
                    }
                    catch (...)
                    {
                        std::cout << "ERROR: trackThatWeAreTryingToEnter->LeaveTrainTrack();" << std::endl;
                        return 0;
                    }

                }

                // Reserve new track
                try
                {
                    trainFunctor_(trackThatWeAreTryingToEnterID);
                }
                catch (...)
                {
                    std::cout << "ERROR: trainFunctor_(trackThatWeAreTryingToEnterID);" << std::endl;
                    return 0;
                }

                // Tell track we're entering
                // Train may get deleted here if TrainTrack is a TrainInput
                try
                {
                    if (trackThatWeAreTryingToEnter->EnterTrainTracks(this))
                    {      
                        std::cout << "Train " << ID_ << " has entered Track " << trackThatWeAreTryingToEnterID << std::endl;
                    }

                }
                catch (...)
                {
                    std::cout << "ERROR: Train " << ID_ << " tried to swim in lava." << std::endl;
                    throw "";
                }

                currentTrack_ = trackThatWeAreTryingToEnter;

                // Tell control tower that we have entered. This will update our signal
                try
                {      
                    (*control_)(ID_, 2); // 2 = entering
                }
                catch (...)
                {
                    std::cout << "ERROR: (*control_)(ID_, 2);" << std::endl;
                    return 0;
                }

                // Remove our now current track from route
                try
                {
                    route_.erase(route_.begin());
                }
                catch (...)
                {
                    std::cout << "ERROR: route_.erase(route_.begin());" << std::endl;
                    return 0;                        
                }

                if (first_round)
                {
                    first_round = false;
                }

                break;
            }
            
            // Take a break
            ulock.unlock();

            t.expires_after(boost::asio::chrono::milliseconds(100));
            t.wait();

            ulock.lock();
        }

        ulock.unlock();
    }
    
    trainFunctor_();
    std::cout << "Train " << ID_ << " was blown up, but don't worry, that is how things are supposed to be." << std::endl;
    return 0;
}

int Train::getID(void)
{
    return ID_;
}