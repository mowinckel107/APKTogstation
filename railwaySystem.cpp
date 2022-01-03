#include "railwaySystem.h"

RailwaySystem::RailwaySystem(void)
{
    // Fill arrays with dummy tracks
    // Yes, this is dumb, but it's an easy way to probably not have pointers pointing at something wrong
    std::map<int, TrainTrack*> emptyMapOfTracks;
    Platform dummyPlatform = Platform(emptyMapOfTracks, 500);
    TrainTrack dummyTrack = TrainTrack(emptyMapOfTracks, 501);
    TrainInput dummyInput = TrainInput(emptyMapOfTracks, 502);
    TrainOutput dummyOutput = TrainOutput(emptyMapOfTracks, 503);

    platforms.fill(dummyPlatform);
    trainTracks.fill(dummyTrack);
    trainInputs.fill(dummyInput);
    trainOutputs.fill(dummyOutput);    

    // trainInput2 and trainInput1
    trainInputs[1] = TrainInput(emptyMapOfTracks, 31);
    TrainInput * trainInput2 = &(trainInputs[1]); 

    trainInputs[0] = TrainInput(emptyMapOfTracks, 30);
    TrainInput * trainInput1 = &(trainInputs[0]);


    // platform2
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform2;

    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput2->GetID(),trainInput2));
    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platforms[1] = Platform(ListOfTrainTracksForplatform2, 21);
    Platform * platform2 = &(platforms[1]);

    // platform1
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform1;

    ListOfTrainTracksForplatform1.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platforms[0] = Platform(ListOfTrainTracksForplatform1, 20);
    Platform * platform1 = &(platforms[0]);

    // trainTrack3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack3;

    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform2->GetID(),trainInput1));
    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform1->GetID(),platform1));

    trainTracks[2] = TrainTrack(ListOfTrainTracksFortrainTrack3, 12);
    TrainTrack * trainTrack3 = &(trainTracks[2]);


    // trainTrack2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack2;

    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));
    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(platform2->GetID(),platform2));

    trainTracks[1] = TrainTrack(ListOfTrainTracksFortrainTrack2, 11);
    TrainTrack * trainTrack2 = &(trainTracks[1]);

    // trainTrack1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack1;

    ListOfTrainTracksFortrainTrack1.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));

    trainTracks[0] = TrainTrack(ListOfTrainTracksFortrainTrack1, 10);
    TrainTrack * trainTrack1 = &(trainTracks[0]);

    // trainOutput3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput3;

    ListOfTrainTracksFortrainOutput3.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));

    trainOutputs[2] = TrainOutput(ListOfTrainTracksFortrainOutput3,2);
    TrainOutput * trainOutput3 = &(trainOutputs[2]);

    // trainOutput2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput2;

    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));
    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    trainOutputs[1] = TrainOutput(ListOfTrainTracksFortrainOutput2,1);
    TrainOutput * trainOutput2 = &(trainOutputs[1]);  

    // trainOutput1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput1;

    ListOfTrainTracksFortrainOutput1.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    trainOutputs[0] = TrainOutput(ListOfTrainTracksFortrainOutput1,0);
    TrainOutput * trainOutput1 = &(trainOutputs[0]);    

}