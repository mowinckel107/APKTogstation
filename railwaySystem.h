#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H


#include "trainTrack.h"
#include <map>
#include <vector>

class RailwaySystem
{
    public:
    RailwaySystem(void);

    std::vector<TrainTrack> trainTracks;
    std::vector<Platform> platforms;
    std::vector<TrainInput> trainInputs;
    std::vector<TrainOutput> trainOutputs;
};



#endif /* RAILWAYSYSTEM_H */