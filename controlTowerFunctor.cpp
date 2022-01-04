#include "controlTowerFunctor.h"
#include "trainFunctor.h"
#include "common.h"
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
#include <iostream>

ControlTowerFunctor::ControlTowerFunctor()
{
    // Lock until we're done
    std::lock_guard<std::mutex> guard(mut_);

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

    // 2) Generate isTrainTrackOccupiedSignal_
        int tempTrack = data.route_.at(0);
        std::vector<int> tempTrains = trackTrains_[tempTrack];
        trainTrackers_.find(trainID)->second.trainsConnectedCount_ = tempTrains.size();

        // for every train driving through the first track on the new trains route
        for (int tempTrain : tempTrains)
        {
            TrainFunctor * tempFunctor = trainFunctors_.find(tempTrain)->second;

            // As we can't really pass the trackID, sig should be called as sig(int)
            // Bound to mode: Some train is requesting track {unknownTrack}
            FunctorWrapper<bool, int, bool, TrainFunctor> TW1(tempFunctor, true);
            trainTrackers_.find(trainID)->second.isTrainTrackOccupiedSignal_->connect(TW1);            
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

void ControlTowerFunctor::operator()(int trainID, int direction)
{
    // this is UpdateTrainCommunicationLeave and UpdateTrainCommunicationEnter in one, with some new features.

    // Lock until we're done
    std::lock_guard<std::mutex> guard(mut_);

    // Does route and train exist?
    if (trainRoutes_.find(trainID) == trainRoutes_.end())
    {
        std::cout << "ERROR: ControlTowerUpdater: Route could not be found using trainID" << std::endl;
        throw "";
    }

    // Find the route for this train
    std::vector<int> * route = &(trainRoutes_.find(trainID)->second);

    // Get route size
    int routeSize = route->size();

    if (routeSize == 0)
    {
        std::cout << "ERROR: ControlTowerUpdater: Train route is empty" << std::endl;
        throw "";
    }

    // Get trainTracker
    std::map<int, TrainTracker>::iterator trainTrackerIterator = trainTrackers_.find(trainID);
    if(trainTrackerIterator == trainTrackers_.end())
    {
        std::cout << "ERROR: UpdateTrainCommunicationLeave got called with trainID that could not be found" << std::endl;
        throw "";

    }
    TrainTracker * trainTracker = &(trainTrackerIterator->second);

    // Leaving or just checking up
    if (direction <= 1)
    {
        // Is this our last stop?
        if (routeSize > 1)
        {
            int tempTrack = route->at(1);
            std::vector<int> tempTrains = trackTrains_[tempTrack];

            // Has train count changed (a train has been created or destroyed)?
            if (trainTracker->trainsConnectedCount_ != tempTrains.size())
            {
                trainTracker->trainsConnectedCount_ = tempTrains.size();
                trainTracker->isTrainTrackOccupiedSignal_->disconnect_all_slots();

                // for every train driving through the first track on the new trains route
                for (int tempTrain : tempTrains)
                {
                    TrainFunctor * tempFunctor = trainFunctors_.find(tempTrain)->second;

                    // As we can't really pass the trackID, sig should be called as sig(int)
                    // Bound to mode: Some train is requesting track {unknownTrack}
                    FunctorWrapper<bool, int, bool, TrainFunctor> TW1(tempFunctor, true);
                    boost::signals2::connection c1 = trainTracker->isTrainTrackOccupiedSignal_->connect(TW1);
                }

            }
        }

        // Leaving
        if (direction == 1)
        {                   
            // Get trains on track that we're LEAVING.
            int trackThatTrainIsLeaving = routeSize > 0 ? route->at(0) : -1;
            std::map<int, std::vector<int>>::iterator trackTrainsIt1 = trackTrains_.find(trackThatTrainIsLeaving);

            if (trackTrainsIt1 != trackTrains_.end())
            {
                std::vector<int> * trainsOnTrackWeAreLeaving = &(trackTrainsIt1->second);

                // Erase train from the stop we're LEAVING
                for (int i = 0; i < trainsOnTrackWeAreLeaving->size(); i++)
                {
                    if (trainsOnTrackWeAreLeaving->at(i) == trainID)
                    {
                        trainsOnTrackWeAreLeaving->erase(trainsOnTrackWeAreLeaving->begin()+i);
                    }
                }
            }

            // Remove the stop that we're LEAVING from route
            route->erase(route->begin());
            routeSize--;            

            // If route has finished, remove train completely
            if (routeSize == 0)
            {
                trainFunctors_.erase(trainID);
                trainTrackers_.erase(trainID);
                trainRoutes_.erase(trainID);
                return;
            }
        }
    }
    else
    {
        int trackThatTrainIsEntering = routeSize > 0 ? route->at(0) : -1;
        int trackThatTrainWillEnterNext = routeSize > 1 ? route->at(1) : -1;

        // Is trackTrains_ OK?
        if (trackTrains_.find(trackThatTrainIsEntering) == trackTrains_.end())
        {
            std::cout << "ERROR: ControlTowerUpdater: Track could not be found using trackThatTrainIsEntering" << std::endl;
            throw "";
        }

        // Get trains on track that we're ENTERING.
        std::vector<int> * trainsOnTrackWeAreEntering = &(trackTrains_.find(trackThatTrainIsEntering)->second);   

        // Remove old connections
        trainTracker->isTrainTrackOccupiedSignal_->disconnect_all_slots();

        // make sure we there is at least 1 more TrainTrack on the route
        if(routeSize > 0)
        {
            std::map<int, std::vector<int>>::iterator trainsEnteringIt = trackTrains_.find(trackThatTrainIsEntering);
            std::map<int, std::vector<int>>::iterator trainsEnterNextIt = trackTrains_.find(trackThatTrainWillEnterNext);

            if (trackTrains_.end() == trainsEnteringIt || trackTrains_.end() == trainsEnterNextIt)
            {
                std::cout << "ERROR: ControlTowerUpdater: Tried to update signals even though there is no trackThatTrainWillEnterNext" << std::endl;
                throw "";
            }

            std::vector<int> trainsEntering = trainsEnteringIt->second;
            std::vector<int> trainsEnterNext = trainsEnterNextIt->second;

            std::map<int, TrainFunctor *>::iterator trainFunctorIterator;

            // Not sure if we need anything here. Train will have permission to enter this track at this point, and reservation happens in train.
            for (auto trainEntering : trainsEntering)
            {
                
            }

            for (auto trainEnterNext : trainsEnterNext)
            {
                trainFunctorIterator = trainFunctors_.find(trainEnterNext);

                // If train still exists
                if(trainFunctorIterator != trainFunctors_.end())
                {
                    trainTracker->isTrainTrackOccupiedSignal_->connect
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
                    std::cout << "ERROR: UpdateTrainCommunicationLeave tried to get a TrainFunctor that could not be found" << std::endl;
                    throw "";
                }
            }
        }


    }

}