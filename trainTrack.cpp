#include "trainTrack.h"
#include <iostream>

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
            std::cout << "returned next track: " << myIterator->second->GetID() << " (burde være " << trainTrackNumber << ")" << std::endl;
            return myIterator->second;
        }
        std::cout << "track " << GetID() << " is connected to track " << myIterator->second->GetID() << ", but not the one" << std::endl;
        myIterator++;
    }
    // If Train asked for a TrainTrack that did not exist
    throw "A Train derailed";
}

bool TrainTrack::EnterTrainTracks(Train* IncomingTrain)
{
    std::cout << "foo1" << std::endl;
    // if a train is already on this traintrack
    if(!(TrainOnTrack == nullptr))
    {
        throw "A train crashed into another train";
    }
    else
    {
        std::cout << "foo2" << std::endl;
        TrainOnTrack = IncomingTrain;
        std::cout << "foo3" << std::endl;
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





