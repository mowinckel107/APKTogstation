#ifndef TRAIN_H
#define TRAIN_H

#include "trainTrack.h"

class TrainTrack;

class Train
{
   public:
        Train(int InputID, TrainTrack * startingTrack);

	private:
		int ID;
		TrainTrack * CurrentTrack;
		

};





#endif /* TRAIN_H */