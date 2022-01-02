#include "train.h"



Train::Train
(
    int ID,
    std::vector<int> route,
    TrainTrack * startingTrack
    ControlTowerFunctor * control
)
{
    ID_ = ID;
    route_ = route;
    currentTrack_ = startingTrack;
    control_ = control;

}

Train::~Train()
{
    isNotDeleted = false;
}
    

void Train::StartDriveLoop(void)
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io);
    TrainTrack* nextTrainTrack;

    while(isNotDeleted)
    {

        // Delay
        t.expires_after(boost::asio::chrono::seconds(1));
        t.wait();

        CurrentTrack_ = CurrentTrack_->GetNextTrainTrack(route_);
        route_.erase(route_.begin());

        bool isNextTrainTrackOccupied = true;
        while(isNextTrainTrackOccupied)
        {
            if (isTrainTrackOccupiedSignal_())
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
        CurrentTrack->LeaveTrainTrack();

        // Tell relevant trains that we're leaving
        leavingSignal_();

        // Tell control tower we're leaving and entering a new track
        control_(CurrentTrackID, ID);

        // Tell track we're entering
        // Train may get deleted here if TrainTrack is a TrainInput
        isNotDeleted = CurrentTrack->EnterTrainTracks(this);
    }
}

int Train::GetID(void)
{
    return ID;
}