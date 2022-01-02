#ifndef CONTROLTOWERFUNCTOR_H
#define CONTROLTOWERFUNCTOR_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include "trainTrack.h"
#include "train.h"
#include "trainFunctor.h"
#include <vector>
#include <map>

using RouteVector = std::vector<std::vector<int>>;

struct TrainCommunicationAndRoute
{
    boost::signals2::signal<void (int)> leavingSignal_;
    boost::signals2::signal<bool (int)> isTrainTrackOccupiedSignal_;
    boost::signals2::signal<void (trackConnectionMap)> birthSignal_;
    trainTrackConnectionMap trainTrackConnections_;
    std::vector<int> route_;
};

struct TrainTracker
{
    boost::signals2::signal<void (int)> * leavingSignal_;
    boost::signals2::signal<bool (int)> * isTrainTrackOccupiedSignal_;
}

class ControlTowerFunctor
{
    public:
        ControlTowerFunctor(bool managerMode);

        TrainCommunicationAndRoute operator()(int startingTrainTrackID, int TrainID, TrainFunctor * newTrainFunctor);
        void operator()(int TrainTrackID, int TrainID);
        
    private:
        bool managerMode_;
        std::map<int, TrainTracker> trainTrackers_; // references to train signals for use in manager mode
        std::map<int, TrainFunctor *> trainFunctors_; // train functors by train
        std::map<int, std::vector<int>> trainRoutes_; // Train routes by train.
        std::map<int, std::vector<int>> trackTrains_; // Train by track (on a train route). Basically the opposite of trainRoutes_
        std::map<int, RouteVector> routes_;
};

#endif /* CONTROLTOWERFUNCTOR_H */