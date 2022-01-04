#include "controlTowerFunctor.h"
#include "trainFunctor.h"
#include "common.h"
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
#include <iostream>

ControlTowerFunctor::ControlTowerFunctor(bool managerMode)
{
    // Lock until we're done
    std::lock_guard<std::mutex> guard(mut_);

    // ManagerMode is when the ControlTower actively signals trains to change stuff, in contrast to trains doing most of it themselves.
    managerMode_ = managerMode;

    // Creating 3 routes for all 3 starting positions
    // 1
    RouteVector trainRouteForTrainOutput0;

    std::vector<int> route10 {1,10,12,20,30};
    trainRouteForTrainOutput0.push_back(route10);

    std::vector<int> route11 {1,10,12,21,30};
    trainRouteForTrainOutput0.push_back(route11);

    std::vector<int> route12 {1,10,12,21,31};
    trainRouteForTrainOutput0.push_back(route12);

    // 2
    RouteVector trainRouteForTrainOutput1;

    std::vector<int> route20 {2,10,12,21,31};
    trainRouteForTrainOutput1.push_back(route20);

    std::vector<int> route21 {2,11,21,30};
    trainRouteForTrainOutput1.push_back(route21);

    std::vector<int> route22 {2,11,12,20,31};
    trainRouteForTrainOutput1.push_back(route22);

    // 3
    RouteVector trainRouteForTrainOutput2;

    std::vector<int> route30 {3,11,21,31};
    trainRouteForTrainOutput2.push_back(route30);

    std::vector<int> route31 {3,11,21,30};
    trainRouteForTrainOutput2.push_back(route31);

    std::vector<int> route32 {3, 11,12,20,30};
    trainRouteForTrainOutput2.push_back(route32);  

    // Insert into map
    routes_.insert(std::make_pair(1, trainRouteForTrainOutput0));
    routes_.insert(std::make_pair(2, trainRouteForTrainOutput1));
    routes_.insert(std::make_pair(3, trainRouteForTrainOutput2));
}

TrainCommunicationAndRoute ControlTowerFunctor::operator()(int startingTrainTrackID, int trainID, TrainFunctor * newTrainFunctor,  TrainTracker trainTracker)
{
    // Lock until we're done
    std::lock_guard<std::mutex> guard(mut_);

    // this is GetRouteAndSignals()

    // 0) Save trainTracker
        trainTrackers_.insert(std::make_pair(trainID, trainTracker));

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
        // Renamed it data because code was getting ridiculous
        TrainCommunicationAndRoute data;

        // Choose route depending on starting track. Same as before, but more flexible.       
        data.route_ = myRoutes[routeCounter]; // copy, not move

    // 2) Generate leavingSignal_ and isTrainTrackOccupiedSignal_
    // What happens now depends on if we're in managerMode. 
        // If we are, we generate just enough for the trains to know when to send for help.
        if (managerMode_ == true)
        {
            // todo
        }
        // If we're not, we generate pretty much everything the train needs to do everything itself.
        else
        {
            std::vector<int> tempRoute;
            std::vector<int> tempTrains;

            std::map<int, std::vector<boost::signals2::connection>> trainsAdded;
            std::vector<boost::signals2::connection> tempTrainAdded;

            TrainFunctor * tempFunctor;
            boost::signals2::connection c1;
            std::map<int, TrainFunctor *>::iterator myIt1;

            // Connections representing one track relating to a train
            vectorOfConnections loopTrackConnections;
            trackConnectionMap loopTrainConnections;

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
                            // Bound to mode: Some train is requesting track {unknownTrack}

                            FunctorWrapper<bool, int, bool, TrainFunctor> TW1(tempFunctor, true);
                            c1 = data.isTrainTrackOccupiedSignal_.connect(TW1);
                            loopTrackConnections.push_back(c1);

                            // Save connections in trainsAdded. We'll need them for when this train shows up again.
                            tempTrainAdded.clear();
                            tempTrainAdded.push_back(c1);

                            trainsAdded.insert(std::make_pair(tempTrain, tempTrainAdded));

                        }
                        // We do however log these connections for every time the train shows up under a seperate track
                        else
                        {
                            tempTrainAdded = trainsAdded.find(tempTrain)->second;

                            for (auto temp4 : tempTrainAdded)
                            {
                                loopTrackConnections.push_back(std::move(temp4));
                            }
                        }
                    }
                    loopTrainConnections.insert(std::make_pair(tempTrack, loopTrackConnections));
                }

                trainTrackConnections_.insert(std::make_pair(myIt1->first, loopTrainConnections));
            }
        }

    // 3) Save this route
        trainRoutes_.insert(std::make_pair(trainID, data.route_));

    // 4) Save tracks
        for (auto temp3 : data.route_)
        {
            std::map<int, std::vector<int>>::iterator trackTrainsIt1 = trackTrains_.find(temp3);

            if (trackTrainsIt1 == trackTrains_.end())
            {
                std::vector<int> trackTrain1 = {trainID};
                trackTrains_.insert(std::make_pair(temp3, trackTrain1));
            }
            else
            {
                trackTrainsIt1->second.push_back(trainID);
            }
        }

    // 5) Save train functor
        trainFunctors_.insert(std::make_pair(trainID, newTrainFunctor));

    return std::move(data);    
}

void ControlTowerFunctor::operator()(int trainID)
{
    // this is UpdateTrainCommunicationLeave and UpdateTrainCommunicationEnter in one, with some new features.

    // Does route and train exist?
    if (trainRoutes_.find(trainID) == trainRoutes_.end())
    {
        throw "ControlTowerUpdater: Route could not be found using trainID";
    }

    // Find the route for this train
    std::vector<int> * route = &(trainRoutes_.find(trainID)->second);

    // Check route size
    int routeSize = route->size();
    if (routeSize == 0)
    {
        throw "ControlTowerUpdater: Train route is empty";
    }

    // Get the coming two track IDs
    int trackThatTrainIsLeaving = route->at(0);
    int trackThatTrainIsEntering = routeSize > 1 ? route->at(1) : -1;
    int trackThatTrainWillEnterNext = routeSize > 2 ? route->at(2) : -1;

    // Is trackTrains_ OK?
    if (trackTrains_.find(trackThatTrainIsLeaving) == trackTrains_.end())
    {
        throw "ControlTowerUpdater: Track could not be found using trackThatTrainIsLeaving";
    }

    // Get trains on track that we're LEAVING.
    std::vector<int> * trainsOnTrackWeAreLeaving = &(trackTrains_.find(trackThatTrainIsLeaving)->second);   

    // Remove the stop that we're LEAVING from route
    route->erase(route->begin());
    routeSize--;

    // Erase train from the stop we're LEAVING
    for (int i = 0; i < trainsOnTrackWeAreLeaving->size(); i++)
    {
        if (trainsOnTrackWeAreLeaving->at(i) == trainID)
        {
            trainsOnTrackWeAreLeaving->erase(trainsOnTrackWeAreLeaving->begin()+i);
        }
    }

    // In manager mode, ControlTower does most of the work instead of train.
    if (managerMode_)
    {
        // I'll deal with this later. Mahbe needs to be updated
        /*
        std::map<int, TrainTracker>::iterator trainTrackerIterator = trainTrackers_.find(trainID);

        // if trainID exists
        if(trainTrackerIterator != trainTrackers_.end())
        {   
            // Remove old connections
            trainTrackerIterator->second.leavingSignal_->disconnect_all_slots();
            trainTrackerIterator->second.isTrainTrackOccupiedSignal_->disconnect_all_slots();

            // make sure we there is at least 1 more TrainTrack on the route
            if(routeSize > 0)
            {
                std::map<int, std::vector<int>>::iterator trainsEnteringIt = trackTrains_.find(trackThatTrainIsEntering);
                std::map<int, std::vector<int>>::iterator trainsEnterNextIt = trackTrains_.find(trackThatTrainWillEnterNext);

                if (trackTrains_.end() == trainsEnteringIt || trackTrains_.end() == trainsEnterNextIt)
                {
                    throw "ControlTowerUpdater: Tried to update signals even though there is no trackThatTrainWillEnterNext";
                }

                std::vector<int> trainsEntering = trainsEnteringIt->second;
                std::vector<int> trainsEnterNext = trainsEnterNextIt->second;

                std::map<int, TrainFunctor *>::iterator trainFunctorIterator;

                // Find correct functor
                for (auto trainEntering : trainsEntering)
                {
                    trainFunctorIterator = trainFunctors_.find(trainEntering);
                    
                    // If train still exists
                    if(trainFunctorIterator != trainFunctors_.end())
                    {
                        // We connect the functor up to the boost:signal, but using boost::bind to fill in the arguments so they are not needed when calling the boost::signal
                        trainTrackerIterator->second.leavingSignal_->connect
                        (
                            // typedef boost::signals2::signal<bool (int)>::slot_type leavingSignalBind
                            // this uses boost::bind automatically
                            // https://www.boost.org/doc/libs/1_49_0/doc/html/signals2/tutorial.html#signals2.tutorial.connection-management
                            // https://stackoverflow.com/questions/10752844/signals-and-binding-arguments
                            leavingSignalBind(
                                *(trainFunctorIterator->second),trainID,boost::placeholders::_1
                            )
                        );                   
                    }
                    else
                    {
                        throw "UpdateTrainCommunicationLeave tried to get a TrainFunctor that could not be found";
                    }
                }

                for (auto trainEnterNext : trainsEnterNext)
                {
                    trainFunctorIterator = trainFunctors_.find(trainEnterNext);

                    // If train still exists
                    if(trainFunctorIterator != trainFunctors_.end())
                    {
                        trainTrackerIterator->second.isTrainTrackOccupiedSignal_->connect
                        (
                            // typedef boost::signals2::signal<bool (int), SignalCombOr<bool(bool,bool)>>::slot_type isTrainOccupiedSignalBind
                            // this uses boost::bind automatically
                            // https://www.boost.org/doc/libs/1_49_0/doc/html/signals2/tutorial.html#signals2.tutorial.connection-management
                            // https://stackoverflow.com/questions/10752844/signals-and-binding-arguments
                            isTrainOccupiedSignalBind
                            (
                                *(trainFunctorIterator->second),true,boost::placeholders::_1
                            )
                        );
                    }
                    else
                    {
                        throw "UpdateTrainCommunicationLeave tried to get a TrainFunctor that could not be found";
                    }
                }
            }
        }
        else
        {
            throw "UpdateTrainCommunicationLeave got called with trainID that could not be found";
        }
        */
    }

    // If route has finished, remove train completely
    if (route->size() == 0)
    {
        trainFunctors_.erase(trainID);
        trainTrackers_.erase(trainID);
        trainRoutes_.erase(trainID);
        return;
    }

}