#ifndef TRAINTRACK_H
#define TRAINTRACK_H

#include "train.h"
#include <map>
#include <iterator>
#include <string>
#include <iostream>

class Train;

// Basic traintracks. Allows 1, and only 1 train to stand on it, and have pointers to Traintracks further ahead
class TrainTrack
{
    public:
        TrainTrack(std::map<int, TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID);
        TrainTrack* GetNextTrainTrack(int trainTrackNumber);
        virtual bool EnterTrainTracks(Train* IncomingTrain);
        void LeaveTrainTrack(void);
        int GetID(void);

    private:
        Train* TrainOnTrack = nullptr;
        std::map<int, TrainTrack*> connectedTraintracks;
        int ID;
};

// This class expands the TrainTrack class with the ability to unload trains
class Platform : public TrainTrack
{
    public:
        Platform(std::map<int, TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}
};

// This class destroys trains, simulating them leaving the area
class TrainInput : public TrainTrack
{
    public:
        TrainInput(std::map<int, TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}

        bool EnterTrainTracks(Train* IncomingTrain);
};

// This class creates trains, simulating them entering the area
class TrainOutput : public TrainTrack
{
    public:
        TrainOutput(std::map<int, TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID) : TrainTrack(outgoingTraintracks, uniqueTrainTrackID)
        {}
};

#endif /* TRAINTRACK_H */