#ifndef TRAINFUNCTOR_H
#define TRAINFUNCTOR_H

#include <map>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>

using vectorOfConnections = std::vector<boost::signals2::connection>;

// int being the ID of a track. Every track related connection on every train driving through this track.
using trackConnectionMap = std::map<int, vectorOfConnections>;

// int being the ID of a train (for sorting)
using trainTrackConnectionMap = std::map<int, trackConnectionMap>;

class TrainFunctor
{

private:
	int reservedID_ = 0;
    int ownerTrainID_ = 0;

    // 1) train, 2) track, 3) connections
    trainTrackConnectionMap trainTrackConnections_;

public:

    // Setup
    TrainFunctor(int ownerTrainID);

    // Clear reservation
    void operator()();

    // Reserve track {trackID}
    void operator()(int trackID);

    // Train {trainID} has left track {trackID}
    void operator()(int trainID, int trackID);

    // Some train is requesting track {TrackID}
    bool operator()(bool isRequest, int trackID);

    // We belong to a new train and we need to be fed with a list of how everyone else is connected to us
    void operator()(trainTrackConnectionMap trainTrackConnections);

    // A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.
    void operator()(int newTrainID, trackConnectionMap trackConnection);

};

#endif /* TRAINFUNCTOR_H */