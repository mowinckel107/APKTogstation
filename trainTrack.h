#ifndef TRAINTRACK_H
#define TRAINTRACK_H

#include "train.h"
#include <vector>


// Basic traintracks. Allows 1, and only 1 train to stand on it, and have pointers to Traintracks further ahead
class TrainTrack
{
    public:
        TrainTrack(std::vector<TrainTrack*> outgoingTraintracks, unsigned int uniqueTrainTrackID);
        TrainTrack* GetNextTrainTrack(unsigned int trainTrackNumber);
        void EnterTrainTracks(Train* IncomingTrain);
        void LeaveTrainTrack(void);
        unsigned int GetID(void);

    private:
        Train* TrainOnTrack = nullptr;
        std::vector<TrainTrack*> connectedTraintracks;
        unsigned int ID;
};

// This class expands the TrainTrack class with the ability to unload trains
class Platform : TrainTrack
{

};

// This class destroys trains, simulating them leaving the area
class TrainInput : TrainTrack
{
    
};

// This class creates trains, simulating them entering the area
class TrainOutput : TrainTrack
{
    
};

#endif /* TRAINTRACK_H */