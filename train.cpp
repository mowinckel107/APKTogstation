#include "train.h"

#include <iostream> 

Train::Train(int InputID, std::vector<int> Route, TrainTrack * startingTrack)
{
    ID = InputID;
    CurrentTrack = startingTrack;
    progressAlongRoute = 0;
    route = Route;
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


        bool isNextTrainTrackOccupied = true;
        while(isNextTrainTrackOccupied)
        {
            // if call to signal2 WantToEnterNextTrain is false TODO
            {
                t.expires_after(boost::asio::chrono::milliseconds(100));
                t.wait();
            }
            //else TODO
            {
                isNextTrainTrackOccupied = false;
            }
        }


        CurrentTrack->LeaveTrainTrack();
        //Call signal2 HaveLeft TODO
        CurrentTrack = CurrentTrack->GetNextTrainTrack(route[progressAlongRoute]);
        progressAlongRoute++;
        CurrentTrack->EnterTrainTracks(this);
    }
}