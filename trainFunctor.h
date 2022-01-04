#ifndef TRAINFUNCTOR_H
#define TRAINFUNCTOR_H

#include <map>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <mutex>
#include "common.h"

class TrainFunctor
{
private:
	int reservedID_ = -1;
    int ownerTrainID_ = -1;

public:
    using result_type = bool;

    // Setup
    TrainFunctor(int ownerTrainID = -1);

    // Clear reservation
    bool operator()();

    // Reserve track {trackID}
    bool operator()(int trackID);

    // Some train is requesting track {TrackID}
    bool operator()(bool isRequest, int trackID);

    // Debugging
    bool operator()(bool a, bool b);

};

#endif /* TRAINFUNCTOR_H */