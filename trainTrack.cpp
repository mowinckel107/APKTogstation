#include "trainTrack.h"

TrainTrack::TrainTrack(std::map<int, TrainTrack*> outgoingTraintracks, int uniqueTrainTrackID)
{
    connectedTraintracks = outgoingTraintracks;
    ID = uniqueTrainTrackID;
}

TrainTrack* TrainTrack::GetNextTrainTrack(int trainTrackNumber)
{
    std::map<int, TrainTrack*>::iterator myIterator = connectedTraintracks.begin();



    while(myIterator != connectedTraintracks.end())
    {
        if(myIterator->first == trainTrackNumber)
        {
            return myIterator->second;
        }
        myIterator++;
    }
    // If Train asked for a TrainTrack that did not exist
    throw "A Train derailed";
}



bool TrainTrack::EnterTrainTracks(Train* IncomingTrain)
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
    return true;
}

void TrainTrack::LeaveTrainTrack(void)
{
    TrainOnTrack = nullptr;
}

int TrainTrack::GetID(void)
{
    return ID;
}



bool TrainInput::EnterTrainTracks(Train* IncomingTrain)
{
    delete IncomingTrain;
    return false;
}





