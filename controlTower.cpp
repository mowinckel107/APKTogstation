#include "controlTower.h"


class FakeTrain : Train
{

    public:
    void setTrainRoute(std::vector<unsigned int> trainRouteToSet)
    {
        trainRoute = trainRouteToSet; // TODO use move to do this to get
    }


    void LeavingTrainTrack()
    {
        ControlTower::GetRouteAndSignals(2);
    }

    void WantToEnterTrainTrack()
    {

    }


    private:
    std::vector<unsigned int> trainRoute;
    boost::signals2::signal<void (std::string)> leavingTrainTrackSignal;
    boost::signals2::signal<bool (std::string)> wantToEnterTrainTrackSignal;
};


ControlTower::ControlTower()
{
    std::vector<unsigned int> route10 {0,0,0,0};
    trainRouteForTrainOutput1.push_back(route10);

    std::vector<unsigned int> route11 {0,0,1,0};
    trainRouteForTrainOutput1.push_back(route11);

    std::vector<unsigned int> route12 {0,0,1,1};
    trainRouteForTrainOutput1.push_back(route12);


    std::vector<unsigned int> route20 {1,0,1,1};
    trainRouteForTrainOutput2.push_back(route20);

    std::vector<unsigned int> route21 {0,0,0};
    trainRouteForTrainOutput2.push_back(route21);

    std::vector<unsigned int> route22 {1,0,0,0};
    trainRouteForTrainOutput2.push_back(route22);


    std::vector<unsigned int> route30 {0,1,0};
    trainRouteForTrainOutput3.push_back(route30);

    std::vector<unsigned int> route31 {0,1,1};
    trainRouteForTrainOutput3.push_back(route31);

    std::vector<unsigned int> route32 {0,0,1,1};
    trainRouteForTrainOutput3.push_back(route32);
}

TrainCommunication * ControlTower::GetRouteAndSignals(unsigned int startingTrainTrackID)
{
    return nullptr;
}

