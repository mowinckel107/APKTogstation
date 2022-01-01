#include "controlTowerFunctor.h"
#include "trainFunctor.h"
#include "functorWrapper.h"
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <functional>

ControlTowerFunctor::ControlTowerFunctor(bool managerMode)
{
    // ManagerMode is when the ControlTower actively signals trains to change stuff, in contrast to trains doing most of it themselves.
    managerMode_ = managerMode;

    // Creating 3 routes for all 3 starting positions
    // 1
    RouteVector trainRouteForTrainOutput0;

    std::vector<int> route10 {10,12,20,30};
    trainRouteForTrainOutput0.push_back(route10);

    std::vector<int> route11 {10,12,21,30};
    trainRouteForTrainOutput0.push_back(route11);

    std::vector<int> route12 {10,12,21,31};
    trainRouteForTrainOutput0.push_back(route12);

    // 2
    RouteVector trainRouteForTrainOutput1;

    std::vector<int> route20 {10,12,21,31};
    trainRouteForTrainOutput1.push_back(route20);

    std::vector<int> route21 {11,21,30};
    trainRouteForTrainOutput1.push_back(route21);

    std::vector<int> route22 {11,12,20,31};
    trainRouteForTrainOutput1.push_back(route22);

    // 3
    RouteVector trainRouteForTrainOutput2;

    std::vector<int> route30 {11,21,31};
    trainRouteForTrainOutput2.push_back(route30);

    std::vector<int> route31 {11,21,30};
    trainRouteForTrainOutput2.push_back(route31);

    std::vector<int> route32 {11,12,20,30};
    trainRouteForTrainOutput2.push_back(route32);  

    // Insert into map
    routes_.insert(std::make_pair(0, trainRouteForTrainOutput0));
    routes_.insert(std::make_pair(1, trainRouteForTrainOutput1));
    routes_.insert(std::make_pair(2, trainRouteForTrainOutput2));
}

TrainCommunicationAndRoute ControlTowerFunctor::operator()(int startingTrainTrackID, int trainID, TrainFunctor * newTrainFunctor)
{
    // this is GetRouteAndSignals()

    // 1) Pick a route
        static int routeCounter = 0;

        RouteVector myRoutes = routes_.find(startingTrainTrackID)->second;

        int routeMax = myRoutes.size() - 1;

        // This will yield trouble if there are more routes for one output than another
        // For example 2 and 3. We count to 3 on one output (max 2), it is reset, and the next output never reached 3.
        // Too tired to do anything about it
        if (routeCounter > routeMax)
        {
            routeCounter = 0;
        }

        // TrainCommunicationAndRoute which is the return type used for Train.
        // This is TrainTracker and TrainCommunicationAndRoute in one.
        // Renamed it data because code was getting ridiculous
        TrainCommunicationAndRoute data;

        // Choose route depending on starting track. Same as before, but more flexible.       
        data.route_ = myRoutes[routeCounter];

    // 2) Generate leavingSignal_ and isTrainTrackOccupiedSignal_
        std::vector<int> tempRoute;
        std::vector<int> tempTrains;

        std::map<int, std::vector<boost::signals2::connection>> trainsAdded;
        std::vector<boost::signals2::connection> tempTrainAdded;


        TrainFunctor * tempFunctor;
        boost::signals2::connection c1;
        boost::signals2::connection c2;
        boost::signals2::connection c3;
        std::map<int, TrainFunctor *>::iterator myIt1;

        // Connections representing one track relating to a train
        vectorOfConnections loopTrackConnections;
        trackConnectionMap loopTrainConnections;
        trainTrackConnectionMap loopTrainTrackConnections;

        // for every train in existence
        for (myIt1 = trainFunctors_.begin(); myIt1 != trainFunctors_.end(); myIt1++)
        {
            loopTrainConnections.clear();

            // Filter route
            tempRoute.clear();
            for (int temp1 : data.route_)
            {
                for (int temp2 : trainRoutes_[myIt1->first])
                {
                    if (temp1 == temp2)
                    {
                        tempRoute.push_back(temp1);
                    }
                }
            }

            // for every track on the new trains route that is also in current train in existence
            for (int tempTrack : tempRoute)
            {
                loopTrackConnections.clear();

                tempTrains = trackTrains_[tempTrack];


                // for every train driving through a track on the new trains route
                for (int tempTrain : tempTrains)
                {
                    // We connect functors ONCE per train
                    if (trainsAdded.find(tempTrain) == trainsAdded.end())
                    {
                        tempFunctor = trainFunctors_.find(tempTrain)->second;

                        // As we can't really pass the trackID, sig should be called as sig(int)
                        // Bound to mode: Train {newTrain} has left track {unknownTrack}
                        FunctorWrapper<int, int, void, TrainFunctor> TW1(tempFunctor, trainID);

                        c1 = data.leavingSignal_.connect(TW1);
                        loopTrackConnections.push_back(c1);

                        // As we can't really pass the trackID, sig should be called as sig(int)
                        // Bound to mode: Some train is requesting track {unknownTrack}

                        FunctorWrapper<bool, int, bool, TrainFunctor> TW2(tempFunctor, true);
                        c2 = data.isTrainTrackOccupiedSignal_.connect(TW2);
                        loopTrackConnections.push_back(c2);

                        // As we can't really pass the trackConnection, sig should be called as sig(trackConnectionMap)
                        // Bound to mode: A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.

                        FunctorWrapper<int, trackConnectionMap, void, TrainFunctor> TW3(tempFunctor, trainID);
                        loopTrackConnections.push_back(c3);

                        // Save connections in trainsAdded. We'll need them for when this train shows up again.
                        tempTrainAdded.clear();
                        tempTrainAdded.push_back(c1);
                        tempTrainAdded.push_back(c2);
                        tempTrainAdded.push_back(c3);

                        trainsAdded.insert(std::make_pair(tempTrain, tempTrainAdded));

                    }
                    // We do however log these connections for every time the train shows up under a seperate track
                    else
                    {
                        tempTrainAdded = trainsAdded.find(tempTrain)->second;

                        for (auto temp4 : tempTrainAdded)
                        {
                            loopTrackConnections.push_back(temp4);
                        }
                    }
                }
                loopTrainConnections.insert(std::make_pair(tempTrack, loopTrackConnections));
            }

            loopTrainTrackConnections.insert(std::make_pair(myIt1->first, loopTrainConnections));
        }
        data.trainTrackConnections_ = loopTrainTrackConnections; // mov?


    // 3) Save this route
        trainRoutes_.insert(std::make_pair(trainID, data.route_));

    // 4) Save tracks
        for (auto temp3 : data.route_)
        {
            trackTrains_.find(temp3)->second.push_back(trainID);
        }       

    // 6) Save train functor
        trainFunctors_.insert(std::make_pair(trainID, newTrainFunctor));


    return data;    
}

void ControlTowerFunctor::operator()(int TrainTrackID, int trainID, int direction)
{
    // this is UpdateTrainCommunicationLeave and UpdateTrainCommunicationEnter in one, with some new features.


    // In manager mode, ControlTower does most of the work.
    if (managerMode_)
    {
        if (direction == 1)
        {
            // Skal ikke fjernes, bare tilpasses
            /*
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
            */
        }
        else if (direction == 2)
        {
            // skal ikke fjernes, bare tilpasses
            /*
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
            */
        }
    }

}