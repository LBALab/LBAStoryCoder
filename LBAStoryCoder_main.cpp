/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004-2006
---------------------------[ ActorScriptEd.cpp ]-----------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Sun Jul 15 2005
Email : alexandrefontoura@oninetspeed.pt

-------------------------------[ GNU License ]-------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-----------------------------------------------------------------------------
*/

#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "LBAStoryCoder_main.h"
#include "about.h"
#include "Settings.h"
#include "SceneLib.h"
#include "StaticParameters.h"
#include "ActorScriptEd.h";
#include "ScriptHelp.h";
#include "Entities.h";
#include "Commands.h";
#include "CoderCommands.h"
#include "ProjectLib.h"
#include "DisplayActor.h"
#include "SelectScenes.h"
#include "SelectGrid.h"
#include "BatchSaving.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma link "CSPIN"
#pragma link "rsComboSpinEdit"
#pragma link "ehsbase"
#pragma link "ehscontextmap"
#pragma link "ehswhatsthis"
#pragma resource "*.dfm"
Tfrm_lba *frm_lba;

unsigned char palette[3*256];
int filesize;
int sceneIdx;
int tmp; // with scene number to open in Builder
AnsiString programPath;
AnsiString Path;
AnsiString bodyDescPath;
AnsiString bodyPath;
AnsiString animPath;
AnsiString spriteDescPath;
AnsiString sprite2DescPath;
AnsiString spritePath;
AnsiString builderPath;
AnsiString entitiesPath;
AnsiString modelViewerPath;
AnsiString spriteViewerPath;
AnsiString helpPath;

extern AnsiString lastScene;
extern AnsiString lastLoadDir;
extern AnsiString lastSaveDir;
extern bool displayRoom;
extern bool stayOnTop;
extern bool lastSceneCheck;
extern vector<AnsiString> recentPath;

TScene Scene;
bool isLBA2 = false;
bool canMove = false;

String vnum = "0.5.0";

vector<TColor> TPalette;
extern unsigned short value;



void *wh;
TCommand Command;
THandle * Handle;

int countTime;

entitiesTableStruct* entitiesStruct;

int gridConv[223] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,0,0,0,0,0,0,0,0,0,44,45,46,47,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,48,49,50,51,52,53,54,55,56,0,0,0,0,0,0,57,0,0,0,0,0,0,58,59,0,0,60,0,61,0,0,0,0,62,63,64,65,66,67,68,69,70,0,71,72,73,74,75,76,77,78,79,0,0,0,80,81,82,83,84,0,85,86,87,88,89,0,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,0,126,127,128,129,130,131,132,133,134,135,136,137,0,137,138,139,140,0,0,0,0,0,0,141,0,0,0,0,142,0,143,0,0,0,144,145,0,146,147,0,148,149};

int canOpen=0;

//---------------------------------------------------------------------------
__fastcall Tfrm_lba::Tfrm_lba(TComponent* Owner)
        : TForm(Owner)
{
   //frm_lba->Caption = frm_lba->Caption + vnum;
   // frm_lba->Caption = frm_lba->Caption + " by alexfont";
   edt_angle->Text = "0 \xB0";

   // load palette to the array
   loadPaletteFromResource();
   // get program directory
   programPath = ExtractFileDir(Application->ExeName);
   helpPath = programPath + "\\help\\StoryCoderHelpProject.hlp";
   // get data paths
   bodyDescPath = programPath + "\\data\\file3d.dat";
   spriteDescPath = programPath + "\\data\\sprites.dat";
   sprite2DescPath = programPath + "\\data\\sprites2.dat";

   Application->HelpFile = helpPath;

   // get config.ini file
   if(frm_settings->loadSettings())
       ShowMessage("Please configure the program in [View]->[Settings] menu for a properly work. Thanks!!");

   if(!entitiesPath.IsEmpty())
      entitiesStruct = parseEntities();

   
    if(stayOnTop)
        frm_lba->FormStyle = fsStayOnTop;
    else
        frm_lba->FormStyle = fsNormal;

    // open last file at startup or by parameter
    if(ParamCount()>0){
       canOpen = 1;
       AnsiString *xis = new AnsiString(ParamStr(1));
       Path = *xis;
    }
    else if(lastSceneCheck){
       if(!lastScene.IsEmpty())
       {
          canOpen = 2;
          Path = lastScene;
       }
    }else {
       canOpen = 0;
       Path = "";
    }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_lba::FormShow(TObject *Sender)
{
   // load files at startup
   if(canOpen!=0){
     canOpen = 0; // block this code to be open when the form will be showed
     if(checkResource(Path.c_str()))
     {
        if(StrPos(LowerCase(Path).c_str(),".scp")){  // LBA Story Coder Project
            isLBA2 = false;
            Scene = loadSceneProject(Path.c_str());
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
            lastScene = Path;
        }
        else if(StrPos(LowerCase(Path).c_str(),".ls1")){  // LBA1 Binary mode
            isLBA2 = false;
            sceneIdx = -1;
            Scene = loadBinaryScene(Path.c_str(),sceneIdx);
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
            lastScene = Path;
        }
        else if(StrPos(LowerCase(Path).c_str(),".sce")){ // LBA1 Text mode
            isLBA2 = false;
            Scene = loadTextScene(Path.c_str());
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
            lastScene = Path;
        }
        else if(StrPos(LowerCase(Path).c_str(),".ls2")){  // LBA2 binary mode
            isLBA2 = true;
            sceneIdx = -1;
            Scene = loadBinaryScene2(Path.c_str(),sceneIdx);
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
            lastScene = Path;
        }
        else if(StrPos(LowerCase(Path).c_str(),"scene.hqr")){  // LBA1 HQR Binary mode
            if(getNumEntries(Path.c_str()) == 120) // LBA1 scenes
              isLBA2 = false;
            else if(getNumEntries(Path.c_str()) == 223) // LBA2 scenes
              isLBA2 = true;
            frm_selectroom->ShowModal();
        }
        else
            ShowMessage("This program doens't support this file!");
      }
      else {
          String s = Path;
	        ShowMessage(s + " couldn't be found!");
          lastScene = "";
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::FormCreate(TObject *Sender)
{
    DragAcceptFiles(Handle,true);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::FormDestroy(TObject *Sender)
{
    DragAcceptFiles(Handle,false);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::FormClose(TObject *Sender, TCloseAction &Action)
{
   frm_settings->saveSettings();

   close3rdParty(); // Close Builder.exe by Zink

   if(frm_actorscript->Showing)
      frm_actorscript->Close();
   if(frm_staticpar->Showing)
      frm_staticpar->Close();
   if(frm_scripthelp->Showing)
      frm_scripthelp->Close();
}
//---------------------------------------------------------------------------
MESSAGE void Tfrm_lba::DropFile(TMessage &Message)
{
   char buffer[256];
   DragQueryFile((HDROP) Message.WParam,0,buffer,256); // 0 means one file dragged
   DragFinish((HDROP) Message.WParam);
                  
   lastScene = "";

   close3rdParty(); // Close Builder.exe by Zink

   if(frm_actorscript->Showing)
      frm_actorscript->Close();
   if(frm_staticpar->Showing)
      frm_staticpar->Close();
   if(frm_scripthelp->Showing)
      frm_scripthelp->Close();

   clearScene();

   AnsiString *xis = new AnsiString(buffer);
   Path = *xis;
   delete xis;

   DelAllTracksCommand();
   DelAllZonesCommand();
   DelAllActorsCommand();

   if(StrPos(LowerCase(Path).c_str(),".scp")){  // LBA Story Coder Project
            isLBA2 = false;
            Scene = loadSceneProject(Path.c_str());
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
                lastScene = Path;
            }
        }
   else if(StrPos(LowerCase(Path).c_str(),".ls1")){
        isLBA2 = false;
        sceneIdx = -1;
        Scene = loadBinaryScene(Path.c_str(),sceneIdx);
        if(filesize!=-1){
            putInitScene();
            bt_reload->Enabled = True;
            menu_reload->Enabled = True;
            bt_close->Enabled = True;
            menu_close->Enabled = True;
            bt_save->Enabled = True;
            menu_save->Enabled = True;
            bt_saveas->Enabled = True;
            menu_saveas->Enabled = True;
            menu_builder->Enabled = True;
            pl_scene->Visible = True;
            lastScene = Path;
        }
   }
   else if(StrPos(LowerCase(Path).c_str(),".sce"))
   {
        isLBA2 = false;
        Scene = loadTextScene(Path.c_str());
        if(filesize!=-1){
            putInitScene();
            bt_reload->Enabled = True;
            menu_reload->Enabled = True;
            bt_close->Enabled = True;
            menu_close->Enabled = True;
            bt_save->Enabled = True;
            menu_save->Enabled = True;
            bt_saveas->Enabled = True;
            menu_saveas->Enabled = True;
            menu_builder->Enabled = True;
            pl_scene->Visible = True;
            lastScene = Path;
        }
   }
   else if(StrPos(LowerCase(Path).c_str(),".ls2")){  // LBA2 binary mode
       isLBA2 = true;
       sceneIdx = -1;
       Scene = loadBinaryScene2(Path.c_str(),sceneIdx);
       if(filesize!=-1){
          putInitScene();
          bt_reload->Enabled = True;
          menu_reload->Enabled = True;
          bt_close->Enabled = True;
          menu_close->Enabled = True;
          bt_save->Enabled = True;
          menu_save->Enabled = True;
          bt_saveas->Enabled = True;
          menu_saveas->Enabled = True;
          menu_builder->Enabled = True;
          pl_scene->Visible = True;
          lastScene = Path;
       }
   }
   else if(StrPos(LowerCase(Path).c_str(),"scene.hqr")){  // LBA1 HQR Binary mode
      if(getNumEntries(Path.c_str()) == 120) // LBA1 scenes
          isLBA2 = false;
      else if(getNumEntries(Path.c_str()) == 223) // LBA2 scenes
          isLBA2 = true;
      frm_selectroom->ShowModal();
   }
   else
       ShowMessage("This program doens't support this file!");
}
//---------------------------------------------------------------------------

MESSAGE TWMCopyData Tfrm_lba::CopyData(TWMCopyData &Message)
{
    TCopyDataStruct *tmp;
    tmp = Message.CopyDataStruct;

    Message.Result = BuilderActions((TStoryCommand *)tmp->lpData, tmp->dwData);
    return Message;
}

//---------------------------------------------------------------------------

void Tfrm_lba::loadPaletteFromResource()
{
   Byte b;
   int color=0;
   TResourceStream *res = new TResourceStream(0,"LBA_1_MAIN","LBA_PALETTE");
   for(int i=0; i < 256; i++){
       res->Read(&b,1);
       //TPalette.push_back(b);
       //TPalette[i] = b;
       color = b;
       res->Read(&b,1);
       //TPalette[i] = TPalette[i] + b*256;
       color = color + b*256;
       res->Read(&b,1);
       //TPalette[i] = TPalette[i] + b*256*256;
       color = color + b*256*256;
       TColor c = (TColor)color;
       TPalette.push_back(c);
   }
   res->Seek(0,soFromBeginning);
   for(int i=0; i < 768; i++){
       res->Read(&b,1);
       palette[i] = b;
   }
   res->Free();
}

//---------------------------------------------------------------------------

void Tfrm_lba::putInitScene()
{
   lastLoadDir = ExtractFileDir(Path);

   // recentPath.insert(0,Path);

   if(!isLBA2)   // LBA1 text bank
   {
      cb_textbank->Items->Clear();
      cb_textbank->Items->Add("00: Citadel Island");
      cb_textbank->Items->Add("01: Principal Island");
      cb_textbank->Items->Add("02: White Leaf Desert");
      cb_textbank->Items->Add("03: Proxima Island");
      cb_textbank->Items->Add("04: Rebelion Island");
      cb_textbank->Items->Add("05: Hamalayi Mountains - Southern Range");
      cb_textbank->Items->Add("06: Hamalayi Mountains - Northern Range");
      cb_textbank->Items->Add("07: Tippet Island");
      cb_textbank->Items->Add("08: Brundle Island");
      cb_textbank->Items->Add("09: Fortress Island");
      cb_textbank->Items->Add("10: Polar Island");
   }
   else   // LBA2 text bank
   {
      cb_textbank->Items->Clear();
      cb_textbank->Items->Add("00: Citadel Island");
      cb_textbank->Items->Add("01: Principal Island <- unused");
      cb_textbank->Items->Add("02: Desert Island");
      cb_textbank->Items->Add("03: Emerald Moon");
      cb_textbank->Items->Add("04: Otringal");
      cb_textbank->Items->Add("05: Celebration");
      cb_textbank->Items->Add("06: Wannies");
      cb_textbank->Items->Add("07: Island of the Mosquibees");
      cb_textbank->Items->Add("08: Island of the Francos");
      cb_textbank->Items->Add("09: Isle CX");
      cb_textbank->Items->Add("10: Elevator to the undergas");
      cb_textbank->Items->Add("11: Under Celebration");
   }

   cb_textbank->ItemIndex = Scene.TextBank;
   edt_cube->Value = Scene.CubeEntry;

   edt_alpha->Value = Scene.AlphaLight;
   edt_beta->Value = Scene.BetaLight;

   edt_amb01->Value = Scene.Amb0_1;
   edt_amb02->Value = Scene.Amb0_2;
   edt_amb03->Value = Scene.Amb0_3;

   edt_amb11->Value = Scene.Amb1_1;
   edt_amb12->Value = Scene.Amb1_2;
   edt_amb13->Value = Scene.Amb1_3;

   edt_amb21->Value = Scene.Amb2_1;
   edt_amb22->Value = Scene.Amb2_2;
   edt_amb23->Value = Scene.Amb2_3;

   edt_amb31->Value = Scene.Amb3_1;
   edt_amb32->Value = Scene.Amb3_2;
   edt_amb33->Value = Scene.Amb3_3;

   if(isLBA2)
   {
       edt_amb04->Visible = True;
       edt_amb04->Value = Scene.Amb0_4;
       edt_amb05->Visible = True;
       edt_amb05->Value = Scene.Amb0_5;
       edt_amb14->Visible = True;
       edt_amb14->Value = Scene.Amb1_4;
       edt_amb15->Visible = True;
       edt_amb15->Value = Scene.Amb1_5;
       edt_amb24->Visible = True;
       edt_amb24->Value = Scene.Amb2_4;
       edt_amb25->Visible = True;
       edt_amb25->Value = Scene.Amb2_5;
       edt_amb34->Visible = True;
       edt_amb34->Value = Scene.Amb3_4;
       edt_amb35->Visible = True;
       edt_amb35->Value = Scene.Amb3_5;

       lb_amb04->Visible = True;
       lb_amb05->Visible = True;
       lb_amb14->Visible = True;
       lb_amb15->Visible = True;
       lb_amb24->Visible = True;
       lb_amb25->Visible = True;
       lb_amb34->Visible = True;
       lb_amb35->Visible = True;
   }
   else
   {
       edt_amb04->Visible = False;
       edt_amb04->Value = 0;
       edt_amb05->Visible = False;
       edt_amb05->Value = 0;
       edt_amb14->Visible = False;
       edt_amb14->Value = 0;
       edt_amb15->Visible = False;
       edt_amb15->Value = 0;
       edt_amb24->Visible = False;
       edt_amb24->Value = 0;
       edt_amb25->Visible = False;
       edt_amb25->Value = 0;
       edt_amb34->Visible = False;
       edt_amb34->Value = 0;
       edt_amb35->Visible = False;
       edt_amb35->Value = 0;

       lb_amb04->Visible = False;
       lb_amb05->Visible = False;
       lb_amb14->Visible = False;
       lb_amb15->Visible = False;
       lb_amb24->Visible = False;
       lb_amb25->Visible = False;
       lb_amb34->Visible = False;
       lb_amb35->Visible = False;
   }

   edt_secondmin->Value = Scene.Second_Min;
   edt_secondecart->Value = Scene.Second_Ecart;

   cb_cubemusic->ItemIndex = Scene.CubeMusic;

   StatusBar1->Panels->Items[0]->Text = "Actors: ";
   StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;
   StatusBar1->Panels->Items[1]->Text = "Tracks: ";
   StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;
   StatusBar1->Panels->Items[2]->Text = "Zones: ";
   StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;

   if(Scene.numActors != 0)
        edt_actors->MaxValue = Scene.numActors-1;
   edt_actors->Value = 0;

   if(Scene.numActors == 1)
     edt_actors->Enabled = False;
   else
     edt_actors->Enabled = True;

   edt_staticflag->Caption = 0;

   //char xis[256];
   //getLine(bodyDescPath.c_str(),xis,0);
  // edt_actorName->Text = "Hero";

   edt_sprite->Value = 0;
   edt_body->Value = 0;
   edt_animation->Value = 0;

   if(!isLBA2)
      edt_entity->MaxValue = entitiesStruct->numOfEntities-1;
   else
      edt_entity->MaxValue = 344; // or 345

   edt_entity->Value = 0;
   lb_realBody->Caption = "0";
   lb_realAnim->Caption = "0";
   edt_hit->Value = 0;
   bar_hit->Progress = 0;
   edt_bonus->Value = 0;
   edt_speed->Value = 0;
   bar_speed->Progress = 0;
   edt_amount->Value = 0;
   edt_talkcolor->Value = 4; // Hero Talk Color
   shape_talkcolor->Brush->Color = TPalette[((4+1) * 14) + (4 * 2)];
   edt_armour->Value = 0;
   bar_armour->Progress = 0;
   edt_points->Value = 0;
   bar_points->Progress = 0;
   cb_controlmode->ItemIndex = 0;

   edt_actorX->Value = Scene.Hero.X;
   scroll_actorX->Position = Scene.Hero.X;
   edt_actorY->Value = Scene.Hero.Y;
   scroll_actorY->Position = (Scene.Hero.Y - 32767) * (-1);
   edt_actorZ->Value = Scene.Hero.Z;
   scroll_actorZ->Position = Scene.Hero.Z;
   edt_angle->Text = "0 - [0 \xB0]";

   edt_cropleft->Text = 0;
   edt_croptop->Text = 0;
   edt_cropright->Text = 0;
   edt_cropbottom->Text = 0;

   bt_staticpar->Enabled = False;
   edt_entity->Enabled = False;
   edt_body->Enabled = False;
   edt_animation->Enabled = False;
   edt_sprite->Enabled = False;
   edt_hit->Enabled = False;
   edt_bonus->Enabled = False;
   cb_bonus->Enabled = False;
   edt_speed->Enabled = False;
   edt_amount->Enabled = False;
   edt_talkcolor->Enabled = False;
   edt_armour->Enabled = False;
   edt_points->Enabled = False;
   edt_cropleft->Enabled = False;
   edt_croptop->Enabled = False;
   edt_cropright->Enabled = False;
   edt_cropbottom->Enabled = False;
   scroll_angle->Enabled = False;
   edt_angle->Enabled = False;
   bar_speed->Progress = 0;
   cb_controlmode->Enabled = False;

   // TRACKS
   if(Scene.numTracks != 0)
        edt_tracks->MaxValue = Scene.numTracks-1;
   edt_tracks->Value = 0;
   if(!Scene.Tracks.empty())
   {
      edt_trackX->Value = Scene.Tracks[edt_tracks->Value].X;
      scroll_trackX->Position = Scene.Tracks[edt_tracks->Value].X;
      edt_trackY->Value = Scene.Tracks[edt_tracks->Value].Y;
      scroll_trackY->Position = (Scene.Tracks[edt_tracks->Value].Y - 32767) * (-1);
      edt_trackZ->Value = Scene.Tracks[edt_tracks->Value].Z;
      scroll_trackZ->Position = Scene.Tracks[edt_tracks->Value].Z;
   }

   if(Scene.numTracks > 0)
   {
      edt_tracks->Enabled = True;
      bt_removetrack->Enabled = True;
      bt_clonetrack->Enabled = True;
      scroll_trackX->Enabled = True;
      scroll_trackY->Enabled = True;
      scroll_trackZ->Enabled = True;
      edt_trackX->Enabled = True;
      edt_trackY->Enabled = True;
      edt_trackZ->Enabled = True;
   }
   if(Scene.numTracks == 1)
   {
      edt_tracks->Enabled = False;
   }
   else if(Scene.numTracks == 0)
   {
      edt_tracks->Enabled = False;
      bt_removetrack->Enabled = False;
      bt_clonetrack->Enabled = False;
      scroll_trackX->Enabled = False;
      scroll_trackY->Enabled = False;
      scroll_trackZ->Enabled = False;
      edt_trackX->Enabled = False;
      edt_trackY->Enabled = False;
      edt_trackZ->Enabled = False;
   }

   // ZONES
   if(Scene.numZones != 0)
       edt_zones->MaxValue = Scene.numZones-1;
   edt_zones->Value = 0;

   if(Scene.numZones == 1)
     edt_zones->Enabled = False;
   else
     edt_zones->Enabled = True;

   if(!Scene.Zones.empty())
   {
      edt_zonedimX->Value = Scene.Zones[edt_zones->Value].X1 - Scene.Zones[edt_zones->Value].X0;
      edt_zonedimY->Value = Scene.Zones[edt_zones->Value].Y1 - Scene.Zones[edt_zones->Value].Y0;
      edt_zonedimZ->Value = Scene.Zones[edt_zones->Value].Z1 - Scene.Zones[edt_zones->Value].Z0;

      edt_bzoneX->Value = Scene.Zones[edt_zones->Value].X0;
      scroll_bzoneX->Position = Scene.Zones[edt_zones->Value].X0;
      edt_bzoneY->Value = Scene.Zones[edt_zones->Value].Y0;
      scroll_bzoneY->Position = (Scene.Zones[edt_zones->Value].Y0 - 32767) * (-1);
      edt_bzoneZ->Value = Scene.Zones[edt_zones->Value].Z0;
      scroll_bzoneZ->Position = Scene.Zones[edt_zones->Value].Z0;


      /*edt_tzoneX->Value = Scene.Zones[edt_zones->Value].X1;
      scroll_tzoneX->Position = Scene.Zones[edt_zones->Value].X1;
      edt_tzoneY->Value = Scene.Zones[edt_zones->Value].Y1;
      scroll_tzoneY->Position = (Scene.Zones[edt_zones->Value].Y1 - 32767) * (-1);
      edt_tzoneZ->Value = Scene.Zones[edt_zones->Value].Z1;
      scroll_tzoneZ->Position = Scene.Zones[edt_zones->Value].Z1;*/

      cb_zonetype->ItemIndex = Scene.Zones[edt_zones->Value].Type;
      edt_info0->Value = Scene.Zones[edt_zones->Value].Info0;
      edt_info1->Value = Scene.Zones[edt_zones->Value].Info1;
      edt_info2->Value = Scene.Zones[edt_zones->Value].Info2;
      edt_info3->Value = Scene.Zones[edt_zones->Value].Info3;

      cb_snap->ItemIndex = Scene.Zones[edt_zones->Value].Snap;

        switch(Scene.Zones[edt_zones->Value].Type)
        {
            case 0: // Cube Zones
            {
                lb_info0->Caption = "Scene index:";
                lb_info1->Caption = "X:";
                lb_info2->Caption = "Y:";
                lb_info3->Caption = "Z:";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = True;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = True;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 1: // Camera Zones
            {
                lb_info0->Caption = "X:";
                lb_info1->Caption = "Y:";
                lb_info2->Caption = "Z:";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 2: // Sceneric Zones
            {
                lb_info0->Caption = "Zone id:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 3: // Grid Zones
            {
                lb_info0->Caption = "Grid index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 4: // Object Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "Bonus Paramenter:";
                lb_info2->Caption = "Bonus Amount:";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = True;
                cb_snap->Visible = True;
                break;
            }
            case 5: // Text Zones
            {
                lb_info0->Caption = "Text index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 6: // Ladder Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            default:
            {
                //ShowMessage("Wrong zone type opcode!");
                break;
            }
        }

   }

   if(Scene.numZones > 0)
   {
      edt_zones->Enabled = True;
      bt_removezone->Enabled = True;
      bt_clonezone->Enabled = True;
      scroll_bzoneX->Enabled = True;
      scroll_bzoneY->Enabled = True;
      scroll_bzoneZ->Enabled = True;
      edt_bzoneX->Enabled = True;
      edt_bzoneY->Enabled = True;
      edt_bzoneZ->Enabled = True;
      edt_zonedimX->Enabled = True;
      edt_zonedimY->Enabled = True;
      edt_zonedimZ->Enabled = True;
      cb_zonetype->Enabled = True;
      edt_info0->Enabled = True;
      edt_info1->Enabled = True;
      edt_info2->Enabled = True;
      edt_info3->Enabled = True;
   }
   if(Scene.numZones == 1)
   {
      edt_zones->Enabled = False;
   }
   else if(Scene.numTracks == 0)
   {
      edt_zones->Enabled = False;
      bt_removezone->Enabled = False;
      bt_clonezone->Enabled = False;
      scroll_bzoneX->Enabled = False;
      scroll_bzoneY->Enabled = False;
      scroll_bzoneZ->Enabled = False;
      edt_bzoneX->Enabled = False;
      edt_bzoneY->Enabled = False;
      edt_bzoneZ->Enabled = False;
      edt_zonedimX->Enabled = False;
      edt_zonedimY->Enabled = False;
      edt_zonedimZ->Enabled = False;
      cb_zonetype->Enabled = False;
      edt_info0->Enabled = False;
      edt_info1->Enabled = False;
      edt_info2->Enabled = False;
      edt_info3->Enabled = False;
   }

   StatusBar1->Panels->Items[3]->Text = "File Name: ";
   StatusBar1->Panels->Items[3]->Text = StatusBar1->Panels->Items[3]->Text + ExtractFileName(Path);

   if(!isLBA2)
   {
      AnsiString currfile;
      currfile = programPath;
      currfile += "\\imgs\\bodies\\";
      currfile += edt_entity->Value;
      currfile += ".bmp";
      img_actorY->Picture->Bitmap->LoadFromFile(currfile);
      img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
   }
   else
   {
      AnsiString currfile;
      currfile = programPath;
      currfile += "\\imgs\\actor.bmp";
      img_actorY->Picture->Bitmap->LoadFromFile(currfile);
      img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
   }
    
   if(displayRoom){ // only if we have this set in settings menu
      // open LBArchitect Builder after open the scene
      if(builderPath != "")
      {
          int tmp=0;
          // get the scene index
          if(StrPos(LowerCase(Path).c_str(),"scene.hqr"))
          {
             tmp = sceneIdx+1;
          }
          // TODO: Do a better number recognition.
          else if(StrPos(LowerCase(Path).c_str(),"scene"))
          {
              AnsiString tmp2 = ExtractFileName(Path).SubString(6,3);
              tmp = tmp2.ToIntDef(0);
          }
          else
          {
              AnsiString tmp2 = ExtractFileName(Path).SubString(0,3);
              tmp = tmp2.ToIntDef(0);
          }

          // if the file name doesn't have scene numbers, choose a grid to open.
          if(tmp==0){
              frm_selectgrid->ShowModal();
              // if the file name doesn't have scene numbers he don't do nothing
              if(sceneIdx==-1)
                return;
              tmp = sceneIdx+1;
          }

          // conversion between scenes numbers and grid entries.
          if(isLBA2){
              tmp = gridConv[tmp-1];
              tmp--;
          }

          if(!IsConnected()){
              AnsiString bPath = builderPath;
              bPath = bPath + " scenemode ";

              if(!isLBA2)
                  bPath = bPath + "1 "; // open LBA1 grids
              else {
                  bPath = bPath + "2 "; // open LBA2 grids
              }

              bPath = bPath + tmp; // pass the scene index

              WinExec(bPath.c_str(),SW_MAXIMIZE);
              BackwardConnection(frm_lba->Handle);
          }
          else
          {
              reloadGrid(tmp);
              BackwardConnection(frm_lba->Handle);
          }

          TimeOut->Enabled = True;

          // Check connection on timer and send values
      }
      else
        ShowMessage("Setup the path for LBArchitect Builder in Settings menu!");
   }
}

void Tfrm_lba::initScene()
{
   cb_textbank->ItemIndex = Scene.TextBank;
   edt_cube->Value = Scene.CubeEntry;

   cb_cubemusic->ItemIndex = Scene.CubeMusic;

   StatusBar1->Panels->Items[0]->Text = "Actors: ";
   StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;
   StatusBar1->Panels->Items[1]->Text = "Tracks: ";
   StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;
   StatusBar1->Panels->Items[2]->Text = "Zones: ";
   StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;

   edt_actors->MaxValue = Scene.numActors-1;
   edt_actors->Value = 0;

   edt_staticflag->Caption = 0;

   //char xis[256];
   //getLine(bodyDescPath.c_str(),xis,0);
  // edt_actorName->Text = "Hero";

   edt_sprite->Value = 0;
   edt_body->Value = 0;
   edt_animation->Value = 0;
   if(!isLBA2)
      edt_entity->MaxValue = entitiesStruct->numOfEntities;
   else
      edt_entity->MaxValue = 344;

   edt_entity->Value = 0;
   lb_realBody->Caption = "0";
   lb_realAnim->Caption = "0";
   edt_hit->Value = 0;
   bar_hit->Progress = 0;
   edt_bonus->Value = 0;
   edt_speed->Value = 0;
   bar_speed->Progress = 0;
   edt_amount->Value = 0;
   edt_talkcolor->Value = 4; // Hero Talk Color
   shape_talkcolor->Brush->Color = TPalette[((4+1) * 14) + (4 * 2)];
   edt_armour->Value = 0;
   bar_armour->Progress = 0;
   edt_points->Value = 0;
   bar_points->Progress = 0;
   cb_controlmode->ItemIndex = 0;

   edt_actorX->Value = Scene.Hero.X;
   scroll_actorX->Position = Scene.Hero.X;
   edt_actorY->Value = Scene.Hero.Y;
   scroll_actorY->Position = (Scene.Hero.Y - 32767) * (-1);
   edt_actorZ->Value = Scene.Hero.Z;
   scroll_actorZ->Position = Scene.Hero.Z;
   edt_angle->Text = "0 - [0 \xB0]";
   scroll_angle->Position = 0;

   edt_cropleft->Text = 0;
   edt_croptop->Text = 0;
   edt_cropright->Text = 0;
   edt_cropbottom->Text = 0;

   bt_staticpar->Enabled = False;
   edt_entity->Enabled = False;
   edt_body->Enabled = False;
   edt_animation->Enabled = False;
   edt_sprite->Enabled = False;
   edt_hit->Enabled = False;
   edt_bonus->Enabled = False;
   cb_bonus->Enabled = False;
   edt_speed->Enabled = False;
   edt_amount->Enabled = False;
   edt_talkcolor->Enabled = False;
   edt_armour->Enabled = False;
   edt_points->Enabled = False;
   edt_cropleft->Enabled = False;
   edt_croptop->Enabled = False;
   edt_cropright->Enabled = False;
   edt_cropbottom->Enabled = False;
   scroll_angle->Enabled = False;
   edt_angle->Enabled = False;
   bar_speed->Progress = 0;
   cb_controlmode->Enabled = False;
}
//--------------------------------------------------------------------------

void Tfrm_lba::clearScene()
{
   Path = "";

   cb_textbank->ItemIndex = 0;
   edt_cube->Value = 0;

   edt_alpha->Value = 0;
   edt_beta->Value = 0;

   edt_amb01->Value = 0;
   edt_amb02->Value = 0;
   edt_amb03->Value = 0;

   edt_amb11->Value = 0;
   edt_amb12->Value = 0;
   edt_amb13->Value = 0;

   edt_amb21->Value = 0;
   edt_amb22->Value = 0;
   edt_amb23->Value = 0;

   edt_amb31->Value = 0;
   edt_amb32->Value = 0;
   edt_amb33->Value = 0;

   // LBA2 amb vars
   edt_amb04->Value = 0;
   edt_amb05->Value = 0;
   edt_amb14->Value = 0;
   edt_amb15->Value = 0;
   edt_amb24->Value = 0;
   edt_amb25->Value = 0;
   edt_amb34->Value = 0;
   edt_amb35->Value = 0;

   edt_secondmin->Value = 0;
   edt_secondecart->Value = 0;

   cb_cubemusic->ItemIndex = 0;

   StatusBar1->Panels->Items[0]->Text = "Actors: 0";
   StatusBar1->Panels->Items[1]->Text = "Tracks: 0";
   StatusBar1->Panels->Items[2]->Text = "Zones: 0";
   StatusBar1->Panels->Items[3]->Text = "File Name: ";

   edt_actors->MaxValue = 0;
   edt_actors->Value = 0;

   /*if(!isLBA2)
      edt_entity->MaxValue = entitiesStruct->numOfEntities;
   else
      edt_entity->MaxValue = 344;*/
      
   edt_entity->Value = 0;
   edt_actorName->Text = " ";

   edt_sprite->Value = 0;
   edt_body->Value = 0;
   edt_animation->Value = 0;
   edt_hit->Value = 0;
   edt_bonus->Value = 0;
   edt_speed->Value = 0;
   edt_amount->Value = 0;
   edt_talkcolor->Value = 0;
   edt_armour->Value = 0;
   edt_points->Value = 0;
   cb_controlmode->ItemIndex = 0;

   edt_actorX->Value = 0;
   scroll_actorX->Position = 0;
   edt_actorY->Value = 0;
   scroll_actorY->Position = 32767;
   edt_actorZ->Value = 0;
   scroll_actorZ->Position = 0;
   edt_angle->Text = "0 - [0 \xB0]";

   edt_cropleft->Text = 0;
   edt_croptop->Text = 0;
   edt_cropright->Text = 0;
   edt_cropbottom->Text = 0;

   // Tracks
   edt_trackX->Value = 0;
   edt_trackY->Value = 0;
   edt_trackZ->Value = 0;

   // Zones
   edt_bzoneX->Value = 0;
   edt_bzoneY->Value = 0;
   edt_bzoneZ->Value = 0;
   edt_zonedimX->Value = 0;
   edt_zonedimY->Value = 0;
   edt_zonedimZ->Value = 0;
   cb_zonetype->ItemIndex = 0;
   edt_info0->Value = 0;
   edt_info1->Value = 0;
   edt_info2->Value = 0;
   edt_info3->Value = 0;
   cb_snap->ItemIndex = 0;
   cb_zonebonus->ItemIndex = 0;


   bt_staticpar->Enabled = False;
   edt_entity->Enabled = False;
   edt_actorName->Text = "";

   edt_body->Enabled = False;
   edt_animation->Enabled = False;
   edt_sprite->Enabled = False;
   edt_hit->Enabled = False;
   edt_bonus->Enabled = False;
   edt_speed->Enabled = False;
   edt_amount->Enabled = False;
   edt_talkcolor->Enabled = False;
   edt_armour->Enabled = False;
   edt_points->Enabled = False;

   edt_cropleft->Enabled = False;
   edt_croptop->Enabled = False;
   edt_cropright->Enabled = False;
   edt_cropbottom->Enabled = False;

   scroll_angle->Enabled = False;

   bt_reload->Enabled = False;
   menu_reload->Enabled = False;
   bt_close->Enabled = False;
   menu_close->Enabled = False;
   bt_save->Enabled = False;
   menu_save->Enabled = False;
   bt_saveas->Enabled = False;
   menu_saveas->Enabled = False;
   menu_builder->Enabled = False;

   pl_scene->Visible = False;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::About1Click(TObject *Sender)
{
    frm_about->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_settings2Click(TObject *Sender)
{
    frm_settings->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_staticparClick(TObject *Sender)
{
    if(stayOnTop)
        frm_staticpar->ShowModal();
    else
        frm_staticpar->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_actorscriptClick(TObject *Sender)
{
    if(stayOnTop)
        frm_actorscript->ShowModal();
    else
        frm_actorscript->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_newactorClick(TObject *Sender)
{
    NewActor(0,0,0);
}

//---------------------------------------------------------------------------

void Tfrm_lba::NewActor(int x, int y, int z)
{
   Scene.numActors++;

   TActor Actor;
   Actor.staticFlag = 0;
   Actor.Entity = 0;
   Actor.X = x;
   Actor.Y = y;
   Actor.Z = z;
   Actor.trackScript = new char[4];
   strcpy(Actor.trackScript,"END\n");
   Actor.lifeScript = new char[4];
   strcpy(Actor.lifeScript,"END\n");
   Scene.Actors.push_back(Actor);


   StatusBar1->Panels->Items[0]->Text = "Actors: ";
   StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;

   if(Scene.numActors > 1)
   {
      edt_actors->MaxValue = Scene.numActors - 1;
      /*if(edt_actors->Value==-1)
        edt_actors->Value = 0;*/
      edt_actors->Value = Scene.numActors - 1;
      edt_actors->Enabled = True;
   }
   else
   {
      bt_staticpar->Enabled = True;
      edt_entity->Enabled = True;

      edt_body->Enabled = True;
      edt_animation->Enabled = True;
      edt_sprite->Enabled = False;
      edt_hit->Enabled = True;
      edt_bonus->Enabled = True;
      edt_speed->Enabled = True;
      edt_amount->Enabled = True;
      edt_talkcolor->Enabled = True;
      edt_armour->Enabled = True;
      edt_points->Enabled = True;

      edt_cropleft->Enabled = True;
      edt_croptop->Enabled = True;
      edt_cropright->Enabled = True;
      edt_cropbottom->Enabled = True;

      scroll_angle->Enabled = True;
   }

   edt_actorName->Text = "";
   edt_staticflag->Caption = "0";
   value = 0;
   edt_sprite->Value = 0;
   edt_entity->Value = 0;
   edt_body->Value = 0;
   edt_animation->Value = 0;
   edt_hit->Value = 0;
   edt_bonus->Value = 0;
   edt_speed->Value = 255;
   edt_amount->Value = 0;
   edt_talkcolor->Value = 0;
   edt_armour->Value = 0;
   edt_points->Value = 0;

   edt_actorX->Value = x;
   scroll_actorX->Position = x;
   edt_actorY->Value = y;
   scroll_actorY->Position = (y - 32767) * (-1);
   edt_actorZ->Value = z;
   scroll_actorZ->Position = z;
   edt_angle->Text = "0 \xBA";
   scroll_angle->Position = 0;

   edt_cropleft->Text = 0;
   edt_croptop->Text = 0;
   edt_cropright->Text = 0;
   edt_cropbottom->Text = 0;

   cb_controlmode->ItemIndex = 0;

   //  if(IsConnected())
       SetActorCommand(Scene.Actors[edt_actors->Value-1],edt_actors->Value);
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_newspriteactorClick(TObject *Sender)
{
    // Deprecated
    //NewSpriteActor(0,0,0);
}

//---------------------------------------------------------------------------

void Tfrm_lba::NewSpriteActor(int x, int y, int z)
{
   TActor Actor;
   Actor.staticFlag = 1024;
   Actor.trackScript = new char[4];
   strcpy(Actor.trackScript,"END\n");
   Actor.lifeScript = new char[4];
   strcpy(Actor.lifeScript,"END\n");
   Scene.Actors.push_back(Actor);
   Scene.numActors++;

   StatusBar1->Panels->Items[0]->Text = "Actors: ";
   StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;

   if(Scene.numActors > 1)
   {
        edt_actors->MaxValue = Scene.numActors - 1;
        /*if(edt_actors->Value==-1)
          edt_actors->Value = 0;*/
        edt_actors->Value = Scene.numActors - 1;
        edt_actors->Enabled = True;
   }
   else
   {
      bt_staticpar->Enabled = True;
      edt_entity->Enabled = False;

      edt_body->Enabled = False;
      edt_animation->Enabled = False;
      edt_sprite->Enabled = True;
      edt_hit->Enabled = False;
      edt_bonus->Enabled = False;
      edt_speed->Enabled = False;
      edt_amount->Enabled = False;
      edt_talkcolor->Enabled = False;
      edt_armour->Enabled = False;
      edt_points->Enabled = False;

      edt_cropleft->Enabled = True;
      edt_croptop->Enabled = True;
      edt_cropright->Enabled = True;
      edt_cropbottom->Enabled = True;

      scroll_angle->Enabled = False;
   }

   if(IsConnected())
       SetActorCommand(Scene.Actors[edt_actors->Value],edt_actors->Value+1);

   edt_actorName->Text = "";
   edt_staticflag->Caption = "1024"; // is Sprite Actor
   value = 1024;  // is sprite actor
   edt_entity->Value = 0;
   edt_body->Value = 0;
   edt_animation->Value = 0;
   edt_sprite->Value = 0;
   edt_hit->Value = 0;
   edt_bonus->Value = 0;
   edt_speed->Value = 0;
   edt_amount->Value = 0;
   edt_talkcolor->Value = 0;
   edt_armour->Value = 0;
   edt_points->Value = 0;

   edt_actorX->Value = 0;
   scroll_actorX->Position = 0;
   edt_actorY->Value = 0;
   scroll_actorY->Position = 32767;
   edt_actorZ->Value = 0;
   scroll_actorZ->Position = 0;
   edt_angle->Text = "0 \xBA";

   edt_cropleft->Text = -1;
   edt_croptop->Text = -1;
   edt_cropright->Text = -1;
   edt_cropbottom->Text = -1;
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_cloneClick(TObject *Sender)
{
    CloneActor(-1,-1,-1); // -1 means no need to change coordinates
}

//---------------------------------------------------------------------------

void Tfrm_lba::CloneActor(int x, int y, int z)
{
    if(edt_actors->Value!=0){
       Scene.numActors++;

       TActor clone = Scene.Actors[edt_actors->Value-1];
       if(x!=-1 && y!=-1 && z!=-1) // don't update coordinates
       {
            clone.X = x;
            clone.Y = y;
            clone.Z = z;
       }

       Scene.Actors.push_back(clone);

       StatusBar1->Panels->Items[0]->Text = "Actors: ";
       StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;

       if(Scene.numActors > 1)
       {
          edt_actors->MaxValue = Scene.numActors - 1;
          edt_actors->Value = Scene.numActors - 1;
          edt_actors->Enabled = True;
       }

       //SetActorCommand(clone,edt_actors->Value);
   }
   else
       ShowMessage("Impossible to clone Hero actor!");
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_removeClick(TObject *Sender)
{
   if(edt_actors->Value!=0)
   {
       if(IsConnected())
           DelAllActorsCommand();

       for(int a=edt_actors->Value-1; a < Scene.numActors-1; a++){
           Scene.Actors[a] = Scene.Actors[a+1];
       }
       Scene.Actors.pop_back();
       Scene.numActors--;
       edt_actors->Value = edt_actors->Value - 1;
       edt_actors->MaxValue = Scene.numActors-1;
       StatusBar1->Panels->Items[0]->Text = "Actors: ";
       StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text + Scene.numActors;

       if(IsConnected())
       {
            SetHeroCommand(Scene.Hero);

            SendBeginUpdate();
            for(int i=0; i < Scene.numActors-1; i++)
            {
                SetActorCommand(Scene.Actors[i],i+1);
            }
            SendEndUpdate();
       }
   }
   else
       ShowMessage("Impossible to remove Hero actor!");
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_actorsChange(TObject *Sender)
{
   if(edt_actors->Value == 0)
   {
       initScene();
    //   edt_actorName->Text = "Hero";

       edt_staticflag->Caption = 0;

       bt_newactor->Enabled = True;
       bt_newspriteactor->Enabled = True;
       bt_clone->Enabled = False;
       bt_remove->Enabled = False;

       if(Scene.numActors == 1)
          edt_actors->Enabled = False;
       else
          edt_actors->Enabled = True;

       if(!isLBA2)
       {
          AnsiString currfile;
          currfile = programPath;
          currfile += "\\imgs\\bodies\\";
          currfile += edt_entity->Value;
          currfile += ".bmp";
          img_actorY->Picture->Bitmap->LoadFromFile(currfile);
          img_actorpos->Picture->Bitmap->LoadFromFile(currfile);

          if(frm_displayactor->Showing)
              frm_displayactor->img_fullactor->Picture->Assign(img_actorpos->Picture);
       }
       else
       {
          AnsiString currfile;
          currfile = programPath;
          currfile += "\\imgs\\actor.bmp";
          img_actorY->Picture->Bitmap->LoadFromFile(currfile);
          img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
       }
   }
   else if(!Scene.Actors.empty())
   {

       edt_staticflag->Caption = Scene.Actors[edt_actors->Value-1].staticFlag;

       if(edt_staticflag->Caption.ToInt() & 0x400){ // Is Sprite Actor

           bt_staticpar->Enabled = True;
           edt_entity->Enabled = False;
           edt_body->Enabled = False;
           edt_animation->Enabled = False;
           edt_sprite->Enabled = True;
           edt_hit->Enabled = False;
           edt_bonus->Enabled = False;
           cb_bonus->Enabled = False;
           edt_speed->Enabled = False;
           edt_amount->Enabled = False;
           edt_talkcolor->Enabled = False;
           edt_armour->Enabled = False;
           edt_points->Enabled = False;
           scroll_angle->Enabled = False;
           edt_angle->Enabled = False;
           edt_cropleft->Enabled = True;
           edt_croptop->Enabled = True;
           edt_cropright->Enabled = True;
           edt_cropbottom->Enabled = True;
           cb_controlmode->Enabled = True;           

           edt_actorName->Text = Scene.Actors[edt_actors->Value-1].Name;
           edt_entity->Value = Scene.Actors[edt_actors->Value-1].Entity;

           // RECHECK
           edt_body->Value = Scene.Actors[edt_actors->Value-1].Body;
           edt_animation->Value = Scene.Actors[edt_actors->Value-1].Animation;

           lb_realBody->Caption = "0";
           lb_realAnim->Caption = "0";

           edt_sprite->Value = Scene.Actors[edt_actors->Value-1].SpriteEntry;
           edt_hit->Value = Scene.Actors[edt_actors->Value-1].StrengthOfHit;
           edt_bonus->Value = Scene.Actors[edt_actors->Value-1].BonusParameter;
           edt_speed->Value = Scene.Actors[edt_actors->Value-1].SpeedRotation;
           edt_amount->Value = Scene.Actors[edt_actors->Value-1].BonusAmount;
           edt_talkcolor->Value = Scene.Actors[edt_actors->Value-1].TalkColor;
           edt_armour->Value = Scene.Actors[edt_actors->Value-1].Armour;
           edt_points->Value = Scene.Actors[edt_actors->Value-1].LifePoints;
           edt_actorX->Value = Scene.Actors[edt_actors->Value-1].X;
           scroll_actorX->Position = Scene.Actors[edt_actors->Value-1].X;
           edt_actorY->Value = Scene.Actors[edt_actors->Value-1].Y;
           scroll_actorY->Position = (Scene.Actors[edt_actors->Value-1].Y - 32767 ) * (-1);
           edt_actorZ->Value = Scene.Actors[edt_actors->Value-1].Z;
           scroll_actorZ->Position = Scene.Actors[edt_actors->Value-1].Z;
           scroll_angle->Position = Scene.Actors[edt_actors->Value-1].Angle;
           edt_cropleft->Text = Scene.Actors[edt_actors->Value-1].cropLeft;
           edt_croptop->Text = Scene.Actors[edt_actors->Value-1].cropTop;
           edt_cropright->Text = Scene.Actors[edt_actors->Value-1].cropRight;
           edt_cropbottom->Text = Scene.Actors[edt_actors->Value-1].cropBottom;
           cb_controlmode->ItemIndex = Scene.Actors[edt_actors->Value-1].Move;

           if(!isLBA2)
            {
                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\sprites\\";
                currfile += edt_sprite->Value;
                currfile += ".bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
            }
            else
            {
                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\actor.bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
            }

       }else  // is 3D model actor
       {
           bt_staticpar->Enabled = True;
           edt_entity->Enabled = True;
           edt_body->Enabled = True;
           edt_animation->Enabled = True;
           edt_sprite->Enabled = False;
           edt_hit->Enabled = True;
           edt_bonus->Enabled = True;
           cb_bonus->Enabled = True;
           edt_speed->Enabled = True;
           edt_amount->Enabled = True;
           edt_talkcolor->Enabled = True;
           edt_armour->Enabled = True;
           edt_points->Enabled = True;
           scroll_angle->Enabled = True;
           edt_angle->Enabled = True;
           edt_cropleft->Enabled = True;
           edt_croptop->Enabled = True;
           edt_cropright->Enabled = True;
           edt_cropbottom->Enabled = True;
           cb_controlmode->Enabled = True;

           edt_actorName->Text = Scene.Actors[edt_actors->Value-1].Name;
           edt_entity->Value = Scene.Actors[edt_actors->Value-1].Entity;

           if(edt_body->MaxValue == 0)
                edt_body->Enabled = False;
            else {
                edt_body->MaxValue = edt_body->MaxValue-1;
                edt_body->Enabled = True;
            }

            if(edt_animation->MaxValue == 0)
                edt_animation->Enabled = False;
            else{
                edt_animation->MaxValue = edt_animation->MaxValue-1;
                edt_animation->Enabled = True;
            }

           edt_animation->Value = Scene.Actors[edt_actors->Value-1].Animation;
           edt_body->Value = Scene.Actors[edt_actors->Value-1].Body;

           edt_hit->Value = Scene.Actors[edt_actors->Value-1].StrengthOfHit;
           edt_bonus->Value = Scene.Actors[edt_actors->Value-1].BonusParameter;
           edt_speed->Value = Scene.Actors[edt_actors->Value-1].SpeedRotation;
           edt_amount->Value = Scene.Actors[edt_actors->Value-1].BonusAmount;
           edt_talkcolor->Value = Scene.Actors[edt_actors->Value-1].TalkColor;
           edt_armour->Value = Scene.Actors[edt_actors->Value-1].Armour;
           edt_points->Value = Scene.Actors[edt_actors->Value-1].LifePoints;
           edt_actorX->Value = Scene.Actors[edt_actors->Value-1].X;
           scroll_actorX->Position = Scene.Actors[edt_actors->Value-1].X;
           edt_actorY->Value = Scene.Actors[edt_actors->Value-1].Y;
           scroll_actorY->Position = (Scene.Actors[edt_actors->Value-1].Y - 32767 ) * (-1);
           edt_actorZ->Value = Scene.Actors[edt_actors->Value-1].Z;
           scroll_actorZ->Position = Scene.Actors[edt_actors->Value-1].Z;
           scroll_angle->Position = Scene.Actors[edt_actors->Value-1].Angle;
           edt_cropleft->Text = Scene.Actors[edt_actors->Value-1].cropLeft;
           edt_croptop->Text = Scene.Actors[edt_actors->Value-1].cropTop;
           edt_cropright->Text = Scene.Actors[edt_actors->Value-1].cropRight;
           edt_cropbottom->Text = Scene.Actors[edt_actors->Value-1].cropBottom;
           cb_controlmode->ItemIndex = Scene.Actors[edt_actors->Value-1].Move;
       }
       if(frm_staticpar->Showing){
           value = Scene.Actors[edt_actors->Value - 1].staticFlag;
           frm_staticpar->loadValues(value);
       }
       bt_newactor->Enabled = True;
       bt_newspriteactor->Enabled = True;
       bt_clone->Enabled = True;
       bt_remove->Enabled = True;
   }

   SelectActorCommand(edt_actors->Value);

   if(frm_actorscript->Showing){
       frm_actorscript->loadTrackScript();
       frm_actorscript->loadLifeScript();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_entityChange(TObject *Sender)
{
    if(edt_actors->Value!=0 && !(edt_staticflag->Caption.ToInt() & 0x400)){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].Entity = edt_entity->Value;

            if(!isLBA2)
            {
                edt_entity->MaxValue = entitiesStruct->numOfEntities-1;
                edt_body->MaxValue = entitiesStruct->entitiesTable[edt_entity->Value].numOfBody; //-1;
                edt_animation->MaxValue = entitiesStruct->entitiesTable[edt_entity->Value].numOfAnims; //-1;
                lb_realBody->Caption = entitiesStruct->entitiesTable[edt_entity->Value].bodyList[edt_body->Value].index;
                lb_realAnim->Caption = entitiesStruct->entitiesTable[edt_entity->Value].animList[edt_animation->Value].index;

                edt_sprite->MaxValue = 117;

                //edt_body->Value = 0;
                //edt_animation->Value = 0;

                // RECHECK BOTH
                if(edt_body->MaxValue == 0)
                    edt_body->Enabled = False;
                else {
                    edt_body->MaxValue = edt_body->MaxValue-1;
                    edt_body->Enabled = True;
                }

                if(edt_animation->MaxValue == 0)
                    edt_animation->Enabled = False;
                else{
                    edt_animation->MaxValue = edt_animation->MaxValue-1;
                    edt_animation->Enabled = True;
                }

                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\bodies\\";
                currfile += edt_entity->Value;
                currfile += ".bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);

                if(frm_displayactor->Showing)
                    frm_displayactor->img_fullactor->Picture->Assign(img_actorpos->Picture);
            }
            else
            {
                // RECHECK all this values
                edt_entity->MaxValue = 344; // or 345
                edt_body->MaxValue = 469;
                edt_animation->MaxValue = 2083;
                edt_sprite->MaxValue = 424;

                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\actor.bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
            }

            if(!isLBA2)
            {
                char xis[256];
                getLine(bodyDescPath.c_str(),xis,edt_entity->Value);
                edt_actorName->Text = xis;
                strcpy(Scene.Actors[edt_actors->Value-1].Name, edt_actorName->Text.c_str());
            }
            else
                edt_actorName->Text = "";

            SetActorCommand(Scene.Actors[edt_actors->Value-1], edt_actors->Value);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_bodyChange(TObject *Sender)
{
if(edt_actors->Value!=0){
   if(!Scene.Actors.empty()){
       Scene.Actors[edt_actors->Value-1].Body = edt_body->Value;

       lb_realBody->Caption = "0";
       lb_realAnim->Caption = "0";

       if(!isLBA2){
          lb_realBody->Caption = entitiesStruct->entitiesTable[edt_entity->Value].bodyList[edt_body->Value].index;
       }
   }
}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_animationChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
           Scene.Actors[edt_actors->Value-1].Animation = edt_animation->Value;

           if(!isLBA2){
              lb_realAnim->Caption = entitiesStruct->entitiesTable[edt_entity->Value].animList[edt_animation->Value].index;
           }
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_spriteChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].SpriteEntry = edt_sprite->Value;

            SetActorCommand(Scene.Actors[edt_actors->Value-1], edt_actors->Value);

           /* if(!isLBA2)
            {
                char xis[256];
                getLine(spriteDescPath.c_str(),xis,edt_sprite->Value);
                edt_actorName->Text = xis;
                strcpy(Scene.Actors[edt_actors->Value-1].Name, edt_actorName->Text.c_str());
            }
            else
            {
                char xis2[256];
                getLine(sprite2DescPath.c_str(),xis2,edt_sprite->Value);
                edt_actorName->Text = xis2;
                strcpy(Scene.Actors[edt_actors->Value-1].Name, edt_actorName->Text.c_str());
            } */

            if(!isLBA2)
            {
                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\sprites\\";
                currfile += edt_sprite->Value;
                currfile += ".bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);

                if(frm_displayactor->Showing)
                    frm_displayactor->img_fullactor->Picture->Assign(img_actorpos->Picture);
            }
            else
            {
                AnsiString currfile;
                currfile = programPath;
                currfile += "\\imgs\\actor.bmp";
                img_actorY->Picture->Bitmap->LoadFromFile(currfile);
                img_actorpos->Picture->Bitmap->LoadFromFile(currfile);
            }
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_hitChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].StrengthOfHit = edt_hit->Value;
            bar_hit->Progress = (edt_hit->Value * 100 ) / 255;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_bonusChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].BonusParameter = edt_bonus->Value;

            if(edt_bonus->Value & 0x0010)
            {
                cb_bonus->ItemIndex = 0;
            }else if(edt_bonus->Value & 0x0020)
            {
                cb_bonus->ItemIndex = 1;
            }
            else if(edt_bonus->Value & 0x0040)
            {
                cb_bonus->ItemIndex = 2;
            }
            else if(edt_bonus->Value & 0x0080)
            {
                cb_bonus->ItemIndex = 3;
            }
            else if(edt_bonus->Value & 0x0100)
            {
                cb_bonus->ItemIndex = 4;
            }
            else
                cb_bonus->ItemIndex = 5;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_bonusChange(TObject *Sender)
{
   if(cb_bonus->ItemIndex == 0) // Money
       edt_bonus->Value = 16;
   else if(cb_bonus->ItemIndex == 1) // Life
       edt_bonus->Value = 32;
   else if(cb_bonus->ItemIndex == 2) // Magic
       edt_bonus->Value = 64;
   else if(cb_bonus->ItemIndex == 3) // Key
       edt_bonus->Value = 128;
   else if(cb_bonus->ItemIndex == 4) // Clove
       edt_bonus->Value = 256;
   else if(cb_bonus->ItemIndex == 5) // Empty
       edt_bonus->Value = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amountChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].BonusAmount = edt_amount->Value;
            bar_amount->Progress = (edt_amount->Value * 100 ) / 255;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_speedChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].SpeedRotation = edt_speed->Value;
            bar_speed->Progress = 100 - ( (edt_speed->Value * 100 ) / 255 );
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_talkcolorChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].TalkColor = edt_talkcolor->Value;
            shape_talkcolor->Brush->Color = TPalette[((edt_talkcolor->Value+1) * 14) + (edt_talkcolor->Value * 2)]; //((edt_talkcolor->Value+1) * 42) + (edt_talkcolor->Value * 6)
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_armourChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].Armour = edt_armour->Value;
            bar_armour->Progress = (edt_armour->Value * 100 ) / 255;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_pointsChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].LifePoints = edt_points->Value;
            bar_points->Progress = (edt_points->Value * 100 ) / 255;
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_angleChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].Angle = scroll_angle->Position;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_actorXChange(TObject *Sender)
{
   scroll_actorX->Position = edt_actorX->Value;
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty())
       {
            int newValue = edt_actorX->Value;
            int oldValue = Scene.Actors[edt_actors->Value-1].X;

            if(newValue != oldValue)
            {
                Scene.Actors[edt_actors->Value-1].X = edt_actorX->Value;
             //   if(IsConnected())
                    SetActorCommand(Scene.Actors[edt_actors->Value-1],edt_actors->Value);
            }
       }
   }
   else{
        int newValue = edt_actorX->Value;
        int oldValue = Scene.Hero.X;

        if(newValue != oldValue)
        {
            Scene.Hero.X = edt_actorX->Value;
           // if(IsConnected())
                SetHeroCommand(Scene.Hero);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_actorYChange(TObject *Sender)
{
   scroll_actorY->Position = (edt_actorY->Value - 32767) * (-1);
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty())
       {
            int newValue = edt_actorY->Value;
            int oldValue = Scene.Actors[edt_actors->Value-1].Y;

            if(newValue != oldValue)
            {
                Scene.Actors[edt_actors->Value-1].Y = edt_actorY->Value;
            //    if(IsConnected())
                    SetActorCommand(Scene.Actors[edt_actors->Value-1],edt_actors->Value);
           }
       }
   }
   else{
        int newValue = edt_actorY->Value;
        int oldValue = Scene.Hero.Y;

        if(newValue != oldValue)
        {
            Scene.Hero.Y = edt_actorY->Value;
           // if(IsConnected())
                SetHeroCommand(Scene.Hero);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_actorZChange(TObject *Sender)
{
   scroll_actorZ->Position = edt_actorZ->Value;
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty())
       {
            int newValue = edt_actorZ->Value;
            int oldValue = Scene.Actors[edt_actors->Value-1].Z;

            if(newValue != oldValue)
            {
                Scene.Actors[edt_actors->Value-1].Z = edt_actorZ->Value;
          //      if(IsConnected())
                    SetActorCommand(Scene.Actors[edt_actors->Value-1],edt_actors->Value);
            }
       }
   }
   else{
        int newValue = edt_actorZ->Value;
        int oldValue = Scene.Hero.Z;

        if(newValue != oldValue)
        {
            Scene.Hero.Z = edt_actorZ->Value;
          //  if(IsConnected())
                SetHeroCommand(Scene.Hero);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_cropleftChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].cropLeft = StrToInt(edt_cropleft->Text);
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_croptopChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].cropTop = StrToInt(edt_croptop->Text);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_croprightChange(TObject *Sender)
{
    if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].cropRight = StrToInt(edt_cropright->Text);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_cropbottomChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
            Scene.Actors[edt_actors->Value-1].cropBottom = StrToInt(edt_cropbottom->Text);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_tracksChange(TObject *Sender)
{
   if(!Scene.Tracks.empty())
   {
       edt_trackX->Value = Scene.Tracks[edt_tracks->Value].X;
       scroll_trackX->Position = Scene.Tracks[edt_tracks->Value].X;
       edt_trackY->Value = Scene.Tracks[edt_tracks->Value].Y;
       scroll_trackY->Position = (Scene.Tracks[edt_tracks->Value].Y - 32767 ) * (-1);
       edt_trackZ->Value = Scene.Tracks[edt_tracks->Value].Z;
       scroll_trackZ->Position = Scene.Tracks[edt_tracks->Value].Z;

       SelectTrackCommand(Scene.Tracks[edt_tracks->Value].Num);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_trackXChange(TObject *Sender)
{
   scroll_trackX->Position = edt_trackX->Value;
   if(!Scene.Tracks.empty())
   {
        int newValue = edt_trackX->Value;
        int oldValue = Scene.Tracks[edt_tracks->Value].X;

        if(newValue != oldValue)
        {
            Scene.Tracks[edt_tracks->Value].X = edt_trackX->Value;
            SetTrackCommand(Scene.Tracks[edt_tracks->Value]);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_trackYChange(TObject *Sender)
{
   scroll_trackY->Position = (edt_trackY->Value - 32767) * (-1);
   if(!Scene.Tracks.empty())
   {
        int newValue = edt_trackY->Value;
        int oldValue = Scene.Tracks[edt_tracks->Value].Y;

        if(newValue != oldValue)
        {
            Scene.Tracks[edt_tracks->Value].Y = edt_trackY->Value;
         //   if(IsConnected())
                SetTrackCommand(Scene.Tracks[edt_tracks->Value]);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_trackZChange(TObject *Sender)
{
   scroll_trackZ->Position = edt_trackZ->Value;
   if(!Scene.Tracks.empty())
   {
        int newValue = edt_trackZ->Value;
        int oldValue = Scene.Tracks[edt_tracks->Value].Z;

        if(newValue != oldValue)
        {
            Scene.Tracks[edt_tracks->Value].Z = edt_trackZ->Value;
        //    if(IsConnected())
                SetTrackCommand(Scene.Tracks[edt_tracks->Value]);
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_clonetrackClick(TObject *Sender)
{
   Scene.numTracks++;

   TTrack track;
   track.X = Scene.Tracks[edt_tracks->Value].X;
   track.Y = Scene.Tracks[edt_tracks->Value].Y;
   track.Z = Scene.Tracks[edt_tracks->Value].Z;
   track.Num = Scene.numTracks-1;
   // Put in last place
   Scene.Tracks.push_back(track);

   // Put in front of the clone track
   //Scene.Tracks.push_back(Scene.Tracks[Scene.numTracks-1]);
   /*for(int a=Scene.numTracks-1; a > edt_tracks->Value; a--)
   {
       Scene.Tracks[a-1].Num = a;
       Scene.Tracks[a] = Scene.Tracks[a-1];
   } */

   StatusBar1->Panels->Items[1]->Text = "Tracks: ";
   StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;

   if(Scene.numTracks > 1)
   {
      edt_tracks->MaxValue = edt_tracks->MaxValue + 1;
      edt_tracks->Value = edt_tracks->MaxValue;
      edt_tracks->Enabled = True;
   }

//   SetTrackCommand(track);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_removetrackClick(TObject *Sender)
{
   if(!Scene.Tracks.empty())
   {
        DelAllTracksCommand();

        for(int a=edt_tracks->Value; a < Scene.numTracks; a++){
            Scene.Tracks[a+1].Num = a;
            Scene.Tracks[a] = Scene.Tracks[a+1];
        }

        Scene.Tracks.pop_back();

        if(Scene.numTracks > 0){ // edt_tracks->MaxValue!=0
            Scene.numTracks--;
            StatusBar1->Panels->Items[1]->Text = "Tracks: ";
            StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;
            if(Scene.numTracks != 0)
            {
                edt_tracks->Value = edt_tracks->Value - 1;
                edt_tracks->MaxValue = edt_tracks->MaxValue - 1;
            }
        }

        // trick to update the values on the form
        if(edt_tracks->Value==0)
        {
            edt_tracks->Value = 1;
            edt_tracks->Value = 0;
        }

        if(Scene.numTracks == 1)
            edt_tracks->Enabled = False;
        else
            edt_tracks->Enabled = True;

        if(Scene.numTracks==0)
        {
            edt_trackX->Value = 0;
            edt_trackY->Value = 0;
            edt_trackZ->Value = 0;
            //  Scene.numTracks--;
            //  StatusBar1->Panels->Items[1]->Text = "Tracks: ";
            //  StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;
            edt_trackX->Enabled = False;
            edt_trackY->Enabled = False;
            edt_trackZ->Enabled = False;
            scroll_trackX->Enabled = False;
            scroll_trackY->Enabled = False;
            scroll_trackZ->Enabled = False;
            bt_removetrack->Enabled = False;
            bt_clonetrack->Enabled = False;
            edt_tracks->Enabled = False;
        }

      //  if(IsConnected())
      //  {
            SendBeginUpdate();
            for(int i=0; i < Scene.numTracks; i++)
            {
                SetTrackCommand(Scene.Tracks[i]);
            }
            SendEndUpdate();
       // }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_newtrackClick(TObject *Sender)
{
   NewTrack(0,0,0);
}
//---------------------------------------------------------------------------

void Tfrm_lba::NewTrack(int x, int y, int z)
{
   Scene.numTracks++;

   TTrack track;
   track.X = x;
   track.Y = y;
   track.Z = z;
   track.Num = Scene.numTracks-1;
   // Put in last place
   Scene.Tracks.push_back(track);

   StatusBar1->Panels->Items[1]->Text = "Tracks: ";
   StatusBar1->Panels->Items[1]->Text = StatusBar1->Panels->Items[1]->Text + Scene.numTracks;

   if(Scene.numTracks > 1)
   {
      edt_tracks->MaxValue = Scene.numTracks-1;
      /*if(edt_tracks->Value==-1)
        edt_tracks->Value = 0;*/
      edt_tracks->Value = edt_tracks->MaxValue;
      edt_tracks->Enabled = True;
   }
   else
   {
      bt_removetrack->Enabled = True;
      bt_clonetrack->Enabled = True;
      edt_trackX->Enabled = True;
      edt_trackY->Enabled = True;
      edt_trackZ->Enabled = True;
      scroll_trackX->Enabled = True;
      scroll_trackY->Enabled = True;
      scroll_trackZ->Enabled = True;
   }

   SetTrackCommand(Scene.Tracks[edt_tracks->Value]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_settingsClick(TObject *Sender)
{
    frm_settings->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_closeClick(TObject *Sender)
{
/*   if(!Path.IsEmpty())
      lastScene = Path; */

   lastScene = "";

   frm_settings->saveSettings();

   close3rdParty(); // Close Builder.exe by Zink
   
   if(frm_actorscript->Showing)
      frm_actorscript->Close();
   if(frm_staticpar->Showing)
      frm_staticpar->Close();
   if(frm_scripthelp->Showing)
      frm_scripthelp->Close();

   clearScene();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_saveasClick(TObject *Sender)
{
   SaveDialog1->Title = "Save LBA1 and LBA2 Binary and Text Scenes";
   SaveDialog1->Filter = "All known files (*.ls1, *.ls2, *.sce)|*.ls1;*.ls2;*.sce|LBA1 Binary Scene files (*.ls1)|*.ls1|LBA2 Binary Scene files (*.ls2)|*.ls2|LBA1 Text Scene files (*.sce)|*.sce";
   SaveDialog1->FileName = Path;
   SaveDialog1->InitialDir = lastSaveDir;

   if(SaveDialog1->Execute()){
      AnsiString tmp = SaveDialog1->FileName;

      if(SaveDialog1->FilterIndex == 1) // all
      {
          if(StrPos(LowerCase(tmp).c_str(),".ls1"))
              saveBinaryScene(Scene,tmp.c_str());
          else if(StrPos(LowerCase(tmp).c_str(),".ls2"))
              saveBinaryScene2(Scene,tmp.c_str());
          else if(StrPos(LowerCase(tmp).c_str(),".sce"))
              saveTextScene(Scene,tmp.c_str());
      }
      else if(SaveDialog1->FilterIndex == 2) // *.ls1
      {
          if(!StrPos(LowerCase(tmp).c_str(),".ls1"))
              tmp = tmp + ".ls1";

          saveBinaryScene(Scene,tmp.c_str());
      }
      else if(SaveDialog1->FilterIndex == 3) // *.ls2
      {
          if(!StrPos(LowerCase(tmp).c_str(),".ls2"))
              tmp = tmp + ".ls2";

          saveBinaryScene2(Scene,tmp.c_str());
      }
      else if(SaveDialog1->FilterIndex == 4) // *.sce
      {
          if(!StrPos(LowerCase(tmp).c_str(),".sce"))
              tmp = tmp + ".sce";

          saveTextScene(Scene,tmp.c_str());
      }

      lastSaveDir = ExtractFileDir(tmp);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_bzoneXChange(TObject *Sender)
{
   scroll_bzoneX->Position = edt_bzoneX->Value;
   if(!Scene.Zones.empty()){
       Scene.Zones[edt_zones->Value].X0 = edt_bzoneX->Value;
       Scene.Zones[edt_zones->Value].X1 = edt_bzoneX->Value + edt_zonedimX->Value;
      // if(IsConnected())
            SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_bzoneZChange(TObject *Sender)
{
   scroll_bzoneZ->Position = edt_bzoneZ->Value;
   if(!Scene.Zones.empty())
   {
       Scene.Zones[edt_zones->Value].Z0 = edt_bzoneZ->Value;
       Scene.Zones[edt_zones->Value].Z1 = edt_bzoneZ->Value + edt_zonedimZ->Value;
    //   if(IsConnected())
            SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);

   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_bzoneYChange(TObject *Sender)
{
   scroll_bzoneY->Position = (edt_bzoneY->Value - 32767) * (-1);
   if(!Scene.Zones.empty()){
       Scene.Zones[edt_zones->Value].Y0 = edt_bzoneY->Value;
       Scene.Zones[edt_zones->Value].Y1 = edt_bzoneY->Value + edt_zonedimY->Value;
    //   if(IsConnected())
            SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_zonetypeChange(TObject *Sender)
{
    if(!Scene.Zones.empty())
    {
        int newValue = cb_zonetype->ItemIndex;
        int oldValue = Scene.Zones[edt_zones->Value].Type;

        if(newValue != oldValue)
        {
            Scene.Zones[edt_zones->Value].Type = cb_zonetype->ItemIndex;
          //  if(IsConnected())
                SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
        }

        switch(Scene.Zones[edt_zones->Value].Type)
        {
            case 0: // Cube Zones
            {
                lb_info0->Caption = "Scene index:";
                lb_info1->Caption = "X:";
                lb_info2->Caption = "Y:";
                lb_info3->Caption = "Z:";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = True;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = True;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 1: // Camera Zones
            {
                lb_info0->Caption = "X:";
                lb_info1->Caption = "Y:";
                lb_info2->Caption = "Z:";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 2: // Sceneric Zones
            {
                lb_info0->Caption = "Zone id:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 3: // Grid Zones
            {
                lb_info0->Caption = "Grid index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 4: // Object Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "Bonus Paramenter:";
                lb_info2->Caption = "Bonus Amount:";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = True;
                cb_snap->Visible = True;
                break;
            }
            case 5: // Text Zones
            {
                lb_info0->Caption = "Text index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 6: // Ladder Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            default:
            {
                //ShowMessage("Wrong zone type opcode!");
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_info0Change(TObject *Sender)
{
    if(!Scene.Zones.empty())
    {
        Scene.Zones[edt_zones->Value].Info0 = edt_info0->Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_info1Change(TObject *Sender)
{
    if(!Scene.Zones.empty())
    {
        Scene.Zones[edt_zones->Value].Info1 = edt_info1->Value;

        if(Scene.Zones[edt_zones->Value].Type==4)
        {
            if(edt_info1->Value & 0x0010)
            {
                cb_zonebonus->ItemIndex = 0;
            }else if(edt_info1->Value & 0x0020)
            {
                cb_zonebonus->ItemIndex = 1;
            }
            else if(edt_info1->Value & 0x0040)
            {
                cb_zonebonus->ItemIndex = 2;
            }
            else if(edt_info1->Value & 0x0080)
            {
                cb_zonebonus->ItemIndex = 3;
            }
            else if(edt_info1->Value & 0x0100)
            {
                cb_zonebonus->ItemIndex = 4;
            }
            else
                cb_zonebonus->ItemIndex = 5;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_info2Change(TObject *Sender)
{
    if(!Scene.Zones.empty())
    {
        Scene.Zones[edt_zones->Value].Info2 = edt_info2->Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_info3Change(TObject *Sender)
{
    if(!Scene.Zones.empty())
    {
        Scene.Zones[edt_zones->Value].Info3 = edt_info3->Value;
    }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_lba::edt_zonesChange(TObject *Sender)
{
   if(Scene.numZones == 1)
     edt_zones->Enabled = False;
   else
     edt_zones->Enabled = True;

   if(!Scene.Zones.empty())
   {
        edt_zonedimX->Value = Scene.Zones[edt_zones->Value].X1 - Scene.Zones[edt_zones->Value].X0;
        edt_zonedimY->Value = Scene.Zones[edt_zones->Value].Y1 - Scene.Zones[edt_zones->Value].Y0;
        edt_zonedimZ->Value = Scene.Zones[edt_zones->Value].Z1 - Scene.Zones[edt_zones->Value].Z0;

        edt_bzoneX->Value = Scene.Zones[edt_zones->Value].X0;
        scroll_bzoneX->Position = Scene.Zones[edt_zones->Value].X0;
        edt_bzoneY->Value = Scene.Zones[edt_zones->Value].Y0;
        scroll_bzoneY->Position = (Scene.Zones[edt_zones->Value].Y0 - 32767) * (-1);
        edt_bzoneZ->Value = Scene.Zones[edt_zones->Value].Z0;
        scroll_bzoneZ->Position = Scene.Zones[edt_zones->Value].Z0;

        edt_info0->Value = Scene.Zones[edt_zones->Value].Info0;
        edt_info1->Value = Scene.Zones[edt_zones->Value].Info1;
        edt_info2->Value = Scene.Zones[edt_zones->Value].Info2;
        edt_info3->Value = Scene.Zones[edt_zones->Value].Info3;

        cb_zonetype->ItemIndex = Scene.Zones[edt_zones->Value].Type;

        cb_snap->ItemIndex = Scene.Zones[edt_zones->Value].Snap;

        switch(Scene.Zones[edt_zones->Value].Type)
        {
            case 0: // Cube Zones
            {
                lb_info0->Caption = "Scene index:";
                lb_info1->Caption = "X:";
                lb_info2->Caption = "Y:";
                lb_info3->Caption = "Z:";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = True;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = True;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 1: // Camera Zones
            {
                lb_info0->Caption = "X:";
                lb_info1->Caption = "Y:";
                lb_info2->Caption = "Z:";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 2: // Sceneric Zones
            {
                lb_info0->Caption = "Zone id:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 3: // Grid Zones
            {
                lb_info0->Caption = "Grid index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 4: // Object Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "Bonus Paramenter:";
                lb_info2->Caption = "Bonus Amount:";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = True;
                lb_info2->Visible = True;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = True;
                edt_info2->Visible = True;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = True;
                cb_snap->Visible = True;
                break;
            }
            case 5: // Text Zones
            {
                lb_info0->Caption = "Text index:";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = True;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = True;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            case 6: // Ladder Zones
            {
                lb_info0->Caption = "";
                lb_info1->Caption = "";
                lb_info2->Caption = "";
                lb_info3->Caption = "";

                lb_info0->Visible = False;
                lb_info1->Visible = False;
                lb_info2->Visible = False;
                lb_info3->Visible = False;
                edt_info0->Visible = False;
                edt_info1->Visible = False;
                edt_info2->Visible = False;
                edt_info3->Visible = False;

                cb_zonebonus->Visible = False;
                cb_snap->Visible = False;
                break;
            }
            default:
            {
                //ShowMessage("Wrong zone type opcode!");
                break;
            }
        }
        
        SelectZoneCommand(edt_zones->Value);
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_zonebonusChange(TObject *Sender)
{
   if(cb_zonebonus->ItemIndex == 0) // Money
       edt_info1->Value = 16;
   else if(cb_zonebonus->ItemIndex == 1) // Life
       edt_info1->Value = 32;
   else if(cb_zonebonus->ItemIndex == 2) // Magic
       edt_info1->Value = 64;
   else if(cb_zonebonus->ItemIndex == 3) // Key
       edt_info1->Value = 128;
   else if(cb_zonebonus->ItemIndex == 4) // Clove
       edt_info1->Value = 256;
   else if(cb_zonebonus->ItemIndex == 5) // Empty
       edt_info1->Value = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_snapChange(TObject *Sender)
{
   if(!Scene.Zones.empty())
   {
       Scene.Zones[edt_zones->Value].Snap = cb_snap->ItemIndex;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_newzoneClick(TObject *Sender)
{
    NewZone(0,0,0,512,256,512);
}
//---------------------------------------------------------------------------

void Tfrm_lba::NewZone(int x1, int y1, int z1, int x2, int y2, int z2)
{
   Scene.numZones++;

   TZone zone;
   zone.X0 = x1;
   zone.Y0 = y1;
   zone.Z0 = z1;
   zone.X1 = x2;
   zone.Y1 = y2;
   zone.Z1 = z2;
   zone.Type = 0;
   zone.Info0 = 0;
   zone.Info1 = 0;
   zone.Info2 = 0;
   zone.Info3 = 0;
   zone.Snap = 0;

   Scene.Zones.push_back(zone);
   
   StatusBar1->Panels->Items[2]->Text = "Zones: ";
   StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;

   if(Scene.numZones > 1){ // RECHECK
      edt_zones->MaxValue = Scene.numZones-1;
      /*if(edt_zones->Value==-1)
        edt_zones->Value = 0;*/
      edt_zones->Value = edt_zones->Value + 1;
      edt_zones->Enabled = True;
   }
   else{
        edt_zones->Value = 0;
        edt_bzoneX->Enabled = True;
        edt_bzoneY->Enabled = True;
        edt_bzoneZ->Enabled = True;
        scroll_bzoneX->Enabled = True;
        scroll_bzoneY->Enabled = True;
        scroll_bzoneZ->Enabled = True;
        edt_zonedimX->Enabled = True;
        edt_zonedimY->Enabled = True;
        edt_zonedimZ->Enabled = True;
        cb_zonetype->Enabled = True;
        edt_info0->Enabled = True;
        edt_info1->Enabled = True;
        edt_info2->Enabled = True;
        edt_info3->Enabled = True;
        cb_snap->Enabled = True;
        cb_zonebonus->Enabled = True;
        bt_removezone->Enabled = True;
        bt_clonezone->Enabled = True;
   }

   SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
}

void __fastcall Tfrm_lba::bt_clonezoneClick(TObject *Sender)
{
    CloneZone(-1, -1, -1, -1, -1, -1);
}

void Tfrm_lba::CloneZone(int x1, int y1, int z1, int x2, int y2, int z2)
{
    // Put in front of the clone track
/*   Scene.Zones.push_back(Scene.Zones[Scene.numZones-1]);
   for(int a=Scene.numZones-1; a > edt_zones->Value; a--)
   {
       Scene.Zones[a] = Scene.Zones[a-1];
   }*/
   Scene.numZones++;

   TZone zone;

   if(x1!=-1 && y1!=-1 && z1!=-1 && x2!=-1 && y2!=-1 && z2!=-1)
   {
        zone.X0 = x1;
        zone.Y0 = y1;
        zone.Z0 = z1;
        zone.X1 = x2;
        zone.Y1 = y2;
        zone.Z1 = z2;
   }

   zone = Scene.Zones[edt_zones->Value];

   Scene.Zones.push_back(zone);

   StatusBar1->Panels->Items[2]->Text = "Zones: ";
   StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;

   if(Scene.numZones > 1){
      edt_zones->MaxValue = edt_zones->MaxValue + 1;
      edt_zones->Value = edt_zones->Value + 1;
      edt_zones->Enabled = True;
   }

   SetZoneCommand(zone,edt_zones->Value);
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::bt_removezoneClick(TObject *Sender)
{
    if(!Scene.Zones.empty())
	{
       if(IsConnected())
            DelAllZonesCommand();

		for(int a=edt_zones->Value; a < Scene.numZones; a++){
			Scene.Zones[a] = Scene.Zones[a+1];
		}
		Scene.Zones.pop_back();

        if(Scene.numZones > 0) // edt_zones->MaxValue != 0
        {
            Scene.numZones--;
		    StatusBar1->Panels->Items[2]->Text = "Zones: ";
		    StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;
            if(Scene.numZones != 0)
            {
                edt_zones->MaxValue = edt_zones->MaxValue - 1;
		        edt_zones->Value = edt_zones->Value - 1;
            }
        }

        // trick to update the values on the form
        if(edt_zones->Value==0)
        {
            edt_zones->Value = 1;
            edt_zones->Value = 0;
        }

        if(Scene.numZones == 1)
            edt_zones->Enabled = False;
        else
            edt_zones->Enabled = True;

        if(Scene.numZones==0)
        {
            edt_zones->Value = 0;
		    edt_bzoneX->Value = 0;
            edt_bzoneY->Value = 0;
            edt_bzoneZ->Value = 0;
            edt_zonedimX->Value = 0;
            edt_zonedimY->Value = 0;
            edt_zonedimZ->Value = 0;
            cb_zonetype->ItemIndex = 0;
            edt_info0->Value = 0;
            edt_info1->Value = 0;
            edt_info2->Value = 0;
            edt_info3->Value = 0;
            cb_snap->ItemIndex = 0;
            cb_zonebonus->ItemIndex = 0;

            /* Scene.numZones--;
		    StatusBar1->Panels->Items[2]->Text = "Zones: ";
		    StatusBar1->Panels->Items[2]->Text = StatusBar1->Panels->Items[2]->Text + Scene.numZones;
            */

            edt_zones->Enabled = False;
            edt_bzoneX->Enabled = False;
            edt_bzoneY->Enabled = False;
            edt_bzoneZ->Enabled = False;
            scroll_bzoneX->Enabled = False;
            scroll_bzoneY->Enabled = False;
            scroll_bzoneZ->Enabled = False;
            edt_zonedimX->Enabled = False;
            edt_zonedimY->Enabled = False;
            edt_zonedimZ->Enabled = False;
            cb_zonetype->Enabled = False;
            edt_info0->Enabled = False;
            edt_info1->Enabled = False;
            edt_info2->Enabled = False;
            edt_info3->Enabled = False;
            cb_snap->Enabled = False;
            cb_zonebonus->Enabled = False;
            bt_removezone->Enabled = False;
            bt_clonezone->Enabled = False;
        }

        if(IsConnected())
        {
            SendBeginUpdate();
            for(int i=0; i < Scene.numZones; i++)
            {
                SetZoneCommand(Scene.Zones[i],i);
            }
            SendEndUpdate();
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_actorNameChange(TObject *Sender)
{
   if(!Scene.Actors.empty()){
      strcpy(Scene.Actors[edt_actors->Value-1].Name, edt_actorName->Text.c_str());
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_loadClick(TObject *Sender)
{
   OpenDialog1->Title = "Load LBA1 and LBA2 Binary and Text Scenes";
   OpenDialog1->Filter = "All known files (*.spc, *.ls1, *.ls2, *.sce, *.hqr)|*.scp;*.ls1;*.ls2;*.sce;scene.hqr|LBA1 Binary Scene files (*.ls1)|*.ls1|LBA2 Binary Scene files (*.ls2)|*.ls2|LBA1 Text Scene files (*.sce)|*.sce|LBA1/2 High Quality Resource scene file (*.hqr)|scene.hqr";

   OpenDialog1->InitialDir = lastLoadDir;

   
   if(OpenDialog1->Execute())
   {
        close3rdParty(); // Close Builder.exe by Zink

        if(frm_actorscript->Showing)
            frm_actorscript->Close();
        if(frm_staticpar->Showing)
            frm_staticpar->Close();
        if(frm_scripthelp->Showing)
            frm_scripthelp->Close();

        clearScene();

        if(IsConnected())
        {
            DelAllTracksCommand();
            DelAllZonesCommand();
            DelAllActorsCommand();
        }


        Path = OpenDialog1->FileName;

        if(!StrPos(LowerCase(Path).c_str(),"scene.hqr"))
            lastScene = Path;

        if(StrPos(LowerCase(Path).c_str(),".ls1")){
            isLBA2 = false;
            sceneIdx = -1;
            Scene = loadBinaryScene(Path.c_str(),sceneIdx);
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
        }
        else if(StrPos(LowerCase(Path).c_str(),".sce"))
        {
            isLBA2 = false;
            Scene = loadTextScene(Path.c_str());
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
        }
        else if(StrPos(LowerCase(Path).c_str(),".ls2")){  // LBA2 binary mode
            isLBA2 = true;
            sceneIdx = -1;
            Scene = loadBinaryScene2(Path.c_str(),sceneIdx);
            if(filesize!=-1){
                putInitScene();
                bt_reload->Enabled = True;
                menu_reload->Enabled = True;
                bt_close->Enabled = True;
                menu_close->Enabled = True;
                bt_save->Enabled = True;
                menu_save->Enabled = True;
                bt_saveas->Enabled = True;
                menu_saveas->Enabled = True;
                menu_builder->Enabled = True;
                pl_scene->Visible = True;
            }
        }
        else if(StrPos(LowerCase(Path).c_str(),"scene.hqr")){  // LBA1 HQR Binary mode
            if(getNumEntries(Path.c_str()) == 120) // LBA1 scenes
                isLBA2 = false;
            else if(getNumEntries(Path.c_str()) == 223) // LBA2 scenes
                isLBA2 = true;
            frm_selectroom->ShowModal();
        }
        else
            ShowMessage("This program doens't support this file!");
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_reloadClick(TObject *Sender)
{
   if(StrPos(LowerCase(Path).c_str(),".ls1")){
        isLBA2 = false;
        sceneIdx = -1;
        Scene = loadBinaryScene(Path.c_str(),sceneIdx);
        if(filesize!=-1){
            putInitScene();
            bt_reload->Enabled = True;
            menu_reload->Enabled = True;
            bt_close->Enabled = True;
            menu_close->Enabled = True;
            bt_save->Enabled = True;
            menu_save->Enabled = True;
            bt_saveas->Enabled = True;
            menu_saveas->Enabled = True;
            menu_builder->Enabled = True;
            pl_scene->Visible = True;
        }
   }
   else if(StrPos(LowerCase(Path).c_str(),".sce"))
   {
        isLBA2 = false;
        Scene = loadTextScene(Path.c_str());
        if(filesize!=-1){
            putInitScene();
            bt_reload->Enabled = True;
            menu_reload->Enabled = True;
            bt_close->Enabled = True;
            menu_close->Enabled = True;
            bt_save->Enabled = True;
            menu_save->Enabled = True;
            bt_saveas->Enabled = True;
            menu_saveas->Enabled = True;
            menu_builder->Enabled = True;
            pl_scene->Visible = True;
        }
   }
   else if(StrPos(LowerCase(Path).c_str(),".ls2")){  // LBA2 binary mode
       isLBA2 = true;
       sceneIdx = -1;
       Scene = loadBinaryScene2(Path.c_str(),sceneIdx);
       if(filesize!=-1){
          putInitScene();
          bt_reload->Enabled = True;
          menu_reload->Enabled = True;
          bt_close->Enabled = True;
          menu_close->Enabled = True;
          bt_save->Enabled = True;
          menu_save->Enabled = True;
          bt_saveas->Enabled = True;
          menu_saveas->Enabled = True;
          menu_builder->Enabled = True;
          pl_scene->Visible = True;
       }
   }
   else if(StrPos(LowerCase(Path).c_str(),"scene.hqr")){  // LBA1 HQR Binary mode
        if(getNumEntries(Path.c_str()) == 120) // LBA1 scenes
          isLBA2 = false;
        else if(getNumEntries(Path.c_str()) == 223) // LBA2 scenes
          isLBA2 = true;
        frm_selectroom->ShowModal();
   }
   else
       ShowMessage("The program couldn't reload the file!");

   if(IsConnected())
      menu_builderClick(this);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_saveClick(TObject *Sender)
{
   if(!isLBA2)
   {
      if(StrPos(LowerCase(Path).c_str(),".scp")){
          saveSceneProject(Scene,Path.c_str());

          lastSaveDir = ExtractFileDir(Path);
      }
      else
      {
          SaveDialog1->Title = "Save LBA Story Coder Project";
          SaveDialog1->Filter = "LBA Story Coder Project (*.scp)|*.scp";
          SaveDialog1->FileName = Path;
          SaveDialog1->InitialDir = lastSaveDir;

          if(SaveDialog1->Execute()){
              AnsiString tmp = SaveDialog1->FileName;

              if(!StrPos(LowerCase(tmp).c_str(),".scp"))
                 tmp = tmp + ".scp";

              saveSceneProject(Scene,tmp.c_str());

              lastSaveDir = ExtractFileDir(tmp);
          }
      }
   }
   else
      ShowMessage("This version doesn't support projects for LBA2 scenes.");
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_cubeChange(TObject *Sender)
{
    Scene.CubeEntry = edt_cube->Value; 
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_textbankChange(TObject *Sender)
{
    Scene.TextBank = cb_textbank->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_cubemusicChange(TObject *Sender)
{
   Scene.CubeMusic = cb_cubemusic->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_alphaChange(TObject *Sender)
{
    Scene.AlphaLight = edt_alpha->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_betaChange(TObject *Sender)
{
    Scene.BetaLight = edt_beta->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_secondminChange(TObject *Sender)
{
    Scene.Second_Min = edt_secondmin->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_secondecartChange(TObject *Sender)
{
    Scene.Second_Ecart = edt_secondecart->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb01Change(TObject *Sender)
{
    Scene.Amb0_1 = edt_amb01->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb02Change(TObject *Sender)
{
    Scene.Amb0_2 = edt_amb02->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb03Change(TObject *Sender)
{
    Scene.Amb0_3 = edt_amb03->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb21Change(TObject *Sender)
{
    Scene.Amb2_1 = edt_amb21->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb22Change(TObject *Sender)
{
    Scene.Amb2_2 = edt_amb22->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb23Change(TObject *Sender)
{
    Scene.Amb2_3 = edt_amb23->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb11Change(TObject *Sender)
{
    Scene.Amb1_1 = edt_amb11->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb12Change(TObject *Sender)
{
    Scene.Amb1_2 = edt_amb12->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb13Change(TObject *Sender)
{
    Scene.Amb1_3 = edt_amb13->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb31Change(TObject *Sender)
{
    Scene.Amb3_1 = edt_amb31->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb32Change(TObject *Sender)
{
    Scene.Amb3_2 = edt_amb32->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_amb33Change(TObject *Sender)
{
    Scene.Amb3_3 = edt_amb33->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::About2Click(TObject *Sender)
{
    frm_about->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::Button1Click(TObject *Sender)
{
   if(!isLBA2)
   {
      if(stayOnTop)
        frm_displayactor->ShowModal();
      else
        frm_displayactor->Show();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_newClick(TObject *Sender)
{
    TScene tmp;

    tmp.TextBank = 0;
    tmp.CubeEntry = 0;
    tmp.AlphaLight = 0;
    tmp.BetaLight = 0;
    tmp.Amb0_1 = 0;
    tmp.Amb0_2 = 0;
    tmp.Amb0_3 = 0;
    tmp.Amb0_4 = 0;
    tmp.Amb0_5 = 0;
    tmp.Amb1_1 = 0;
    tmp.Amb1_2 = 0;
    tmp.Amb1_3 = 0;
    tmp.Amb1_4 = 0;
    tmp.Amb1_5 = 0;
    tmp.Amb2_1 = 0;
    tmp.Amb2_2 = 0;
    tmp.Amb2_3 = 0;
    tmp.Amb2_4 = 0;
    tmp.Amb2_5 = 0;
    tmp.Amb3_1 = 0;
    tmp.Amb3_2 = 0;
    tmp.Amb3_3 = 0;
    tmp.Amb3_4 = 0;
    tmp.Amb3_5 = 0;
    tmp.Second_Min = 0;
    tmp.Second_Ecart = 0;
    tmp.CubeMusic = 0;
    tmp.Hero.X = 0;
    tmp.Hero.Y = 0;
    tmp.Hero.Z = 0;
    tmp.Hero.trackScript = "END\n";
    tmp.Hero.lifeScript = "END\n";
    tmp.numActors = 1;
    tmp.Actors.clear();
    tmp.numTracks = 0;
    tmp.Tracks.clear();
    tmp.numZones = 0;
    tmp.Zones.clear();

    Scene = tmp;
    // Message to choose the scenes
    clearScene();
    putInitScene();
    edt_actors->Enabled = False;

    bt_reload->Enabled = True;
    menu_reload->Enabled = True;
    bt_close->Enabled = True;
    menu_close->Enabled = True;
    bt_save->Enabled = True;
    menu_save->Enabled = True;
    bt_saveas->Enabled = True;
    menu_saveas->Enabled = True;
    menu_builder->Enabled = True;
    pl_scene->Visible = True;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::Help4Click(TObject *Sender)
{
   Application->HelpCommand(HELP_FINDER, 0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::Checknewversion1Click(TObject *Sender)
{
  AnsiString tmp = "http://sacredcarrot.fishos.cc/storycoder.php?vnum=";
  tmp+=vnum;
  ShellExecute(Handle,"open",tmp.c_str(),NULL,NULL,SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::BugTrackingSystem1Click(TObject *Sender)
{
  ShellExecute(Handle,"open","http://sacredcarrot.fishos.cc/mantis/project_issues.php?project_id=15;1",NULL,NULL,SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::TheSacredCarrotwebsite1Click(TObject *Sender)
{
  ShellExecute(Handle,"open","http://sacredcarrot.fishos.cc",NULL,NULL,SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::LBACommunityHomePage1Click(TObject *Sender)
{
  ShellExecute(Handle,"open","http://www.magicball.net/forum",NULL,NULL,SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::cb_controlmodeChange(TObject *Sender)
{
   if(edt_actors->Value!=0){
        if(!Scene.Actors.empty()){
          Scene.Actors[edt_actors->Value-1].Move = cb_controlmode->ItemIndex;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::WhatsThis1Help(TObject *Sender,
      TObject *HelpItem, bool IsMenu, THelpContext HContext, int X, int Y,
      bool &CallHelp)
{
  WinHelp(Application->Handle, helpPath.c_str(), HELP_CONTEXTPOPUP, (int)HContext);
  CallHelp = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_exitClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::TimeOutTimer(TObject *Sender)
{
    countTime += TimeOut->Interval;
    if(countTime >= 30000) // 30s
    {
        countTime = 0;
        TimeOut->Enabled = False;
        ShowMessage("LBArchitect Builder Connection Time Out!");
    }
    else
    {
        if(IsConnected())
        {
            SetHeroCommand(Scene.Hero);

            // Set Track in Builder
            SendBeginUpdate();
            for(int i=0; i < Scene.numTracks; i++)
            {
                SetTrackCommand(Scene.Tracks[i]);
            }

            // Set Zone in Builder
            for(int i=0; i < Scene.numZones; i++)
            {
                SetZoneCommand(Scene.Zones[i],i);
            }

            // Set Actor in Builder
            for(int i=0; i < Scene.numActors-1; i++)
            {
                SetActorCommand(Scene.Actors[i],i+1);
            }
            SendEndUpdate();

            countTime = 0;
            TimeOut->Enabled = False;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::ToolButton5Click(TObject *Sender)
{
    stayOnTop = !stayOnTop;
    if(stayOnTop)
    {
        frm_lba->FormStyle = fsStayOnTop;
    }
    else
    {
        frm_lba->FormStyle = fsNormal;
    }
    DragAcceptFiles(Handle,true);
    BackwardConnection(frm_lba->Handle);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_builderClick(TObject *Sender)
{
      // open LBArchitect Builder after open the scene
      if(builderPath != "")
      {
          int tmp=0;
          // get the scene index
          if(StrPos(LowerCase(Path).c_str(),"scene.hqr"))
          {
             tmp = sceneIdx+1;
          }
          // TODO: Do a better number recognition.
          else if(StrPos(LowerCase(Path).c_str(),"scene"))
          {
              AnsiString tmp2 = ExtractFileName(Path).SubString(6,3);
              tmp = tmp2.ToIntDef(0);
          }
          else
          {
              AnsiString tmp2 = ExtractFileName(Path).SubString(0,3);
              tmp = tmp2.ToIntDef(0);
          }

          // if the file name doesn't have scene numbers, choose a grid to open.
          if(tmp==0){
              frm_selectgrid->ShowModal();
              // if the file name doesn't have scene numbers he don't do nothing
              if(sceneIdx==-1)
                return;
              tmp = sceneIdx+1;
          }

          // conversion between scenes numbers and grid entries.
          if(isLBA2){
              tmp = gridConv[tmp-1];
              tmp--;
          }

          if(!IsConnected()){
              AnsiString bPath = builderPath;
              bPath = bPath + " scenemode ";

              if(!isLBA2)
                  bPath = bPath + "1 "; // open LBA1 grids
              else {
                  bPath = bPath + "2 "; // open LBA2 grids
              }

              bPath = bPath + tmp; // pass the scene index

              WinExec(bPath.c_str(),SW_MAXIMIZE);
              BackwardConnection(frm_lba->Handle);
          }
          else
          {
              reloadGrid(tmp);
              BackwardConnection(frm_lba->Handle);
          }

          TimeOut->Enabled = True;
      }
      else
        ShowMessage("Setup the path for LBArchitect Builder in Settings menu!");
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_bzoneYChange(TObject *Sender)
{
   edt_bzoneY->Value = (scroll_bzoneY->Position - 32767) * (-1);
   img_bzoneY->Top = 103 - (edt_bzoneY->Value * 83) / 32767;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_bzoneZChange(TObject *Sender)
{
   edt_bzoneZ->Value = scroll_bzoneZ->Position;
   img_bzonepos->Top = 50 - ((32511 - edt_bzoneZ->Value) * 46) / 32511 + (edt_bzoneX->Value * 46) / 32511;
   img_bzonepos->Left = 7 + ((32511 - edt_bzoneZ->Value) * 46) / 32511 + (edt_bzoneX->Value * 46) / 32511;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_bzoneXChange(TObject *Sender)
{
   edt_bzoneX->Value = scroll_bzoneX->Position;
   img_bzonepos->Top = 50 + ((edt_bzoneX->Value) * 46) / 32511 - ((32511 - edt_bzoneZ->Value) * 46) / 32511;
   img_bzonepos->Left = 7 + ((edt_bzoneX->Value) * 46) / 32511 + ((32511 - edt_bzoneZ->Value) * 46) / 32511;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_trackYChange(TObject *Sender)
{
   edt_trackY->Value = (scroll_trackY->Position - 32767) * (-1);
   img_trackY->Top = 119 - (edt_trackY->Value * 83) / 32767;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_trackZChange(TObject *Sender)
{
   edt_trackZ->Value = scroll_trackZ->Position;
   img_trackpos->Top = 66 - ((32767 - edt_trackZ->Value) * 46) / 32767 + (edt_trackX->Value * 46) / 32767;
   img_trackpos->Left = 7 + ((32767 - edt_trackZ->Value) * 46) / 32767 + (edt_trackX->Value * 46) / 32767;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_trackXChange(TObject *Sender)
{
   edt_trackX->Value = scroll_trackX->Position;
   img_trackpos->Top = 66 + ((edt_trackX->Value) * 46) / 32767 - ((32767 - edt_trackZ->Value) * 46) / 32767;
   img_trackpos->Left = 7 + ((edt_trackX->Value) * 46) / 32767 + ((32767 - edt_trackZ->Value) * 46) / 32767;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_actorXChange(TObject *Sender)
{
   edt_actorX->Value = scroll_actorX->Position;
   img_actorpos->Top = 45 + ((edt_actorX->Value) * 46) / 32767 - ((32767 - edt_actorZ->Value) * 46) / 32767;
   img_actorpos->Left = 0 + ((edt_actorX->Value) * 46) / 32767 + ((32767 - edt_actorZ->Value) * 46) / 32767;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_actorZChange(TObject *Sender)
{
   edt_actorZ->Value = scroll_actorZ->Position;
   img_actorpos->Top = 45 - ((32767 - edt_actorZ->Value) * 46) / 32767 + (edt_actorX->Value * 46) / 32767;
   img_actorpos->Left = 0 + ((32767 - edt_actorZ->Value) * 46) / 32767 + (edt_actorX->Value * 46) / 32767;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_actorYChange(TObject *Sender)
{
   edt_actorY->Value = (scroll_actorY->Position - 32767) * (-1);
   img_actorY->Top = 95 - (edt_actorY->Value * 83) / 32767;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::scroll_angleChange(TObject *Sender)
{
   edt_angle->Text = scroll_angle->Position;
   edt_angle->Text = edt_angle->Text + " - [";
   edt_angle->Text = edt_angle->Text + (360*scroll_angle->Position) / 32767;
   edt_angle->Text = edt_angle->Text + " \xB0]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_zonedimXChange(TObject *Sender)
{
    edt_bzoneX->MaxValue = 32511 - edt_zonedimX->Value;
    scroll_bzoneX->Max = 32511 - edt_zonedimX->Value;
    Scene.Zones[edt_zones->Value].X1 = Scene.Zones[edt_zones->Value].X0 + edt_zonedimX->Value;
   // if(IsConnected())
        SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_zonedimYChange(TObject *Sender)
{
    edt_bzoneY->MaxValue = 32767 - edt_zonedimY->Value;
    scroll_bzoneY->Max = (32767 - edt_zonedimY->Value) * (-1);
    Scene.Zones[edt_zones->Value].Y1 = Scene.Zones[edt_zones->Value].Y0 + edt_zonedimY->Value;
  //  if(IsConnected())
        SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::edt_zonedimZChange(TObject *Sender)
{
    edt_bzoneZ->MaxValue = 32511 - edt_zonedimZ->Value;
    scroll_bzoneZ->Max = 32511 - edt_zonedimZ->Value;
    Scene.Zones[edt_zones->Value].Z1 = Scene.Zones[edt_zones->Value].Z0 + edt_zonedimZ->Value;
  //  if(IsConnected())
    SetZoneCommand(Scene.Zones[edt_zones->Value],edt_zones->Value);    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::menu_batchsavingClick(TObject *Sender)
{
    frm_batchsaving->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lba::pl_sceneChange(TObject *Sender)
{
    switch(pl_scene->ActivePageIndex) // Track
    {
        case 1: SelectActorCommand(edt_actors->Value); break;
        case 2: SelectTrackCommand(Scene.Tracks[edt_tracks->Value].Num); break;
        case 3: SelectZoneCommand(edt_zones->Value); break;
    }
}
//---------------------------------------------------------------------------


