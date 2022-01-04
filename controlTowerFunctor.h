#ifndef CONTROLTOWERFUNCTOR_H
#define CONTROLTOWERFUNCTOR_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include "train.h"
#include "trainFunctor.h"
#include "common.h"
#include <vector>
#include <map>
#include <thread>
#include <mutex>

// compiler seems to be weird with circular includes
class Train;

class ControlTowerFunctor
{
    public:
        ControlTowerFunctor();

        TrainCommunicationAndRoute operator()(int startingTrainTrackID, int TrainID, TrainFunctor * newTrainFunctor, TrainTracker trainTracker);
        void operator()(int TrainI, int direction);
        
    private:
        std::mutex mut_;
        std::map<int, TrainTracker> trainTrackers_; // references to train signals for use in manager mode
        std::map<int, TrainFunctor *> trainFunctors_; // train functors by train
        std::map<int, std::vector<int>> trainRoutes_; // Train routes by train.
        std::map<int, std::vector<int>> trackTrains_; // Train by track (on a train route). Basically the opposite of trainRoutes_
        std::map<int, RouteVector> routes_;
};

#endif /* CONTROLTOWERFUNCTOR_H */