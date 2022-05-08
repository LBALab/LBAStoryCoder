//---------------------------------------------------------------------------

#include <vcl.h>
#include <assert.h>
#pragma hdrstop

#include "ProjectLib.h"
#include "HQRLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// ----------------
// - Load Routines
// -------------------------------------------------------------------------

TScene loadSceneProject(char* fileName)
{
   TScene Scene;
   FILE * sceneHandle;
   char buffer[256];
   int tmp=0;

   sceneHandle = fopen(fileName,"rt");

   assert(sceneHandle);

   // because the info at beginning
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(!strcmp(buffer,">>>[BEGIN_PROJECT]<<<"));

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(!strcmp(buffer,"[MAIN_SETTINGS]"));

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"TextBank=%d",&Scene.TextBank) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"CubeEntry=%d",&Scene.CubeEntry) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"AlphaLight=%d",&Scene.AlphaLight) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"BetaLight=%d",&Scene.BetaLight) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb0_1=%d",&Scene.Amb0_1) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb0_2=%d",&Scene.Amb0_2) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb0_3=%d",&Scene.Amb0_3) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb1_1=%d",&Scene.Amb1_1) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb1_2=%d",&Scene.Amb1_2) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb1_3=%d",&Scene.Amb1_3) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb2_1=%d",&Scene.Amb2_1) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb2_2=%d",&Scene.Amb2_2) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb2_3=%d",&Scene.Amb2_3) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb3_1=%d",&Scene.Amb3_1) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb3_2=%d",&Scene.Amb3_2) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Amb3_3=%d",&Scene.Amb3_3) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Second_Min=%d",&Scene.Second_Min) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Second_Ecart=%d",&Scene.Second_Ecart) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"CubeMusic=%d",&Scene.CubeMusic) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"[ACTORS num=%d]",&tmp) == 1);

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(!strcmp(buffer,"[OBJECT 0]"));

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"X=%d",&Scene.Hero.X) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Y=%d",&Scene.Hero.Y) == 1);
   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(sscanf(buffer,"Z=%d",&Scene.Hero.Z) == 1);

   Scene.Hero.trackScript = getTrackProjectScript(sceneHandle);
   Scene.Hero.lifeScript = getLifeProjectScript(sceneHandle);

   //----------
   // Actors ----------------------------------------------------

   Scene.numActors = 1;

   if(tmp > 1)
   {

   while(1)
   {
       TActor Actor;
       char buffer2[256];
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;

       sprintf(buffer2,"[OBJECT %d]", Scene.numActors);
       if(strcmp(buffer2,buffer))
           break;

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       sscanf(buffer,"Name=%s",Actor.Name);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"StaticFlags=%d",&Actor.staticFlag)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Entity=%d",&Actor.Entity)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Body=%d",&Actor.Body)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Animation=%d",&Actor.Animation)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"SpriteEntry=%d",&Actor.SpriteEntry)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"X=%d",&Actor.X)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Y=%d",&Actor.Y)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Z=%d",&Actor.Z)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"StrengthOfHit=%d",&Actor.StrengthOfHit)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"BonusParameter=%d",&Actor.BonusParameter)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"BetaAngle=%d",&Actor.Angle)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"SpeedRotation=%d",&Actor.SpeedRotation)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Move=%d",&Actor.Move)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"CropLeft=%d",&Actor.cropLeft)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"CropTop=%d",&Actor.cropTop)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"CropRight=%d",&Actor.cropRight)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"CropBottom=%d",&Actor.cropBottom)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"BonusAmount=%d",&Actor.BonusAmount)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"TalkColor=%d",&Actor.TalkColor)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Armour=%d",&Actor.Armour)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"LifePoints=%d",&Actor.LifePoints)==1);

       Actor.trackScript = getTrackProjectScript(sceneHandle);
       Actor.lifeScript = getLifeProjectScript(sceneHandle);

       Scene.Actors.push_back(Actor);
       Scene.numActors++;
   }

   }

   //---------
   // Zones ----------------------------------------------------

   Scene.numZones = 0;

   if(Scene.numActors == 1){
      fgets(buffer,256,sceneHandle);
      *strchr(buffer,0xA) = 0;
   }

//   assert(!strcmp(buffer,"[ZONES]"));
   assert(sscanf(buffer,"[ZONES num=%d]",&tmp) == 1);

   if(tmp != 0)
   {

   while(1)
   {
       TZone Zone;

       char buffer2[256];
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;

       sprintf(buffer2,"[OBJECT %d]", Scene.numZones);
       if(strcmp(buffer2,buffer))
           break;

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"X0=%d",&Zone.X0)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Y0=%d",&Zone.Y0)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Z0=%d",&Zone.Z0)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"X1=%d",&Zone.X1)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Y1=%d",&Zone.Y1)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Z1=%d",&Zone.Z1)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Type=%d",&Zone.Type)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Info0=%d",&Zone.Info0)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Info1=%d",&Zone.Info1)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Info2=%d",&Zone.Info2)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Info3=%d",&Zone.Info3)==1);

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Snap=%d",&Zone.Snap)==1);

       Scene.numZones++;

       //fgets(buffer,256,sceneHandle);
       //*strchr(buffer,0xA) = 0;

       Scene.Zones.push_back(Zone);
    }

    }

    if(Scene.numZones == 0)
    {
        fgets(buffer,256,sceneHandle);
        *strchr(buffer,0xA) = 0;
    }

   //assert(!strcmp(buffer,"[TRACKS]"));
   assert(sscanf(buffer,"[TRACKS num=%d]",&tmp) == 1);

   Scene.numTracks = 0;

   if(tmp!=0)
   {

   while(1)
   {
       TTrack Track;

       char buffer2[256];
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;

       sprintf(buffer2,"[OBJECT %d]", Scene.numTracks);
       if(strcmp(buffer2,buffer))
           break;

       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"X=%d",&Track.X)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Y=%d",&Track.Y)==1);
       fgets(buffer,256,sceneHandle);
       *strchr(buffer,0xA) = 0;
       assert(sscanf(buffer,"Z=%d",&Track.Z)==1);

       Track.Num = Scene.numTracks;

       Scene.numTracks++;

       Scene.Tracks.push_back(Track);
   }

   }

   return Scene;
}

char* getTrackProjectScript(FILE* sceneHandle)
{
  /* int position = ftell(sceneHandle);
   int position2;  */
   int size = 0;
   char buffer[256];
   int numLine = 0;

   char* ptr = (char*)malloc(1);

   *ptr = 0;

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(!strcmp(buffer,"->[TRACK_SCRIPT]<-"));

   while(1)
   {
       numLine++;
       fgets(buffer,256,sceneHandle);

       size+= strlen(buffer)+1;

       ptr = (char*)realloc(ptr,size);

       strcat(ptr,buffer);

       *strchr(buffer,0xA) = 0;
       if(!strcmp(buffer,"END"))
           break;
   }
   return ptr;
}

char* getLifeProjectScript(FILE* sceneHandle)
{
  /* int position = ftell(sceneHandle);
   int position2;    */
   int size = 0;
   char buffer[256];
   int numLine = 0;

   char* ptr = (char*)malloc(1);

   *ptr = 0;

   fgets(buffer,256,sceneHandle);
   *strchr(buffer,0xA) = 0;
   assert(!strcmp(buffer,"->[LIFE_SCRIPT]<-"));

   while(1)
   {
       numLine++;
       fgets(buffer,256,sceneHandle);

       size+= strlen(buffer)+1;

       ptr = (char*)realloc(ptr,size);

       strcat(ptr,buffer);

       *strchr(buffer,0xA) = 0;
       if(!strcmp(buffer,"END"))
           break;
   }
   return ptr;
}

// ----------------
// - Save Routines
// -------------------------------------------------------------------------

void saveSceneProject(TScene Scene, char * fileName)
{
   char buffer[100000];

   FILE * sceneHandle;
   sceneHandle = fopen(fileName,"wt");

//   fseek(sceneHandle, SEEK_SET, 0);

   fputs("This is LBA Story Coder project file. Don't mess this file if you don't know what your doing.\n",sceneHandle);

   fputs(">>>[BEGIN_PROJECT]<<<\n",sceneHandle);

   fputs("[MAIN_SETTINGS]",sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"TextBank=%d",Scene.TextBank);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"CubeEntry=%d",Scene.CubeEntry);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"AlphaLight=%d",Scene.AlphaLight);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"BetaLight=%d",Scene.BetaLight);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb0_1=%d",Scene.Amb0_1);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb0_2=%d",Scene.Amb0_2);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb0_3=%d",Scene.Amb0_3);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb1_1=%d",Scene.Amb1_1);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb1_2=%d",Scene.Amb1_2);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb1_3=%d",Scene.Amb1_3);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb2_1=%d",Scene.Amb2_1);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb2_2=%d",Scene.Amb2_2);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb2_3=%d",Scene.Amb2_3);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb3_1=%d",Scene.Amb3_1);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb3_2=%d",Scene.Amb3_2);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Amb3_3=%d",Scene.Amb3_3);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Second_Min=%d",Scene.Second_Min);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"Second_Ecart=%d",Scene.Second_Ecart);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"CubeMusic=%d",Scene.CubeMusic);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"[ACTORS num=%d]",Scene.numActors);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   fputs("[OBJECT 0]",sceneHandle);
   fputs("\n",sceneHandle);

   sprintf(buffer,"X=%d",Scene.Hero.X);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);
   sprintf(buffer,"Y=%d",Scene.Hero.Y);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);
   sprintf(buffer,"Z=%d",Scene.Hero.Z);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   fputs("->[TRACK_SCRIPT]<-",sceneHandle);
   fputs("\n",sceneHandle);
   sprintf(buffer,Scene.Hero.trackScript);
   fputs(buffer,sceneHandle);

   fputs("->[LIFE_SCRIPT]<-",sceneHandle);
   fputs("\n",sceneHandle);
   sprintf(buffer,Scene.Hero.lifeScript);
   fputs(buffer,sceneHandle);

   //----------
   // Actors ----------------------------------------------------


   for(int a=0;a<Scene.numActors-1;a++)
   {
       sprintf(buffer,"[OBJECT %d]", a+1);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Name=%s",Scene.Actors[a].Name);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"StaticFlags=%d",Scene.Actors[a].staticFlag);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Entity=%d",Scene.Actors[a].Entity);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Body=%d",Scene.Actors[a].Body);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Animation=%d",Scene.Actors[a].Animation);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"SpriteEntry=%d",Scene.Actors[a].SpriteEntry);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"X=%d",Scene.Actors[a].X);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Y=%d",Scene.Actors[a].Y);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Z=%d",Scene.Actors[a].Z);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"StrengthOfHit=%d",Scene.Actors[a].StrengthOfHit);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"BonusParameter=%d",Scene.Actors[a].BonusParameter);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"BetaAngle=%d",Scene.Actors[a].Angle);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"SpeedRotation=%d",Scene.Actors[a].SpeedRotation);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Move=%d",Scene.Actors[a].Move);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"CropLeft=%d",Scene.Actors[a].cropLeft);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"CropTop=%d",Scene.Actors[a].cropTop);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"CropRight=%d",Scene.Actors[a].cropRight);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"CropBottom=%d",Scene.Actors[a].cropBottom);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"BonusAmount=%d",Scene.Actors[a].BonusAmount);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"TalkColor=%d",Scene.Actors[a].TalkColor);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Armour=%d",Scene.Actors[a].Armour);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"LifePoints=%d",Scene.Actors[a].LifePoints);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       fputs("->[TRACK_SCRIPT]<-",sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,Scene.Actors[a].trackScript);
       fputs(buffer,sceneHandle);
       fputs("->[LIFE_SCRIPT]<-",sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,Scene.Actors[a].lifeScript);
       fputs(buffer,sceneHandle);
   }
                             
   //---------
   // Zones ----------------------------------------------------

   sprintf(buffer,"[ZONES num=%d]",Scene.numZones);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   for(int a=0; a < Scene.numZones; a++)
   {
       sprintf(buffer,"[OBJECT %d]", a);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"X0=%d",Scene.Zones[a].X0);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Y0=%d",Scene.Zones[a].Y0);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Z0=%d",Scene.Zones[a].Z0);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"X1=%d",Scene.Zones[a].X1);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Y1=%d",Scene.Zones[a].Y1);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Z1=%d",Scene.Zones[a].Z1);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Type=%d",Scene.Zones[a].Type);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Info0=%d",Scene.Zones[a].Info0);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Info1=%d",Scene.Zones[a].Info1);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Info2=%d",Scene.Zones[a].Info2);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Info3=%d",Scene.Zones[a].Info3);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"Snap=%d",Scene.Zones[a].Snap);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
   }

   sprintf(buffer,"[TRACKS num=%d]",Scene.numTracks);
   fputs(buffer,sceneHandle);
   fputs("\n",sceneHandle);

   for(int a=0;a<Scene.numTracks;a++)
   {
       sprintf(buffer,"[OBJECT %d]", a);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);

       sprintf(buffer,"X=%d",Scene.Tracks[a].X);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Y=%d",Scene.Tracks[a].Y);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
       sprintf(buffer,"Z=%d",Scene.Tracks[a].Z);
       fputs(buffer,sceneHandle);
       fputs("\n",sceneHandle);
   }

   fputs(">>>[END_PROJECT]<<<\n",sceneHandle);

   fclose(sceneHandle);
}
 