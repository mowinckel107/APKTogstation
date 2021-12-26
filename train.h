#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio.hpp>

class TrainTrack;

class Train
{
   public:
        Train(int InputID, std::vector<int> Route, TrainTrack * startingTrack);
		~Train();
		void StartDriveLoop(void);


	private:
		int ID;
		TrainTrack * CurrentTrack;
		std::vector<int> route;
		int progressAlongRoute;
		bool isNotDeleted = true;
};





#endif /* TRAIN_H */