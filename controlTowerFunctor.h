#ifndef CONTROLTOWERFUNCTOR_H
#define CONTROLTOWERFUNCTOR_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include "trainTrack.h"
#include "train.h"
#include "trainFunctor.h"
#include <vector>
#include <map>

using RouteVector = std::vector<std::vector<unsigned int>>;

struct TrainCommunicationAndRoute
{
    boost::signals2::signal<void ()> * leavingSignal_;
    boost::signals2::signal<bool ()> * isTrainTrackOccupiedSignal_;
    trainTrackConnectionMap * trainTrackConnections_;
    std::vector<unsigned int> route_;
};

class ControlTowerFunctor
{
    public:
        ControlTowerFunctor();

        TrainCommunicationAndRoute operator()(unsigned int startingTrainTrackID, int TrainID);
        void operator()(unsigned int TrainTrackID, int TrainID, bool leaveMode);
        
    private:
        std::map<int, TrainFunctor> trainFunctors_; // train functors by train
        std::map<int, std::vector<int>> trainRoutes_; // Train routes by train
        std::map<int, RouteVector> routes_; 
};

#endif /* CONTROLTOWERFUNCTOR_H */