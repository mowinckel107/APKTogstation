#include "train.h"

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

void Train::StartDriveLoop(void)
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io);

    // Prepare to start drive loop
        TrainTracker trainTracker;
        trainTracker.leavingSignal_ = &leavingSignal_;
        trainTracker.isTrainTrackOccupiedSignal_ = &isTrainTrackOccupiedSignal_;

        TrainCommunicationAndRoute ctOutput = (*control_)(currentTrack_->GetID(), ID_, &trainFunctor_, trainTracker);

        // Signals
        leavingSignal_ = std::move(ctOutput.leavingSignal_);
        isTrainTrackOccupiedSignal_ = std::move(ctOutput.isTrainTrackOccupiedSignal_);
        birthSignal_ = std::move(ctOutput.birthSignal_);

        // Functor
        trainFunctor_(); // Clear train ID
        trainFunctor_(std::move(ctOutput.trainTrackConnections_)); // Configure connection map

    // Drive loop
    while(isNotDeleted_)
    {   
        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        // Get current track ID
        int currentTrackID = currentTrack_->GetID();

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
        route_.erase(route_.begin());       

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

        // Tell track we're leaving
        currentTrack_->LeaveTrainTrack();

        // Tell relevant trains that we're leaving
        leavingSignal_(currentTrackID);

        // Tell control tower we're leaving and entering a new track
        (*control_)(currentTrackID, ID_);

        // Tell track we're entering
        // Train may get deleted here if TrainTrack is a TrainInput
        if (!nextTrack->EnterTrainTracks(this) || !isNotDeleted_)
        {
            break;
        }
        currentTrack_ = nextTrack;
    }
}

int Train::GetID(void)
{
    return ID_;
}