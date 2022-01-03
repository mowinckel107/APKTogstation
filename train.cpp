#include "train.h"

#include <iostream>

Train::Train
(
    int ID,
    TrainTrack * startingTrack,
    ControlTowerFunctor * control
)
{
    ID_ = ID;
    currentTrack_ = startingTrack;
    control_ = control;
    TrainFunctor trainFunctor_(ID_);
}

Train::~Train()
{
    isNotDeleted_ = false;
}

void Train::start(void)
{
    std::thread t1(&Train::startDriveLoop, this);
    t1.join();
}

void Train::startDriveLoop(void)
{
    std::cout << "test1" << std::endl;

    boost::asio::io_context io;
    boost::asio::steady_timer t(io);

    std::cout << "test2" << std::endl;

    // Prepare to start drive loop
        TrainTracker trainTracker;
        std::cout << "test21" << std::endl;

        trainTracker.leavingSignal_ = &leavingSignal_;

        std::cout << "test22" << std::endl;

        trainTracker.isTrainTrackOccupiedSignal_ = &isTrainTrackOccupiedSignal_;

        std::cout << "test23" << std::endl;

        TrainCommunicationAndRoute ctOutput = (*control_)(currentTrack_->GetID(), ID_, &trainFunctor_, trainTracker);

        std::cout << "test3" << std::endl;

        // Signals
        leavingSignal_ = std::move(ctOutput.leavingSignal_);
        isTrainTrackOccupiedSignal_ = std::move(ctOutput.isTrainTrackOccupiedSignal_);
        birthSignal_ = std::move(ctOutput.birthSignal_);

        std::cout << "test4" << std::endl;

        // Functor
        trainFunctor_(); // Clear train ID
        trainFunctor_(std::move(ctOutput.trainTrackConnections_)); // Configure connection map

        std::cout << "test5" << std::endl;

        // Route
        route_ = std::move(ctOutput.route_);

    // Drive loop
    while(isNotDeleted_)
    {   
        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        std::cout << "test6" << std::endl;

        // Get current track ID
        int currentTrackID = currentTrack_->GetID();

        std::cout << "test7" << std::endl;

        // Get next track
        int nextTrackID;
        if (route_.size() > 0)
        {
            std::cout << "route size > 0 " << std::endl;
            nextTrackID = route_.at(0);
        }
        else
        {
            std::cout << "route size 0 " << std::endl;
            nextTrackID = 0;            
        }

        std::cout << "test8" << std::endl;

        TrainTrack * nextTrack = currentTrack_->GetNextTrainTrack(nextTrackID);
        route_.erase(route_.begin());       

        std::cout << "test9" << std::endl;

        // Wait for permission
        bool isNextTrainTrackOccupied = true;
        while(isNextTrainTrackOccupied)
        {
            if (isTrainTrackOccupiedSignal_(nextTrackID))
            {
                t.expires_after(boost::asio::chrono::milliseconds(100));
                t.wait();
            }
            else
            {
                isNextTrainTrackOccupied = false;
            }
        }

        std::cout << "test100" << std::endl;

        // Tell track we're leaving
        currentTrack_->LeaveTrainTrack();

        std::cout << "test110" << std::endl;

        // Tell relevant trains that we're leaving
        leavingSignal_(currentTrackID);

        std::cout << "test120" << std::endl;

        // Tell control tower we're leaving and entering a new track
        (*control_)(ID_);

        std::cout << "test130" << std::endl;

        // Tell track we're entering
        // Train may get deleted here if TrainTrack is a TrainInput
        if (!nextTrack->EnterTrainTracks(this) || !isNotDeleted_)
        {
            std::cout << "train: train was destroyed by input" << std::endl;
            break;
        }
        
        std::cout << "train: remaining route: " << route_.size() << std::endl;
        currentTrack_ = nextTrack;
    }
}

int Train::getID(void)
{
    return ID_;
}