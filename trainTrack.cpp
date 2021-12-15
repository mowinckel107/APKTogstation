#include "trainTrack.h"



    TrainTrack::TrainTrack(std::vector<TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID)
    {
        connectedTraintracks = outgoingTraintracks;
        ID = uniqueTrainTrackID;
    }

    TrainTrack* TrainTrack::GetNextTrainTrack(unsigned int trainTrackNumber)
    {
        return connectedTraintracks[trainTrackNumber];
    }

    void TrainTrack::EnterTrainTracks(Train* IncomingTrain)
    {
        // if a train is already on this traintrack
        if(!(TrainOnTrack == nullptr))
        {
            throw "A train crashed into another train";
        }
        else
        {
            TrainOnTrack = IncomingTrain;
        }
    }

    void TrainTrack::LeaveTrainTrack(void)
    {
        TrainOnTrack = nullptr;
    }

    unsigned int TrainTrack::GetID(void)
    {
        return ID;
    }




