#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H


#include "trainTrack.h"
#include "common.h"
#include "cargo.h"
#include <vector>
#include <string>

class RailwaySystem
{
    public:
    RailwaySystem(void);

    // Tracks
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

    // Vectors
    std::vector<TrainOutput *> outputs_;

    // Cargo
    /*
    Cargo<frozen, solid> material1("Ice.");

    Cargo<temperate, liquid> material2(... "Chocolate too close to the window");
    Cargo<temperate, gas> material3(... "11 different symbols on the peridic table");
    Cargo<temperate, solid> material4(... "Olaf");

    Cargo<cold, solid> material5(... "Honey");
    Cargo<cold, gas> material6(... "Oxygen");
    Cargo<cold, liquid> material7(... "Salt water");
    */
};



#endif /* RAILWAYSYSTEM_H */