#ifndef TRAINFUNCTOR_H
#define TRAINFUNCTOR_H

typedef vectorOfConnections = std::vector<boost::signals2::signal<bool ()>;
typedef trackConnectionMap = std::map<int, vectorOfSignals>;
typedef trainTrackConnectionMap = std::map<int, trackConnectionMap>;

class TrainFunctor
{

private:
	int reservedID_ = 0;
    int ownerTrainID_ = 0;

    // 1) train, 2) track, 3) connections
    trainTrackConnectionMap trainTrackConnections_;

public:

    // Setup
    TrainFunctor(int ownerTrainID);

    // Clear reservation
    bool operator()();

    // Reserve track {trackID}
    bool operator()(int trackID);

    // Train {trainID} has left track {trackID}
    bool operator()(int trackID, int trainID);

    // Some train is requesting track {TrackID}
    bool operator()(bool isRequest, int trackID);

    // We belong to a new train and we need to be fed with a list of how everyone else is connected to us
    bool operator()(trainTrackConnectionMap trainTrackConnections);

    // A new train has arrived, and it wants us to know every way it is connected to the existing train we belong to.
    bool operator()(int newTrainID, trackConnectionMap trackConnection);

};

#endif /* TRAINFUNCTOR_H */