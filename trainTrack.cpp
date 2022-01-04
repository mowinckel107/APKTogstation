#include "trainTrack.h"
#include "common.h"
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
            return myIterator->second;
        }
        myIterator++;
    }
    
    std::cout << "Train " << TrainOnTrack->getID() << " derailed while trying to enter Track " <<  trainTrackNumber <<  " from Track " << GetID() << std::endl;
    throw "";
}

bool TrainTrack::EnterTrainTracks(Train* IncomingTrain)
{
    // if a train is already on this traintrack
    if(!(TrainOnTrack == nullptr))
    {
        std::cout << "Train " << TrainOnTrack->getID() << " was crashed into on Track " << GetID() << std::endl;
        throw "";
    }
    else
    {
        TrainOnTrack = IncomingTrain;
        return true;
    }
    return false;
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
    IncomingTrain->isNotDeleted_ = false;
    return false;
}





