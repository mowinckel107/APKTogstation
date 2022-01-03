#include "tests2.h"

#include "controlTowerFunctor.h"
#include "train.h"
#include "railwaySystem.h"
#include <iostream>
#include <thread>


void TestsOfCT1(void);
void TestsOfTrain1(void);
void TestOfTrack1(void);
void TestsOfTrain2(void);
void TestOfSystem1(void);
void TestOfThreading1(void);

void RunTests2()
{   
    TestsOfCT1();

    TestsOfTrain1();

    TestOfTrack1();

    TestsOfTrain2();

    TestOfSystem1();

    TestOfThreading1();    
}

// Does constructor run?
void TestsOfCT1(void)
{
    ControlTowerFunctor Tower(false);
    std::cout << "TestsOfCT1 passed: Does constructor run?" << std::endl;
}

// Does constructor run with nullptr track?
void TestsOfTrain1(void)
{
    ControlTowerFunctor Tower(false);
    Train train1(0, nullptr, &Tower);
    std::cout << "TestsOfTrain1 passed: Does constructor run with nullptr track?" << std::endl;
}

// Does constructor run?
void TestOfTrack1(void)
{
    std::map<int, TrainTrack *> ttm1;
    TrainTrack tt1(ttm1, 0);
    std::cout << "TestOfTrack1 passed: Does constructor run?" << std::endl;
}

// Does constructor run with a real track?
void TestsOfTrain2(void)
{
    std::map<int, TrainTrack *> ttm1;
    TrainTrack tt1(ttm1, 0);

    ControlTowerFunctor Tower(false);
    Train train2(0, &tt1, &Tower);
    std::cout << "TestsOfTrain2 passed: Does constructor run with a real track?" << std::endl;
}

// Crashtest of railway system constructor
void TestOfSystem1(void)
{
    // Tower
    ControlTowerFunctor Tower(false);

    // Railway system
    RailwaySystem system;

    // Get the first output track
    TrainOutput * tto1p = &((system.trainOutputs)[0]);

    // Train
    Train train1(0, tto1p, &Tower);

    // Success?
    std::cout << "TestOfSystem1 passed: Crashtest of railway system constructor" << std::endl;
}


// Test threading as well as GetRouteAndSignals and startDriveLoop together with one train
void TestOfThreading1(void)
{
    // Tower
    ControlTowerFunctor Tower(false);

    // Railway system
    RailwaySystem system;

    // Get the first output track
    TrainOutput * tto1p = &((system.trainOutputs)[0]);

    // Train
    Train train1(0, tto1p, &Tower);

    // Thread
    train1.start();

    // Success?
    std::cout << "TestOfThreading1 passed: Test threading as well as GetRouteAndSignals together with one train" << std::endl;
}


