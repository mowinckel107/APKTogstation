#ifndef TRAIN_H
#define TRAIN_H



class Train
{

/*   public:
		int ID; // Id på vogne
		Container * ContainerOnTrain; // Olie, livestock, andet?
		TrainTrack * CurrentTrack; // Hvis toget selv skal kunne køre nogen steder, må det nødvendigvis have en pointer til nuværende SPOR.
		Instruction * CurrentInstruction; // Instruction er et fælles interface mellem TOG og KONTROLHUS.
			// Instruction:
			// TrainTrack * TakeOffPoint;
			// TrainTrack * ArrivalPoint;
            // TrainTrack * BlockedPoints; // .. så den ikke kører baglens
			// int TrainTrackCount;
			// uint64 TakeOffTime;
			// uint64 ArrivalTime;


        Train(); // Opret tog og vent på yderligere instruktioner.

		Train(int inputID, TrainTrack * Track = nullptr); // Opret tog. Hvis der følger et track med, kør ind på det.

		void SetInstruction(Instruction * Ins); // Kaldes fra KONTROLHUS, ind til vi har noget med SIGNAL kørende.

		bool GetInstruction(ControlTower * CT); // Anmoder KONTROLHUS om instruktioner. Denne ERSTATTER RequestTrack()

		void MoveTrack(TrainTrack * Track); // Kør til næste SPOR. Dvs. fortæl afgangs og ankomst spor at vi henholdsvis skrider og ankommer
                                                      // (og få at vide hvis vi er døde i en forfærdelig ulykke).
                                                      // Bemærk ny parameter.

        void Drive(); // Følg instruktioner.
*/ 
};




#endif /* TRAIN_H */