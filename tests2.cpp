#include "tests2.h"

#include "controlTowerFunctor.h"
#include "train.h"
#include <iostream>


void TestsOfCT1(void);
void TestsOfTrain1(void);
void TestOfTrack1(void);
void TestsOfTrain2(void);
void TestsOfCT2(void);

void RunTests2()
{   
    TestsOfCT1();

    TestsOfTrain1();

    TestOfTrack1();

    TestsOfTrain2();
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

// Test GetRouteAndSignals together with one train
void TestsOfCT2(void)
{
    ControlTowerFunctor Tower(false);

    std::cout << "TestsOfCT2 passed" << std::endl;
}


