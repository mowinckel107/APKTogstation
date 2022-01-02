#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"
#include "trainFunctor.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <iostream> 

class Train
{
   public:
        Train
		(
			int ID,
			std::vector<int> route,
			TrainTrack * startingTrack
			ControlTowerFunctor * control
		);
		
		~Train();
		void StartDriveLoop(void);
		int GetID(void);

		TrainFunctor trainFunctor_;

	private:
		int ID_;
		bool ControlTowerManagerMode;
		TrainTrack * currentTrack_;
		ControlTowerFunctor * control_;
		std::vector<int> route_;
    	boost::signals2::signal<void (int)> leavingSignal_;
    	boost::signals2::signal<bool (int)> isTrainTrackOccupiedSignal_;
		boost::signals2::signal<void (trackConnectionMap)> birthSignal_;
		bool isNotDeleted_ = true;
};


#endif /* TRAIN_H */