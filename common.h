#ifndef COMMON_H
#define COMMON_H

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

// Combiner
template<typename T>
struct BoolCombOR
{
    typedef T result_type;

    template<typename T2>
	T operator()(T2 first, T2 last) const
	{
        T status = false;

        while (first != last)
        {
            status = (status || *first);
            first++;
        }

		return status;
	}
};

// https://stackoverflow.com/questions/10752844/signals-and-binding-arguments
// Generate slot types for slots so that we can have placeholder argyments
typedef boost::signals2::signal<bool (int), BoolCombOR<bool>> occupiedSignalType;
typedef occupiedSignalType::slot_type isTrainOccupiedSignalBind;

using vectorOfConnections = std::vector<boost::signals2::connection>;
using trackConnectionMap = std::map<int, vectorOfConnections>;
using trainTrackConnectionMap = std::map<int, trackConnectionMap>;

// Functor wrapper
template <typename DATA, typename INPUT, typename OUTPUT, typename FUNCTORTYPE>
struct FunctorWrapper
{
    FUNCTORTYPE * func_;
    DATA data_;

    FunctorWrapper(FUNCTORTYPE * func, DATA data) : func_(func), data_(data) { } 

    OUTPUT operator()(INPUT input)
    {
        return (*func_)(data_, input);
    }
};

// Communication
struct TrainCommunicationAndRoute
{
    occupiedSignalType isTrainTrackOccupiedSignal_;
    std::vector<int> route_;
};

struct TrainTracker
{
    occupiedSignalType * isTrainTrackOccupiedSignal_;
};

using RouteVector = std::vector<std::vector<int>>;

#endif /* COMMON_H */