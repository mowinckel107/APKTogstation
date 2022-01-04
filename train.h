#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"
#include "trainFunctor.h"
#include "controlTowerFunctor.h"
#include "common.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <iostream> 

// compiler seems to be weird with circular includes
class TrainTrack;
class ControlTowerFunctor;

class Train
{
   public:
		Train
		(
			int ID,
			TrainTrack * startingTrack,
			ControlTowerFunctor * control,
		    std::mutex * inmut
		);
		
		~Train();
		std::thread start(std::mutex * inmut);
		int startDriveLoop();
		int getID(void);

		TrainFunctor trainFunctor_;
		bool isNotDeleted_ = true;

	private:
		std::mutex * inmut_;
		int ID_;
		bool controlTowerManagerMode_;
		TrainTrack * currentTrack_;
		ControlTowerFunctor * control_;
		std::vector<int> route_;
    	occupiedSignalType isTrainTrackOccupiedSignal_;
};

#endif /* TRAIN_H */