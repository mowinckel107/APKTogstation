#include "controlTower.h"


ControlTower::ControlTower()
{
    // Creating 3 routes for all 3 starting positions
    std::vector<unsigned int> route10 {10,12,20,30};
    trainRouteForTrainOutput0.push_back(route10);

    std::vector<unsigned int> route11 {10,12,21,30};
    trainRouteForTrainOutput0.push_back(route11);

    std::vector<unsigned int> route12 {10,12,21,31};
    trainRouteForTrainOutput0.push_back(route12);


    std::vector<unsigned int> route20 {10,12,21,31};
    trainRouteForTrainOutput1.push_back(route20);

    std::vector<unsigned int> route21 {11,21,30};
    trainRouteForTrainOutput1.push_back(route21);

    std::vector<unsigned int> route22 {11,12,20,31};
    trainRouteForTrainOutput1.push_back(route22);


    std::vector<unsigned int> route30 {11,21,31};
    trainRouteForTrainOutput2.push_back(route30);

    std::vector<unsigned int> route31 {11,21,30};
    trainRouteForTrainOutput2.push_back(route31);

    std::vector<unsigned int> route32 {11,12,20,30};
    trainRouteForTrainOutput2.push_back(route32);


    // Creating 10 functors, one for each TrainTrack
    TrainSignalFunctor trainSignal0;
    trainSignalFunctors.insert(std::make_pair(0, trainSignal0));

    TrainSignalFunctor trainSignal1;
    trainSignalFunctors.insert(std::make_pair(1, trainSignal1));

    TrainSignalFunctor trainSignal2;
    trainSignalFunctors.insert(std::make_pair(2, trainSignal2));

    TrainSignalFunctor trainSignal10;
    trainSignalFunctors.insert(std::make_pair(10, trainSignal10));

    TrainSignalFunctor trainSignal11;
    trainSignalFunctors.insert(std::make_pair(11, trainSignal11));

    TrainSignalFunctor trainSignal12;
    trainSignalFunctors.insert(std::make_pair(12, trainSignal12));

    TrainSignalFunctor trainSignal20;
    trainSignalFunctors.insert(std::make_pair(20, trainSignal20));

    TrainSignalFunctor trainSignal21;
    trainSignalFunctors.insert(std::make_pair(21, trainSignal21));

    TrainSignalFunctor trainSignal30;
    trainSignalFunctors.insert(std::make_pair(30, trainSignal30));

    TrainSignalFunctor trainSignal31;
    trainSignalFunctors.insert(std::make_pair(31, trainSignal31));
}

TrainCommunicationAndRoute ControlTower::GetRouteAndSignals(unsigned int startingTrainTrackID, int trainID)
{
    static int routeCounter = 0;
    routeCounter++;
    if (routeCounter == 2)
    {
        routeCounter = 0;
    }

    // We create 2 objects.
    // TrainTracker which will be keept in ControlTower To keep track of Train
    TrainTracker myTrainTracker;
    // TrainCommunicationAndRoute which is the return type for Train.
    TrainCommunicationAndRoute trainCommunicationAndRoute;

    trainCommunicationAndRoute.leavingSignal = &myTrainTracker.leavingSignal;
    trainCommunicationAndRoute.isTrainTrackOccupiedSignal = &myTrainTracker.isTrainTrackOccupiedSignal;


    if(startingTrainTrackID == 0)
    {
        myTrainTracker.route = trainRouteForTrainOutput0[routeCounter];
    }
    else if(startingTrainTrackID == 1)
    {
        myTrainTracker.route = trainRouteForTrainOutput1[routeCounter];
    }
    else if(startingTrainTrackID == 2)
    {
        myTrainTracker.route = trainRouteForTrainOutput2[routeCounter];
    }
        trainCommunicationAndRoute.route = myTrainTracker.route;

    // Saving 
    trainTrackers.insert(std::make_pair(trainID, std::move(myTrainTracker)));

    return trainCommunicationAndRoute;
}

void ControlTower::UpdateTrainCommunicationLeave(int trainID)
{
        std::map<int, TrainTracker>::iterator trainTrackerIterator = trainTrackers.find(trainID);

        // if trainID exists
        if(trainTrackerIterator != trainTrackers.end())
        {   
            // Remove old connection.
            trainTrackerIterator->second.leavingSignal.disconnect_all_slots();

            // Find the new functor via TrainTrackID

            // if the train is leaving the second last TrainTrack, it will be deleted
            if(trainTrackerIterator->second.route.size() == trainTrackerIterator->second.howFarAlongRoute)
            {
                // Delete TrainTracker object now that the related Train object will be deleted
                trainTrackers.erase(trainTrackerIterator);
            }
            // make sure we there is at least 1 more TrainTrack on the route
            else if(trainTrackerIterator->second.route.size() < trainTrackerIterator->second.howFarAlongRoute)
            {
                trainTrackerIterator->second.howFarAlongRoute++;
                // find TrainTrackID for the next TrainTrack
                int TrainTrackID = trainTrackerIterator->second.route[trainTrackerIterator->second.howFarAlongRoute];

                // Find correct functor via TrainTrackID
                std::map<int, TrainSignalFunctor>::iterator trainSignalFunctorIterator = trainSignalFunctors.find(TrainTrackID);

                // if TrainTrackID exists
                if(trainSignalFunctorIterator != trainSignalFunctors.end())
                {
                    // We connect the functor up to the boost:signal, but using boost::bind to fill in the arguments so they are not needed when calling the boost::signal
                    trainTrackerIterator->second.leavingSignal.connect
                    (
                        // note, the return value is not actually used in this signal, but needs to be specificed anyway
                        boost::bind<bool>
                        (
                            trainSignalFunctorIterator->second,false,trainID
                        )
                    );
                }
                else
                {
                    throw "UpdateTrainCommunicationLeave got called with TrainTrackID that could not be found";
                }
            }
        }
        else
        {
            throw "UpdateTrainCommunicationLeave got called with trainID that could not be found";
        }

}


void ControlTower::UpdateTrainCommunicationEnter(int trainID)
{
    std::map<int, TrainTracker>::iterator trainTrackerIterator = trainTrackers.find(trainID);

    // if trainID exists
    if(trainTrackerIterator != trainTrackers.end())
    {   
        // Remove old connection.
        trainTrackerIterator->second.isTrainTrackOccupiedSignal.disconnect_all_slots();

        // Find the new functor via TrainTrackID

        // make sure we there is at least 1 more TrainTrack on the route
        if(trainTrackerIterator->second.route.size() < trainTrackerIterator->second.howFarAlongRoute)
        {  
            // incriment how far along the route the train is
            // find TrainTrackID for the next TrainTrack
            int TrainTrackID = trainTrackerIterator->second.route[trainTrackerIterator->second.howFarAlongRoute+1];

            // Find correct functor via TrainTrackID
            std::map<int, TrainSignalFunctor>::iterator trainSignalFunctorIterator = trainSignalFunctors.find(TrainTrackID);

            // if TrainTrackID exists
            if(trainSignalFunctorIterator != trainSignalFunctors.end())
            {
                // We connect the functor up to the boost:signal, but using boost::bind to fill in the arguments so they are not needed when calling the boost::signal
                trainTrackerIterator->second.isTrainTrackOccupiedSignal.connect
                (
                    boost::bind<bool>
                    (
                        trainSignalFunctorIterator->second,true,trainID
                    )
                );
            }
            else
            {
                throw "UpdateTrainCommunicationLeave got called with TrainTrackID that could not be found";
            }
        }
    }
    else
    {
        throw "UpdateTrainCommunicationEnter got called with trainID that could not be found";
    }

}