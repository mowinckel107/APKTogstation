#include "train.h"

Train::Train
(
    int ID,
    std::vector<int> route,
    TrainTrack * startingTrack,
    ControlTowerFunctor * control
)
{
    ID_ = ID;
    route_ = route;
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

    TrainTrack * nextTrack;
    int nextTrackID = 0;
    int currentTrackID = currentTrack_->GetID();

    while(isNotDeleted_)
    {   
        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        // We need a route
        if (route_.size() > 0)
        {
            nextTrackID = route_.at(0);
        }

        nextTrack = currentTrack_->GetNextTrainTrack(nextTrackID);
        route_.erase(route_.begin());       

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