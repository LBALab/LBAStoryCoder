//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Commands.h"

extern TCommand * Command;
extern THandle * ComHandle;

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TestConnection()
{
   Command = (TCommand *)MapViewOfFile(ComHandle,FILE_MAP_ALL_ACCESS,0,0,0);
   Command->Code = 1;
   Command->Sent = True;

    Sleep(2000);

   if(Command->Code == 0)
        ShowMessage("Comunication OK");
   else
        ShowMessage("Comunication Time Out");

   UnmapViewOfFile(Command);
}

bool IsConnected()
{
   Command = (TCommand *)MapViewOfFile(ComHandle,FILE_MAP_ALL_ACCESS,0,0,0);
   Command->Code = 1;
   Command->Sent = True;
   Sleep(20);

   if(Command->Code == 0){
        UnmapViewOfFile(Command);
        return true;
   }
   UnmapViewOfFile(Command);
   return false;
}

void SetTrackCommand(TTrack Track)
{
    AnsiString tmp;
    Command = (TCommand *)MapViewOfFile(ComHandle,FILE_MAP_ALL_ACCESS,0,0,0);
    Command->Code = 2;
    Command->Id = Track.Num;
    Command->x1 = Track.X;
    Command->y1 = Track.Y;
    Command->z1 = Track.Z;
    Command->x2 = 0; // unused
    Command->y2 = 0; // unused
    Command->z2 = 0; // unused
    tmp = "Track ";
    tmp += Track.Num;
    strcpy(Command->Text,tmp.c_str());
    Command->Sent = True;
    UnmapViewOfFile(Command);
}
