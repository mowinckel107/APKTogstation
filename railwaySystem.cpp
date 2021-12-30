#include "railwaySystem.h"

RailwaySystem::RailwaySystem(void)
{
    // trainInput2 and trainInput1
    std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainInput;

    TrainInput trainInput1(emptyListOfTrainTracksForTrainInput, 30);
    trainInputs.push_back(trainInput1);

    TrainInput trainInput2(emptyListOfTrainTracksForTrainInput, 31);
    trainInputs.push_back(trainInput2);


    // platform2
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform2;

    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput2.GetID(),&trainInput2));
    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput1.GetID(),&trainInput1));

    Platform platform2(ListOfTrainTracksForplatform2, 21);
    platforms.push_back(platform2);


    // platform1
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform1;

    ListOfTrainTracksForplatform1.insert(std::make_pair(trainInput1.GetID(),&trainInput1));

    Platform platform1(ListOfTrainTracksForplatform1, 20);
    platforms.push_back(platform1);


    // trainTrack3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack3;

    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform2.GetID(),&trainInput1));
    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform1.GetID(),&platform1));

    TrainTrack trainTrack3(ListOfTrainTracksFortrainTrack3, 12);
    trainTracks.push_back(trainTrack3);


    // trainTrack2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack2;

    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(trainTrack3.GetID(),&trainTrack3));
    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(platform2.GetID(),&platform2));

    TrainTrack trainTrack2(ListOfTrainTracksFortrainTrack2, 11);
    trainTracks.push_back(trainTrack2);


    // trainTrack1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack1;

    ListOfTrainTracksFortrainTrack1.insert(std::make_pair(trainTrack3.GetID(),&trainTrack3));

    TrainTrack trainTrack1(ListOfTrainTracksFortrainTrack1, 10);
    trainTracks.push_back(trainTrack1);


    // trainOutput3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput3;

    ListOfTrainTracksFortrainOutput3.insert(std::make_pair(trainTrack2.GetID(),&trainTrack2));

    TrainOutput trainOutput3(ListOfTrainTracksFortrainOutput3,2);
    trainOutputs.push_back(trainOutput3);


    // trainOutput2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput2;

    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack2.GetID(),&trainTrack2));
    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack1.GetID(),&trainTrack1));

    TrainOutput trainOutput2(ListOfTrainTracksFortrainOutput2,1);
    trainOutputs.push_back(trainOutput2);


    // trainOutput1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput1;

    ListOfTrainTracksFortrainOutput1.insert(std::make_pair(trainTrack1.GetID(),&trainTrack1));

    TrainOutput trainOutput1(ListOfTrainTracksFortrainOutput1,0);
    trainOutputs.push_back(trainOutput1);

}