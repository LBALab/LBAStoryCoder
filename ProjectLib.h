//---------------------------------------------------------------------------

#ifndef ProjectLibH
#define ProjectLibH

//#include <stdio.h>
//#include <vector>
#include <fstream.h>
#include "SceneLib.h"

//---------------------------------------------------------------------------

TScene loadSceneProject(char * fileName);
char* getTrackProjectScript(FILE* sceneHandle);
char* getLifeProjectScript(FILE* sceneHandle);
void saveSceneProject(TScene Scene, char * fileName);

#endif
