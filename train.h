#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <iostream> 

class TrainTrack;


class Train
{
   public:
        Train
		(
			int InputID,
			std::vector<int> Route,
			TrainTrack * startingTrack,
			boost::signals2::signal<void ()> * inputLeavingSignal,
			boost::signals2::signal<bool ()> * inputIsTrainTrackOccupiedSignal
		);
		
		~Train();
		void StartDriveLoop(void);
		int GetID(void);


	private:
		int ID;
		TrainTrack * CurrentTrack;
		std::vector<int> route;
		int progressAlongRoute;
    	boost::signals2::signal<void ()> * leavingTrainTrackSignal;
    	boost::signals2::signal<bool ()> * wantToEnterTrainTrackSignal;
		bool isNotDeleted = true;
};





#endif /* TRAIN_H */