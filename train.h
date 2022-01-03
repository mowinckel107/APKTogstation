#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"
#include "trainFunctor.h"
#include "controlTowerFunctor.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <iostream> 

// https://stackoverflow.com/questions/10752844/signals-and-binding-arguments
// Generate slot types for slots so that we can have placeholder argyments
typedef boost::signals2::signal<bool (int)> leavingSignalType;
typedef leavingSignalType::slot_type leavingSignalBind;
typedef boost::signals2::signal<bool (int)> occupiedSignalType;
typedef occupiedSignalType::slot_type isTrainOccupiedSignalBind;

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
			ControlTowerFunctor * control
		);
		
		~Train();
		void start(void);
		int startDriveLoop(void);
		int getID(void);

		TrainFunctor trainFunctor_;
		bool isNotDeleted_ = true;

	private:
		int ID_;
		bool controlTowerManagerMode_;
		TrainTrack * currentTrack_;
		ControlTowerFunctor * control_;
		std::vector<int> route_;
    	boost::signals2::signal<bool (int)> leavingSignal_;
    	boost::signals2::signal<bool (int)> isTrainTrackOccupiedSignal_;
		boost::signals2::signal<bool (trackConnectionMap)> birthSignal_;
};


#endif /* TRAIN_H */