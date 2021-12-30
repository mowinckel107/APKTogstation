
#include "trainTrack.h"
#include "train.h"
#include "controlTower.h"
#include "container.h"

#include <vector>
#include <iostream>

#include "tests.h"


int main()
{
    //RunTests(); // Uncomment/Comment to run/not run the tests
    Container<cold, liquid> water("water");

    std::cout << water.seeCargo() << std::endl;

    return 0;
}







