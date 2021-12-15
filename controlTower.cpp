


#include "controlTower.h"


class FakeTrain : Train
{

    public:
    void setTrainRoute(std::vector<unsigned int> trainRouteToSet)
    {
        trainRoute = trainRouteToSet; // TODO use move to do this to get
    }

    FakeTrain(unsigned int ID)
    {
        
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




        TrainCommunication * ControlTower::GetRouteAndSignals(unsigned int startingTrainTrackID)
        {
            return nullptr;
        }

