#include "railwaySystem.h"

RailwaySystem::RailwaySystem(void)
{
    // trainInput2 and trainInput1
    std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainInput;

    trainInputs.push_back(TrainInput(emptyListOfTrainTracksForTrainInput, 30));
    TrainInput * trainInput1 = &(trainInputs.back()); 

    trainInputs.push_back(TrainInput(emptyListOfTrainTracksForTrainInput, 31));
    TrainInput * trainInput2 = &(trainInputs.back()); 

    // platform2
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform2;

    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput2->GetID(),trainInput2));
    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platforms.push_back(Platform(ListOfTrainTracksForplatform2, 21));
    Platform * platform2 = &(platforms.back());

    // platform1
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform1;

    ListOfTrainTracksForplatform1.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platforms.push_back(Platform(ListOfTrainTracksForplatform1, 20));
    Platform * platform1 = &(platforms.back());


    // trainTrack3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack3;

    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform2->GetID(),trainInput1));
    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform1->GetID(),platform1));

    trainTracks.push_back(TrainTrack(ListOfTrainTracksFortrainTrack3, 12));
    TrainTrack * trainTrack3 = &(trainTracks.back());


    // trainTrack2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack2;

    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));
    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(platform2->GetID(),platform2));

    trainTracks.push_back(TrainTrack(ListOfTrainTracksFortrainTrack2, 11));
    TrainTrack * trainTrack2 = &(trainTracks.back());

    // trainTrack1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack1;

    ListOfTrainTracksFortrainTrack1.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));

    trainTracks.push_back(TrainTrack(ListOfTrainTracksFortrainTrack1, 10));
    TrainTrack * trainTrack1 = &(trainTracks.back());

    // trainOutput3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput3;

    ListOfTrainTracksFortrainOutput3.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));

    trainOutputs.push_back(TrainOutput(ListOfTrainTracksFortrainOutput3,2));
    TrainOutput * trainOutput3 = &(trainOutputs.back());

    // trainOutput2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput2;

    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));
    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    trainOutputs.push_back(TrainOutput(ListOfTrainTracksFortrainOutput2,1));
    TrainOutput * trainOutput2 = &(trainOutputs.back());  

    // trainOutput1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput1;

    ListOfTrainTracksFortrainOutput1.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    trainOutputs.push_back(TrainOutput(ListOfTrainTracksFortrainOutput1,0));
    TrainOutput * trainOutput1 = &(trainOutputs.back());    

}