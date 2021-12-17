#include "tests.h"




void TestsOfTrainTrack1(void);
void TestsOfTrainTrack2(void);
void TestsOfTrainTrack3(void);

void TestsOfTrain(void);



void RunTests(void)
{
std::cout << "Starting Tests of TrainTrack:" << std::endl;
TestsOfTrainTrack1();
TestsOfTrainTrack2();
TestsOfTrainTrack3();

TestsOfTrain();
}

void TestsOfTrainTrack1(void)
{
    // Test 1, Linking 2 TrainTracks
    try
    {
    // Step 1: Arrange

    // Give TrainTrack2 an empty vector, as it leads to no other TrainTracks
    std::vector<TrainTrack*> emptyListOfTrainTracksForTrainTrack2;

    TrainTrack myTrainTrack2(emptyListOfTrainTracksForTrainTrack2, 2);


    // Step 2: Act

    // Give TrainTrack1 a vector only containing a pointer to TrainTrack2
    std::vector<TrainTrack*> listOfTrainTracksForTrainTrack1;
    listOfTrainTracksForTrainTrack1.push_back(&myTrainTrack2);

    TrainTrack myTrainTrack1(listOfTrainTracksForTrainTrack1, 2);
    }
    catch(...)
    {
        std::cout << "      Test 1, Linking 2 TrainTracks, failed" << std::endl;
        return;
    }
    std::cout << "      Test 1, Linking 2 TrainTracks, succeeded" << std::endl;
}

void TestsOfTrainTrack2(void)
{
    // Test 2, Train entering and leaving TrainTrack

    try
    {
        // Step 1: Arrange

        // Give TrainTrack2 an empty vector, as it leads to no other TrainTracks
        std::vector<TrainTrack*> emptyListOfTrainTracksForTrainTrack2;
        TrainTrack myTrainTrack2(emptyListOfTrainTracksForTrainTrack2, 2);

        // Give TrainTrack1 a vector only containing a pointer to TrainTrack2
        std::vector<TrainTrack*> listOfTrainTracksForTrainTrack1;
        listOfTrainTracksForTrainTrack1.push_back(&myTrainTrack2);

        TrainTrack myTrainTrack1(listOfTrainTracksForTrainTrack1, 1);

        // Create Train to use for exercising TrainTracks
        Train myTrain(0, nullptr);

        // Variable to hold pointer to nextTrainTrack instead of controlTower or train
        TrainTrack * nextTrainTrack;


        // Step 2: Act

        myTrainTrack1.EnterTrainTracks(&myTrain);
        nextTrainTrack = myTrainTrack1.GetNextTrainTrack(0);
        myTrainTrack1.LeaveTrainTrack();
        nextTrainTrack->EnterTrainTracks(&myTrain);


        // Step 3: Assert
        //TODO friend function to test internals of TrainTracks.
    }
    catch(...)
    {
        std::cout << "      Test 2, Train entering and leaving TrainTrack, failed" << std::endl;
        return;
    }
    std::cout << "      Test 2, Train entering and leaving TrainTrack, succeeded" << std::endl;
}



void TestsOfTrainTrack3(void)
{
    // Test 3, Crashing 2 Trains together
    try
    {
        // Step 1: Arrange

        // Give myTrainTrack an empty vector, as it leads to no other TrainTracks
        std::vector<TrainTrack*> emptyListOfTrainTracksForTrainTrack;
        TrainTrack myTrainTrack(emptyListOfTrainTracksForTrainTrack, 0);

        // Create Trains to use for exercising TrainTracks
        Train myTrain1(0,nullptr);
        Train myTrain2(1,nullptr);


        // Step 2: Act

        myTrainTrack.EnterTrainTracks(&myTrain1);
        // train1 does NOT leave the TrainTrack before train2 enters TrainTrack.


        // Step 3: Assert
        //TODO friend function to test internals of TrainTracks.
        try
        {
            myTrainTrack.EnterTrainTracks(&myTrain2);
        }
        catch(const char* msg)
        {
            if(static_cast<std::string>(msg) == "A train crashed into another train")
            {
                std::cout << "      Test 3, Crashing 2 Trains together, succeeded" << std::endl;
                return;
            }
        }
    }
    catch(...)
    {
        std::cout << "      Test 3, Crashing 2 Trains together, failed" << std::endl;
        return;
    }
    std::cout << "      Test 3, Crashing 2 Trains together, failed" << std::endl;
}

void TestsOfTrain(void)
{

}