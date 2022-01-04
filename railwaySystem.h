#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H


#include "trainTrack.h"
#include "common.h"
#include <map>
#include <vector>
#include <array>

class RailwaySystem
{
    public:
    RailwaySystem(void);

    TrainTrack track1_;
    TrainTrack track2_;
    TrainTrack track3_;
    Platform platform1_;
    Platform platform2_;
    TrainOutput output1_;
    TrainOutput output2_;
    TrainOutput output3_;    
    TrainInput input1_;
    TrainInput input2_;

};



#endif /* RAILWAYSYSTEM_H */