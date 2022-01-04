#include "tests2.h"
#include "common.h"
#include "controlTowerFunctor.h"
#include "train.h"
#include "railwaySystem.h"
#include <iostream>
#include <thread>

void trainFunc(Train &myTrain)
{
    myTrain.startDriveLoop();
}


void TestsOfCT1(void);
void TestsOfTrain1(void);
void TestOfTrack1(void);
void TestsOfTrain2(void);
void TestOfSystem1(void);
void TestOfThreading1(void);
void TestOfThreading2(void);

void RunTests2()
{   
    TestsOfCT1();

    TestsOfTrain1();

    TestOfTrack1();

    TestsOfTrain2();

    TestOfSystem1();

    TestOfThreading1();

    //TestOfThreading2();
}

// Does constructor run?
void TestsOfCT1(void)
{
    ControlTowerFunctor Tower;
    std::cout << "TestsOfCT1 passed: Does constructor run?" << std::endl;
}

// Does constructor run with nullptr track?
void TestsOfTrain1(void)
{
    ControlTowerFunctor Tower;
    std::mutex mut;
    Train train1(0, nullptr, &Tower, &mut);
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

    ControlTowerFunctor Tower;
    std::mutex mut;
    Train train½(0, &tt1, &Tower, &mut);
    std::cout << "TestsOfTrain2 passed: Does constructor run with a real track?" << std::endl;
}

// Crashtest of railway system constructor
void TestOfSystem1(void)
{
    // Tower
    ControlTowerFunctor Tower;

    // Railway system
    RailwaySystem system;

    // Get the first output track
    TrainOutput * tto1p = &(system.output1_);

    // Train
    std::mutex mut;
    Train train1(0, tto1p, &Tower, &mut);

    // Success?
    std::cout << "TestOfSystem1 passed: Crashtest of railway system constructor" << std::endl;
}

// Test threading as well as GetRouteAndSignals and startDriveLoop together with one train
void TestOfThreading1(void)
{
    // Tower
    ControlTowerFunctor Tower;

    // Railway system
    RailwaySystem system;

    // Get the first output track
    TrainOutput * tto1p = &(system.output1_);

    // Train
    std::mutex mut;
    Train train1(0, tto1p, &Tower, &mut);

     // Thread
    std::thread t1(trainFunc, std::ref(train1));
    t1.join();

    // Success?
    std::cout << "TestOfThreading1 passed: Test threading as well as GetRouteAndSignals together with one train" << std::endl;
}

// Test threading as well as GetRouteAndSignals and startDriveLoop together with one train
void TestOfThreading2(void)
{
    std::mutex mut;

    // Tower
    ControlTowerFunctor Tower;

    // Railway system
    RailwaySystem system;

    // Get three output tracks
    TrainOutput * tto1p0 = &(system.output1_);
    TrainOutput * tto1p1 = &(system.output2_);
    TrainOutput * tto1p2 = &(system.output3_);

    // Train
    Train train9(9, tto1p0, &Tower, &mut);
    Train train1(1, tto1p1, &Tower, &mut);
    Train train2(2, tto1p2, &Tower, &mut);
    Train train3(3, tto1p0, &Tower, &mut);
    Train train4(4, tto1p1, &Tower, &mut);
    Train train5(5, tto1p2, &Tower, &mut);
    Train train6(6, tto1p0, &Tower, &mut);
    Train train7(7, tto1p1, &Tower, &mut);
    Train train8(8, tto1p2, &Tower, &mut);

    // Thread
    std::thread t9(trainFunc, std::ref(train9));
    std::thread t1(trainFunc, std::ref(train1));
    std::thread t2(trainFunc, std::ref(train2));
    std::thread t3(trainFunc, std::ref(train3));
    std::thread t4(trainFunc, std::ref(train4));
    std::thread t5(trainFunc, std::ref(train5));
    std::thread t6(trainFunc, std::ref(train6));
    std::thread t7(trainFunc, std::ref(train7));
    std::thread t8(trainFunc, std::ref(train8));

    // Join
    t9.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    // Success?
    std::cout << "TestOfThreading1 passed: Test threading as well as GetRouteAndSignals together with one train" << std::endl;
}



