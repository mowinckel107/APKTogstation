

#include "train.h"


Train::Train()
{
    ID = 0;
    CurrentTrack = nullptr;
}

Train::Train(int InputID, TrainTrack * Track)
{
    ID = InputID;
    CurrentTrack = nullptr;

    if (Track != nullptr)
    {
        MoveTrack(Track);
    }
}

void Train::SetInstruction(Instruction * Ins)
{
    CurrentInstruction = Ins;
    // det er IKKE mit problem at destruere brugte instruktioner
}

bool Train::GetInstruction(ControlTower * CT)
{
    // pseudokode:
        // Kald metode på kontrolhus og angiv ID eller this.
        // returnerer hvad end metoden på kontrolhus returnerer.
}

void Train::Drive()
{
    // pseudokode:
        // Notér tracks vi kan køre til, som ikke er blokerede
        // Notér tracks endestation kan køre til
        // Loop igennem dem ind og find alle ruter imellem dem
        // Notér den korteste
        // Beregn hvornår toget skal afsted til næste punkt på ruten
        // Notér næste punkt på ruten, NextTrack

        // HVIS tidTilAtKøre
            // MoveTrack(NextTrack)
}

void Train::MoveTrack(TrainTrack * Track)
{
    try
    {
        Track->EnterTrainTracks(this);
    }
    catch (const char* msg)
    {
        if(static_cast<std::string>(msg) == "A train crashed into another train")
        {
            // do something ...
            return;
        }
    }

    if (CurrentTrack != nullptr)
    {
        Track->LeaveTrainTrack();
    }

    CurrentTrack = Track;

}
