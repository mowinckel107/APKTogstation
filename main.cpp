
#include "trainTrack.h"
#include "train.h"
#include "controlTowerFunctor.h"
#include "railwaySystem.h"
#include "common.h"
#include "cargo.h"
#include "container.h"

#include <vector>
#include <iostream>
#include <string>

void trainFunc(Train &myTrain)
{
    myTrain.startDriveLoop();
}

/*
struct NineTrains
{
    Train train1_;
    Train train2_;
    Train train3_;
    Train train4_;
    Train train5_;
    Train train6_;
    Train train7_;
    Train train8_;
    Train train9_;
    std::vector<Train *> trains_;
    std::vector<std::thread> threads_;

    NineTrains()
    {
        trains_.push_back(&train1_);
        trains_.push_back(&train2_);
        trains_.push_back(&train3_);
        trains_.push_back(&train4_);
        trains_.push_back(&train5_);
        trains_.push_back(&train6_);
        trains_.push_back(&train7_);
        trains_.push_back(&train8_);
        trains_.push_back(&train9_);
    }
};
*/

int main()
{



// Retired code that didn't work for whatever reason
/*
    // Create mutex for trains to use
    std::mutex mut;

    // Create control tower
    ControlTowerFunctor ct;

    // Create a railway system
    RailwaySystem rs;

    // Somewhere for the trains to go
    NineTrains nineTrains;

    //Create trains
    int trainCounter = 1;

    std::for_each(rs.outputs_.begin(), rs.outputs_.end(), [&](TrainOutput * o){
        for (int i = 0; i < 3; i++)
        {
            *(nineTrains.trains_.at(trainCounter) - 1) = Train(trainCounter, *o, &ct, &mut);
            trainCounter++;
        }
    });


    // Create threads and join
    for (auto train : nineTrains.trains_)
    {
        nineTrains.threads_.push_back(std::thread(TrainFunc, std::ref(*train)));
    }

    for (auto th : nineTrains.threads_)
    {
        th.join();
    }    

    */

    // Container showcase
    Container<cold, liquid> water("water");

    std::cout << "What is in this new container?" << std::endl;
    std::cout << water.seeCargo() << std::endl;

    water.removeCargo();

    std::cout << "What is in this container now that we removed cargo?" << std::endl;
    std::cout << water.seeCargo() << std::endl;

    water.addCargo("water");

    std::cout << "What is in this container now that added water again?" << std::endl;
    std::cout << water.seeCargo() << std::endl;


    // Thread showcase
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

    return 0;
}







