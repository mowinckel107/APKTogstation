#ifndef CONTROLTOWER_H
#define CONTROLTOWER_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include "trainTrack.h"
#include "train.h"
#include <vector>
#include <map>

class TrainSignalFunctor;

struct TrainCommunicationAndRoute
{
    boost::signals2::signal<void ()> * leavingSignal;
    boost::signals2::signal<bool ()> * isTrainTrackOccupiedSignal;
    std::vector<unsigned int> route;
};

struct TrainTracker
{
    boost::signals2::signal<void ()> leavingSignal;
    boost::signals2::signal<bool ()> isTrainTrackOccupiedSignal;
    int howFarAlongRoute = 0;
    std::vector<unsigned int> route;

};


class ControlTower
{
    public:
        ControlTower();
        TrainCommunicationAndRoute GetRouteAndSignals(unsigned int startingTrainTrackID, int TrainID);
        void UpdateTrainCommunicationLeave(int trainID);
        void UpdateTrainCommunicationEnter(int trainID);
        
    private:
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput0;
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput1;
        std::vector<std::vector<unsigned int>> trainRouteForTrainOutput2;

        std::map<int, TrainTracker> trainTrackers;
        std::map<int, TrainSignalFunctor> trainSignalFunctors;

};



#endif /* CONTROLTOWER_H */