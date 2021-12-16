#include "setup.h"



TrainTrackHolder::TrainTrackHolder(void)
{
    // trainInput2 and trainInput1
    std::vector<TrainTrack*> emptyListOfTrainTracksForTrainInput;

    TrainInput trainInput1(emptyListOfTrainTracksForTrainInput, 30);
    trainInputs.push_back(trainInput1);

    TrainInput trainInput2(emptyListOfTrainTracksForTrainInput, 31);
    trainInputs.push_back(trainInput2);


    // platform2
    std::vector<TrainTrack*> ListOfTrainTracksForplatform2;

    ListOfTrainTracksForplatform2.push_back(&trainInput2);
    ListOfTrainTracksForplatform2.push_back(&trainInput1);

    Platform platform2(ListOfTrainTracksForplatform2, 21);
    platforms.push_back(platform2);


    // platform1
    std::vector<TrainTrack*> ListOfTrainTracksForplatform1;

    ListOfTrainTracksForplatform1.push_back(&trainInput1);

    Platform platform1(ListOfTrainTracksForplatform1, 20);
    platforms.push_back(platform1);


    // trainTrack3
    std::vector<TrainTrack*> ListOfTrainTracksFortrainTrack3;

    ListOfTrainTracksFortrainTrack3.push_back(&platform2);
    ListOfTrainTracksFortrainTrack3.push_back(&platform1);

    TrainTrack trainTrack3(ListOfTrainTracksFortrainTrack3, 12);
    trainTracks.push_back(trainTrack3);


    // trainTrack2
    std::vector<TrainTrack*> ListOfTrainTracksFortrainTrack2;

    ListOfTrainTracksFortrainTrack2.push_back(&trainTrack3);
    ListOfTrainTracksFortrainTrack2.push_back(&platform2);

    TrainTrack trainTrack2(ListOfTrainTracksFortrainTrack2, 11);
    trainTracks.push_back(trainTrack2);


    // trainTrack1
    std::vector<TrainTrack*> ListOfTrainTracksFortrainTrack1;

    ListOfTrainTracksFortrainTrack1.push_back(&trainTrack3);

    TrainTrack trainTrack1(ListOfTrainTracksFortrainTrack1, 10);
    trainTracks.push_back(trainTrack1);


    // trainOutput3
    std::vector<TrainTrack*> ListOfTrainTracksFortrainOutput3;

    ListOfTrainTracksFortrainOutput3.push_back(&trainTrack2);

    TrainOutput trainOutput3(ListOfTrainTracksFortrainOutput3,0);
    trainOutputs.push_back(trainOutput3);


    // trainOutput2
    std::vector<TrainTrack*> ListOfTrainTracksFortrainOutput2;

    ListOfTrainTracksFortrainOutput2.push_back(&trainTrack2);
    ListOfTrainTracksFortrainOutput2.push_back(&trainTrack1);

    TrainOutput trainOutput2(ListOfTrainTracksFortrainOutput2,1);
    trainOutputs.push_back(trainOutput2);


    // trainOutput1
    std::vector<TrainTrack*> ListOfTrainTracksFortrainOutput1;

    ListOfTrainTracksFortrainOutput1.push_back(&trainTrack1);

    TrainOutput trainOutput1(ListOfTrainTracksFortrainOutput1,2);
    trainOutputs.push_back(trainOutput1);

}