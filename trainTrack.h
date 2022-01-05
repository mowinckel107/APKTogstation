#ifndef TRAINTRACK_H
#define TRAINTRACK_H

#include "train.h"
#include "common.h"
#include <map>
#include <iterator>
#include <string>
#include <iostream>

class Train;

// Basic traintracks. Allows 1, and only 1 train to stand on it, and have pointers to Traintracks further ahead
class TrainTrack
{
    public:
        TrainTrack() {}

        TrainTrack(std::map<int, TrainTrack*> outgoingTraintracks, int uniqueTrainTrackID);
        TrainTrack* GetNextTrainTrack(int trainTrackNumber);
        virtual bool EnterTrainTracks(Train* IncomingTrain);
        //virtual void EnterTrainTracks(Train* trainPtr, ControlTowerFunctor * ct, std::mutex * mut) {}
        virtual bool HasUnloadedCargo(void) { return false; }
        void LeaveTrainTrack(void);
        int GetID(void);
        //int TrainCounter = 1;

    private:
        Train* TrainOnTrack = nullptr;
        std::map<int, TrainTrack*> connectedTraintracks;
        int ID;

};

// This class expands the TrainTrack class with the ability to unload trains
class Platform : public TrainTrack
{
    public:
        Platform(){}

        Platform(std::map<int, TrainTrack*> outgoingTraintracks, int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}

        bool EnterTrainTracks(Train* IncomingTrain);

        bool HasUnloadedCargo(void);
};

// This class destroys trains, simulating them leaving the area
class TrainInput : public TrainTrack
{
    public:
        TrainInput(){}

        TrainInput(std::map<int, TrainTrack*> outgoingTraintracks, int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}

        bool EnterTrainTracks(Train* IncomingTrain);
};

// This class creates trains, simulating them entering the area
class TrainOutput : public TrainTrack
{
    public:
        TrainOutput(){}

        TrainOutput(std::map<int, TrainTrack*> outgoingTraintracks, int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}

        //void EnterTrainTracks(Train* trainPtr, ControlTowerFunctor * ct, std::mutex * mut);
};

#endif /* TRAINTRACK_H */