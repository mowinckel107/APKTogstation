#include "trainFunctor.h"


// Setup
TrainFunctor::TrainFunctor(int ownerTrainID)
{
    ownerTrainID_ = ownerTrainID;
}

// Clear reservation
void TrainFunctor::operator()()
{
    reservedID_ = 0;
}

// Reserve track {trackID}
void TrainFunctor::operator()(int trackID)
{
    reservedID_ = trackID;
}

// Train {trainID} has left track {trackID}
void TrainFunctor::operator()(int trainID, int trackID)
{
    std::map<int, vectorOfConnections> foundTrain = trainTrackConnections_.find(trainID)->second;
    vectorOfConnections foundTrack = foundTrain.find(trackID)->second;

    // If the last link is to be removed, disconnect all remaining connections
    if ((foundTrain.size()) == 1)
    {
        for (auto elem : foundTrack)
        {
            elem.disconnect();
        }
    }

    // The chosen track in relation to train {trainID} does no longer have any links
    foundTrack.clear();
    foundTrain.erase(trackID);
}


// Some train is requesting track {TrackID}
bool TrainFunctor::operator()(bool isRequest, int trackID)
{
    // I am currently sitting on this ID
    if (reservedID_ == trackID)
    {
        return true;
    }
    // I am not in the way
    else
    {
        return false;
    }
}

// We belong to a new train and we need to be fed with a list of how everyone else is connected to us
void TrainFunctor::operator()(trainTrackConnectionMap trainTrackConnections)
{
    trainTrackConnections_ = trainTrackConnections;
}

// A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.
void TrainFunctor::operator()(int newTrainID, trackConnectionMap trackConnection)
{
    trainTrackConnections_.insert ( std::pair<int, trackConnectionMap>(newTrainID, trackConnection) );
}
