
#include "trainTrack.h"
#include "train.h"
#include "controlTower.h"
#include "container.h"
#include "setup.h"


#include <vector>
#include <iostream>

#include "tests.h"


int main()
{
    //RunTests(); // Uncomment/Comment to run/not run the tests
    Container<cold, liquid> water("water");

    std::cout << water.seeCargo() << std::endl;

    water.removeCargo();

    std::cout << water.seeCargo() << std::endl;

    water.addCargo("water");

    std::cout << water.seeCargo() << std::endl;
    TrainTrackHolder TheTrainTracks;

    return 0;
}







