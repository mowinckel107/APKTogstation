#include "railwaySystem.h"
#include "common.h"

RailwaySystem::RailwaySystem(void)
{
    // Fill arrays with dummy tracks
    // Yes, this is dumb, but it's an easy way to probably not have pointers pointing at something wrong
    std::map<int, TrainTrack*> emptyMapOfTracks;

    // trainInput2 and trainInput1
    input2_ = TrainInput(emptyMapOfTracks, 31);
    TrainInput * trainInput2 = &input2_; 

    input1_ = TrainInput(emptyMapOfTracks, 30);
    TrainInput * trainInput1 = &input1_;

    // platform2
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform2;

    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput2->GetID(),trainInput2));
    ListOfTrainTracksForplatform2.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platform2_ = Platform(ListOfTrainTracksForplatform2, 21);
    Platform * platform2 = &platform2_;

    // platform1
    std::map<int, TrainTrack*> ListOfTrainTracksForplatform1;

    ListOfTrainTracksForplatform1.insert(std::make_pair(trainInput1->GetID(),trainInput1));

    platform1_ = Platform(ListOfTrainTracksForplatform1, 20);
    Platform * platform1 = &platform1_;

    // trainTrack3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack3;

    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform2->GetID(),trainInput1));
    ListOfTrainTracksFortrainTrack3.insert(std::make_pair(platform1->GetID(),platform1));

    track3_ = TrainTrack(ListOfTrainTracksFortrainTrack3, 12);
    TrainTrack * trainTrack3 = &track3_;

    // trainTrack2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack2;

    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));
    ListOfTrainTracksFortrainTrack2.insert(std::make_pair(platform2->GetID(),platform2));

    track2_ = TrainTrack(ListOfTrainTracksFortrainTrack2, 11);
    TrainTrack * trainTrack2 = &track2_;

    // trainTrack1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainTrack1;

    ListOfTrainTracksFortrainTrack1.insert(std::make_pair(trainTrack3->GetID(),trainTrack3));

    track1_ = TrainTrack(ListOfTrainTracksFortrainTrack1, 10);
    TrainTrack * trainTrack1 = &track1_;

    // trainOutput3
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput3;

    ListOfTrainTracksFortrainOutput3.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));

    output3_ = TrainOutput(ListOfTrainTracksFortrainOutput3,3);
    TrainOutput * trainOutput3 = &output3_;

    // trainOutput2
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput2;

    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack2->GetID(),trainTrack2));
    ListOfTrainTracksFortrainOutput2.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    output2_ = TrainOutput(ListOfTrainTracksFortrainOutput2,2);
    TrainOutput * trainOutput2 = &output2_;  
    // trainOutput1
    std::map<int, TrainTrack*> ListOfTrainTracksFortrainOutput1;

    ListOfTrainTracksFortrainOutput1.insert(std::make_pair(trainTrack1->GetID(),trainTrack1));

    output1_ = TrainOutput(ListOfTrainTracksFortrainOutput1,1);
    TrainOutput * trainOutput1 = &output1_;    

}