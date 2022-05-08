//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Commands.h"

//extern TCommand * Command;
//extern THandle * ComHandle;

extern void *wh;
extern THandle * Handle;
extern TCommand Command;

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TestConnection()
{
    int a;
    TCopyDataStruct temp;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 01;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;

    a = SendMessage(wh,WM_COPYDATA,0,(int)&temp);
    if (a == 1000)
        MessageBox(Handle,"Communication OK!","",MB_ICONINFORMATION+MB_OK);
    else
        MessageBox(Handle,"Comm Error!","",MB_ICONERROR+MB_OK);
}

bool IsConnected()
{
    int a;
    TCopyDataStruct temp;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 01;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;

    a = SendMessage(wh,WM_COPYDATA,0,(int)&temp);
    if (a == 1000)
        return true;

    return false;
}

void close3rdParty()
{
    TCopyDataStruct temp;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 03;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;
    SendMessage(wh,WM_CLOSE,0,(int)&temp);
}

void BackwardConnection(void *handle)
{
    TCopyDataStruct temp;

    Command.Data = (int)handle;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 04;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;
    SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void reloadGrid(int sceneIdx)
{
   TCopyDataStruct temp;

   Command.Id = 1; // LBA1 only for now
   Command.Data = sceneIdx;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 02;
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SendBeginUpdate()
{
    TCopyDataStruct temp;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 8;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;
    SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SendEndUpdate()
{
    TCopyDataStruct temp;

    wh = FindWindow(0,"Little Grid Builder - Scene Mode");
    temp.dwData = 9;
    temp.cbData = sizeof(TCommand);
    temp.lpData = &Command;
    SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SetTrackCommand(TTrack Track)
{
   AnsiString tmp;
   TCopyDataStruct temp;

   Command.Id = Track.Num;
   Command.x1 = Track.X;
   Command.y1 = Track.Y;
   Command.z1 = Track.Z;
   Command.x2 = 0;
   Command.y2 = 0;
   Command.z2 = 0;
   tmp = "";
   tmp = tmp + Track.Num;
   strcpy(Command.Text,tmp.c_str());

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 11;  // set
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelTrackCommand(TTrack Track)
{
   TCopyDataStruct temp;

   Command.Id = Track.Num;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 12; // delete
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelTrackCommandByNumbers(int num)
{
   TCopyDataStruct temp;

   Command.Id = num;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 12; // delete
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelAllTracksCommand()
{
   TCopyDataStruct temp;

   Command.Id = 0;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 13; // delete all
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SelectTrackCommand(int num)
{
   TCopyDataStruct temp;

   Command.Id = num;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 14; // select
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SetZoneCommand(TZone Zone,int numZone)
{
   AnsiString tmp;
   TCopyDataStruct temp;

   Command.Id = numZone;
   Command.x1 = Zone.X0;
   Command.y1 = Zone.Y0;
   Command.z1 = Zone.Z0;
   Command.x2 = Zone.X1;
   Command.y2 = Zone.Y1;
   Command.z2 = Zone.Z1;
   Command.Data = Zone.Type;
   tmp = "";
   tmp = tmp + numZone;
   strcpy(Command.Text,tmp.c_str());

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 21;  // set
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelZoneCommand(int numZone)
{
   TCopyDataStruct temp;

   Command.Id = numZone;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 22; // delete
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelAllZonesCommand()
{
   TCopyDataStruct temp;

   Command.Id = 0;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 23; // delete all
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SelectZoneCommand(int numZone)
{
   TCopyDataStruct temp;

   Command.Id = numZone;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 24; // select
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SetActorCommand(TActor Actor,int numActor)
{
   AnsiString tmp;
   TCopyDataStruct temp;

   Command.Id = numActor;
   Command.x1 = Actor.X;
   Command.y1 = Actor.Y;
   Command.z1 = Actor.Z;
   Command.x2 = 0;
   Command.y2 = 0;
   Command.z2 = 0;
   if(Actor.staticFlag & 0x400) // is Sprite Actor
   {
      Command.Data = Actor.SpriteEntry+1;
      if(Actor.staticFlag & 0x8)
      {
            Command.cx1 = Actor.cropLeft;
            Command.cy1 = Actor.cropTop;
            Command.cx2 = Actor.cropRight;
            Command.cy2 = Actor.cropBottom;
      }
   }
   else
      Command.Data = 0;
   tmp = "";
   tmp = tmp + numActor;
   strcpy(Command.Text,tmp.c_str());

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 31;  // set
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelActorCommand(int numActor)
{
   TCopyDataStruct temp;

   Command.Id = numActor;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 32; // delete
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelAllActorsCommand()
{
   TCopyDataStruct temp;

   Command.Id = 0;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 33; // delete all
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SetHeroCommand(THero Hero)
{
   AnsiString tmp;
   TCopyDataStruct temp;

   Command.Id = 0;
   Command.x1 = Hero.X;
   Command.y1 = Hero.Y;
   Command.z1 = Hero.Z;
   Command.x2 = 0;
   Command.y2 = 0;
   Command.z2 = 0;
   Command.Data = 0;
   tmp = "0";
   strcpy(Command.Text,tmp.c_str());

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 31;  // set
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void DelHeroCommand()
{
   TCopyDataStruct temp;

   Command.Id = 0;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 32; // delete
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}

void SelectActorCommand(int numActor)
{
   TCopyDataStruct temp;

   Command.Id = numActor;

   wh = FindWindow(0,"Little Grid Builder - Scene Mode");
   temp.dwData = 34; // select
   temp.cbData = sizeof(TCommand);
   temp.lpData = &Command;
   SendMessage(wh,WM_COPYDATA,0,(int)&temp);
}
