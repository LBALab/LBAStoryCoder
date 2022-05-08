//---------------------------------------------------------------------------

#ifndef CommandsH
#define CommandsH

#include "SceneLib.h"

typedef struct {
    byte Id;
    short x1, y1, z1, x2, y2, z2;
    int Data;
    char Text[201];
    short cx1, cy1, cx2, cy2;
} TCommand;

//---------------------------------------------------------------------------

void TestConnection();
bool IsConnected();
void close3rdParty();
void BackwardConnection(void *handle);
void reloadGrid(int sceneIdx);
void SendBeginUpdate();
void SendEndUpdate();
void SetTrackCommand(TTrack Track);
void DelTrackCommand(TTrack Track);
void DelTrackCommandByNumbers(int num);
void DelAllTracksCommand();
void SelectTrackCommand(int num);
void SetZoneCommand(TZone Zone,int numZone);
void DelZoneCommand(int numZone);
void DelAllZonesCommand();
void SelectZoneCommand(int numZone);
void SetActorCommand(TActor Actor,int numActor);
void DelActorCommand(int numActor);
void DelAllActorsCommand();
void SetHeroCommand(THero Hero);
void DelHeroCommand();
void SelectActorCommand(int numActor);

#endif
