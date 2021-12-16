#ifndef SETUP_H
#define SETUP_H


#include "trainTrack.h"

class TrainTrackHolder
{
    public:
    TrainTrackHolder(void);

    std::vector<TrainTrack> trainTracks;
    std::vector<Platform> platforms;
    std::vector<TrainInput> trainInputs;
    std::vector<TrainOutput> trainOutputs;
};



#endif /* SETUP_H */