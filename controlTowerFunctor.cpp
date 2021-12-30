#include "controlTowerFunctor.h"

ControlTowerFunctor::ControlTowerFunctor(bool managerMode)
{
    // Creating 3 routes for all 3 starting positions
    // 1
    RouteVector trainRouteForTrainOutput0;

    std::vector<unsigned int> route10 {10,12,20,30};
    trainRouteForTrainOutput0.push_back(route10);

    std::vector<unsigned int> route11 {10,12,21,30};
    trainRouteForTrainOutput0.push_back(route11);

    std::vector<unsigned int> route12 {10,12,21,31};
    trainRouteForTrainOutput0.push_back(route12);

    // 2
    RouteVector trainRouteForTrainOutput1

    std::vector<unsigned int> route20 {10,12,21,31};
    trainRouteForTrainOutput1.push_back(route20);

    std::vector<unsigned int> route21 {11,21,30};
    trainRouteForTrainOutput1.push_back(route21);

    std::vector<unsigned int> route22 {11,12,20,31};
    trainRouteForTrainOutput1.push_back(route22);

    // 3
    RouteVector trainRouteForTrainOutput2;

    std::vector<unsigned int> route30 {11,21,31};
    trainRouteForTrainOutput2.push_back(route30);

    std::vector<unsigned int> route31 {11,21,30};
    trainRouteForTrainOutput2.push_back(route31);

    std::vector<unsigned int> route32 {11,12,20,30};
    trainRouteForTrainOutput2.push_back(route32);  

    // Insert into map
    routes_.insert(std::make_pair(0, trainRouteForTrainOutput0));
    routes_.insert(std::make_pair(1, trainRouteForTrainOutput1));
    routes_.insert(std::make_pair(2, trainRouteForTrainOutput2));
}

TrainCommunicationAndRoute ControlTowerFunctor::operator()(unsigned int startingTrainTrackID, int TrainID)
{
    // this is GetRouteAndSignals()
    
}

void ControlTowerFunctor::operator()(unsigned int TrainTrackID, int TrainID, bool direction)
{
    // this is UpdateTrainCommunicationLeave and UpdateTrainCommunicationEnter in one, with some new features.

}