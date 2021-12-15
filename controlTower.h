#ifndef CONTROLTOWER_H
#define CONTROLTOWER_H


#include "boost_1_77_0/boost/signals2.hpp"
#include "trainTrack.h"
#include "train.h"
#include <vector>

struct TrainCommunication
{
boost::signals2::signal<void (std::string)> A;
boost::signals2::signal<void (std::string)> B;

};

class ControlTower
{
    public:
        static TrainCommunication * GetRouteAndSignals(unsigned int startingTrainTrackID);
        
    private:
        std::vector<TrainCommunication> trainSignals; // These should be saved in a container of type std::set
        std::vector<std::vector<unsigned int>> trainRoutes;
        std::vector<TrainTrack*> trainTracks;

};


#endif /* CONTROLTOWER_H */