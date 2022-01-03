#include "tests.h"




void TestsOfTrainTrack1(void);
void TestsOfTrainTrack2(void);
void TestsOfTrainTrack3(void);


void TestsOfTrain1(void);
void TestsOfTrain2(void);



void RunTests(void)
{
    std::cout << "Starting tests of TrainTrack:" << std::endl;
    TestsOfTrainTrack1();
    TestsOfTrainTrack2();
    TestsOfTrainTrack3();

    std::cout << "Starting tests of Train" << std::endl;
    TestsOfTrain1();
    TestsOfTrain2();
}

void TestsOfTrainTrack1(void)
{
    // Test 1, Linking 2 TrainTracks
    try
    {
    // Step 1: Arrange

    // Give TrainTrack2 an empty map, as it leads to no other TrainTracks
    std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainTrack2;

    TrainTrack myTrainTrack2(emptyListOfTrainTracksForTrainTrack2, 2);

    // Step 2: Act

    // Give TrainTrack1 a map only containing ID and pointer to TrainTrack2
    std::map<int, TrainTrack*> listOfTrainTracksForTrainTrack1;
    listOfTrainTracksForTrainTrack1.insert(std::make_pair(myTrainTrack2.GetID(),&myTrainTrack2));

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
        // Control tower
        ControlTowerFunctor Tower(false);

        // Step 1: Arrange

        // Give TrainTrack2 an empty map, as it leads to no other TrainTracks
        std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainTrack2;
        TrainTrack myTrainTrack2(emptyListOfTrainTracksForTrainTrack2, 2);

        // Give TrainTrack1 a map only containing a pointer to TrainTrack2
        std::map<int, TrainTrack*> listOfTrainTracksForTrainTrack1;
        listOfTrainTracksForTrainTrack1.insert(std::make_pair(myTrainTrack2.GetID(),&myTrainTrack2));

        TrainTrack myTrainTrack1(listOfTrainTracksForTrainTrack1, 1);

        std::vector<int> routeForMyTrain{2};

        // Create Train to use for exercising TrainTracks
        Train myTrain(0, nullptr, &Tower);

        // Variable to hold pointer to nextTrainTrack instead of controlTower or train
        TrainTrack * nextTrainTrack;


        // Step 2: Act

        myTrainTrack1.EnterTrainTracks(&myTrain);
        nextTrainTrack = myTrainTrack1.GetNextTrainTrack(2);
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
        // Control tower
        ControlTowerFunctor Tower(false);

        // Step 1: Arrange

        // Give myTrainTrack an empty map, as it leads to no other TrainTracks
        std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainTrack;
        TrainTrack myTrainTrack(emptyListOfTrainTracksForTrainTrack, 0);

        std::vector<int> EmptyTrainRoute;

        // Create Trains to use for exercising TrainTracks
        Train myTrain1(0, nullptr, &Tower);
        Train myTrain2(1, nullptr, &Tower);

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


void TestsOfTrain1(void)
{
        // Test 1, Creating train on TrainTrack
    try
    {
        // Control tower
        ControlTowerFunctor Tower(false);

        // Step 1: Arrange
        // Give TrainTrack an empty map, as it leads to no other TrainTracks
        std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainTrack;
        TrainInput myTrainTrack(emptyListOfTrainTracksForTrainTrack, 0);

        // Step 2: Act
        // Create Train with an empty route
        std::vector<int> TrainRoute{};
        Train myTrain(0, &myTrainTrack, &Tower);
    
        // Step 3: Assert
    }
    catch(...)
    {
        std::cout << "      Test 1, Creating train on TrainTrack, failed" << std::endl;
    }

        std::cout << "      Test 1, Creating train on TrainTrack, succeeded" << std::endl;
}

void TestsOfTrain2(void)
{
    // Test 2, Running infinite loop
    try
    {
        // Control tower
        ControlTowerFunctor Tower(false);

        // Step 1: Arrange
            // Give TrainTrack2 an empty map, as it leads to no other TrainTracks
            std::map<int, TrainTrack*> emptyListOfTrainTracksForTrainTrack2;
            TrainInput myTrainTrack2(emptyListOfTrainTracksForTrainTrack2, 2);

            // Give TrainTrack1 a map only containing a pointer to TrainTrack2
            std::map<int, TrainTrack*> listOfTrainTracksForTrainTrack1;
            listOfTrainTracksForTrainTrack1.insert(std::make_pair(myTrainTrack2.GetID(),&myTrainTrack2));

            TrainTrack myTrainTrack1(listOfTrainTracksForTrainTrack1, 1);

            // Create Train with route on TrainTrack1
            std::vector<int> TrainRoute{2};
            Train *myTrain = new Train(0, &myTrainTrack1, &Tower);

        // Step 2: Act

        myTrain->StartDriveLoop();
        
        // Step 3: Assert
    }
    catch(const char* msg)
    {
        std::cout << "      Test 2, Running infinite loop, failed" << std::endl;
        std::cout << "      " << msg << std::endl;
    }
    catch(...)
    {
        std::cout << "      Test 2, Running infinite loop, failed" << std::endl;
    }

    std::cout <<"      Test 2, Running infinite loop, succeeded" << std::endl;
}