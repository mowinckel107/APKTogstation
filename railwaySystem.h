#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H


#include "trainTrack.h"
#include <map>
#include <vector>
#include <array>

class RailwaySystem
{
    public:
    RailwaySystem(void);

    std::array<TrainTrack,30> trainTracks;
    std::array<Platform,30> platforms;
    std::array<TrainInput,30> trainInputs;
    std::array<TrainOutput,30> trainOutputs;
};



#endif /* RAILWAYSYSTEM_H */