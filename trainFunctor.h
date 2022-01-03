#ifndef TRAINFUNCTOR_H
#define TRAINFUNCTOR_H

#include <map>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>

using vectorOfConnections = std::vector<boost::signals2::connection>;
using trackConnectionMap = std::map<int, vectorOfConnections>;
using trainTrackConnectionMap = std::map<int, trackConnectionMap>;

class TrainFunctor
{
private:
	int reservedID_ = 0;
    int ownerTrainID_ = 0;

    // 1) train, 2) track, 3) connections
    trainTrackConnectionMap trainTrackConnections_;

public:
    using result_type = bool;

    // Setup
    TrainFunctor(int ownerTrainID = 0);

    // Clear reservation
    bool operator()();

    // Reserve track {trackID}
    bool operator()(int trackID);

    // Train {trainID} has left track {trackID}
    bool operator()(int trainID, int trackID);

    // Some train is requesting track {TrackID}
    bool operator()(bool isRequest, int trackID);

    // We belong to a new train and we need to be fed with a list of how everyone else is connected to us
    bool operator()(trainTrackConnectionMap trainTrackConnections);

    // A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.
    bool operator()(int newTrainID, trackConnectionMap trackConnection);

};

#endif /* TRAINFUNCTOR_H */