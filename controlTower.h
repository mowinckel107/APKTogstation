#ifndef CONTROLTOWER_H
#define CONTROLTOWER_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include "trainTrack.h"
#include "train.h"
#include <vector>
#include <map>

struct TrainCommunicationAndRoute
{
    boost::signals2::signal<void ()> * leavingSignal;
    boost::signals2::signal<bool ()> * isTrainTrackOccupiedSignal;
    std::vector<unsigned int> route;
};

class ControlTower
{
    public:
        ControlTower();
        TrainCommunicationAndRoute operator()(unsigned int startingTrainTrackID, int TrainID);
        
    private:
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput0;
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput1;
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput2;

        std::map<int, TrainFunctor> trainFunctors;
};



#endif /* CONTROLTOWER_H */