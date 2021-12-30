#include "trainFunctor.h"

// Setup
TrainFunctor::TrainFunctor(int ownerTrainID)
{
    ownerTrainID_ = ownerTrainID;
}

// Clear reservation
bool TrainFunctor::operator()()
{
    reservedID_ = 0;
}

// Reserve track {trackID}
bool TrainFunctor::operator()(int trackID)
{
    reservedID_ = trackID;
}

// Train {trainID} has left track {trackID}
bool TrainFunctor::operator()(int trackID, int trainID)
{
    std::map<int, vectorOfSignals> foundTrains = trainTrackConnections_.find(trainID);
    vectorOfSignals foundTracks = foundTrains.find(trackID);

    for (auto elem : foundTracks)
    {
        elem.disconnect(this);
    }
}

// Some train is requesting track {TrackID}
bool TrainFunctor::operator()(bool isRequest, int trackID)
{
    // I am currently sitting on this ID
    if (reservedID_ == trackID)
    {
        return false;
    }
    // I am not in the way
    else
    {
        return true;
    }
}

// We belong to a new train and we need to be fed with a list of how everyone else is connected to us
bool TrainFunctor::operator()(trainTrackConnectionMap trainTrackConnections)
{
    trainTrackConnections_ = trainTrackConnections;
}

// A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.
bool TrainFunctor::operator()(int newTrainID, trackConnectionMap trackConnection)
{
    trainTrackConnections_.insert ( std::pair<int, trackConnectionMap>(newTrainID, trackConnection) );
}
