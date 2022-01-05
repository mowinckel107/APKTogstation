#include "trainFunctor.h"
#include "common.h"
#include <iostream>

// Setup
TrainFunctor::TrainFunctor(int ownerTrainID)
{   
    ownerTrainID_ = ownerTrainID;
}

// Clear reservation
bool TrainFunctor::operator()()
{
    reservedID_ = -1;
    return true;
}

// Reserve track {trackID}
bool TrainFunctor::operator()(int trackID)
{   
    reservedID_ = trackID;

    return true;    
}

// Some train is requesting track {TrackID}
bool TrainFunctor::operator()(bool isRequest, int trackID)
{
    // I am currently sitting on this ID
    if (reservedID_ == trackID)
    {
        return true;
    }
    // I am not in the way
    else
    {
        return false;
    }
}

// Debugging
/*
bool TrainFunctor::operator()(bool a, bool b)
{
    if (a && b)
    {
        return (ownerTrainID_ > 0);
    }
    else if (!a && !b)
    {
        return (reservedID_ > 0);
    }
    return false;
}
*/