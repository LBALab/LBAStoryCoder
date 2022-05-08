/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004-2006
------------------------------[ Settings.cpp ]-------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Tus Aug 24 2004
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
#include <IniFiles.hpp>
#include <Registry.hpp>
#include <stdio.h>
#include <vector>
#include <fstream.h>
#pragma hdrstop

#include "Settings.h"
#include "LBAStoryCoder_main.h"
#include "HQRLib.h"
#include "SceneLib.h"
#include "Entities.h";
#include "ActorScriptEd.h";
#include "about.h";
#include "StaticParameters.h";
#include "DisplayActor.h";
#include "SelectScenes.h";
#include "SelectGrid.h";

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_settings *frm_settings;

extern TScene Scene;

// to save last 10 paths of opened files
vector<AnsiString> recentPath;

bool lastSceneCheck=true;
bool displayRoom=true;
bool stayOnTop=true;
bool scpType=true;
bool ls1Type=true;
bool ls2Type=true;
bool sceType=true;
bool useBrickCoord=true;
bool useBrickCoordActors=true;
bool useBrickCoordTracks=true;
bool useBrickCoordZones=true;

// Syntax highlight options
bool syntax=true;
TColor comp;
TColor cond;
TColor condvars;
TColor macros;
TColor numbers;
TColor comments;
TColor tracklabel;
TColor trackstop;
TColor trackmacros;

// backup lastthings
AnsiString lastLoadDir;
AnsiString lastSaveDir;
AnsiString lastScene;

// load file path
extern AnsiString Path;

// HQR files paths
extern AnsiString bodyPath;
extern AnsiString animPath;
extern AnsiString spritePath;
extern AnsiString entitiesPath;

// programs paths
extern AnsiString builderPath;
extern AnsiString modelViewerPath;
extern AnsiString spriteViewerPath;


extern entitiesTableStruct* entitiesStruct;

//---------------------------------------------------------------------------
__fastcall Tfrm_settings::Tfrm_settings(TComponent* Owner)
   : TForm(Owner)
{
    if(stayOnTop)
        frm_settings->FormStyle = fsStayOnTop;
    else
        frm_settings->FormStyle = fsNormal;
}
//---------------------------------------------------------------------------

void Tfrm_settings::saveSettings()
{
   TIniFile *ini;
   ini = new TIniFile(ExtractFileDir(Application->ExeName)+"\\config.ini");

   ini->WriteBool("General","lastScene",lastSceneCheck);
   ini->WriteBool("General","roomDesign",displayRoom);
   ini->WriteBool("General","stayOnTop",stayOnTop);   
   ini->WriteBool("General","useBrickCoord",useBrickCoord);
   ini->WriteBool("General","useBrickCoordActors",useBrickCoordActors);
   ini->WriteBool("General","useBrickCoordTracks",useBrickCoordTracks);
   ini->WriteBool("General","useBrickCoordZones",useBrickCoordZones);
   ini->WriteString("General","lastScenePath",lastScene);
   ini->WriteBool("Association","scp",scpType);
   ini->WriteBool("Association","ls1",ls1Type);
   ini->WriteBool("Association","ls2",ls2Type);   
   ini->WriteBool("Association","sce",sceType);
   ini->WriteString("Paths","builder",builderPath);
   ini->WriteString("Paths","modelViewer",modelViewerPath);
   ini->WriteString("Paths","spritesViewer",spriteViewerPath);
   ini->WriteString("HQRs","entities",entitiesPath);
   ini->WriteString("HQRs","body",bodyPath);
   ini->WriteString("HQRs","anim",animPath);
   ini->WriteString("HQRs","sprite",spritePath);
   ini->WriteString("Directories","lastLoad",lastLoadDir);
   ini->WriteString("Directories","lastSave",lastSaveDir);
   ini->WriteBool("Syntax","useSyntax",syntax);
   ini->WriteInteger("Syntax","colorComp",comp);
   ini->WriteInteger("Syntax","colorCond",cond);
   ini->WriteInteger("Syntax","colorCondVars",condvars);
   ini->WriteInteger("Syntax","colorMacros",macros);
   ini->WriteInteger("Syntax","colorNumbers",numbers);
   ini->WriteInteger("Syntax","colorComments",comments);
   ini->WriteInteger("Syntax","colorTrackLabel",tracklabel);
   ini->WriteInteger("Syntax","colorTrackStop",trackstop);
   ini->WriteInteger("Syntax","colorTrackMacros",trackmacros);

/*   if(!recentPath.empty())
      for(int i=0; i < 9; i++)
      {
           ini->WriteString("Recent",i,recentPath[i]);
      }   */

   delete ini;
}
//---------------------------------------------------------------------------

bool Tfrm_settings::loadSettings()
{
   String s = ExtractFileDir(Application->ExeName)+"\\config.ini";
   FILE *fileHandle;
   fileHandle = fopen(s.c_str(), "r");
   if (!fileHandle)
	    return true;

   TIniFile *ini;
   ini = new TIniFile(ExtractFileDir(Application->ExeName)+"\\config.ini");

   lastSceneCheck = ini->ReadBool("General","lastScene",true);
   displayRoom = ini->ReadBool("General","roomDesign",true);
   stayOnTop = ini->ReadBool("General","stayOnTop",true);
   useBrickCoord = ini->ReadBool("General","useBrickCoord",true);
   useBrickCoordActors = ini->ReadBool("General","useBrickCoordActors",true);
   useBrickCoordTracks = ini->ReadBool("General","useBrickCoordTracks",true);
   useBrickCoordZones = ini->ReadBool("General","useBrickCoordZones",true);
   lastScene = ini->ReadString("General","lastScenePath","");
   scpType = ini->ReadBool("Association","scp",true);
   ls1Type = ini->ReadBool("Association","ls1",true);
   ls2Type = ini->ReadBool("Association","ls2",true);
   sceType = ini->ReadBool("Association","sce",true);
   builderPath = ini->ReadString("Paths","builder","");
   modelViewerPath = ini->ReadString("Paths","modelViewer","");
   spriteViewerPath = ini->ReadString("Paths","spritesViewer","");
   entitiesPath = ini->ReadString("HQRs","entities","");
   bodyPath = ini->ReadString("HQRs","body","");
   animPath = ini->ReadString("HQRs","anim","");
   spritePath = ini->ReadString("HQRs","sprite","");
   lastLoadDir = ini->ReadString("Directories","lastLoad","");
   lastSaveDir = ini->ReadString("Directories","lastSave","");
   syntax = ini->ReadBool("Syntax","useSyntax",true);
   comp = ini->ReadInteger("Syntax","colorComp",clGreen);
   cond = ini->ReadInteger("Syntax","colorCond",clRed);
   condvars = ini->ReadInteger("Syntax","colorCondVars",clFuchsia);
   macros = ini->ReadInteger("Syntax","colorMacros",clBlue);
   numbers = ini->ReadInteger("Syntax","colorNumbers",clMaroon);
   comments = ini->ReadInteger("Syntax","colorComments",clTeal);
   tracklabel = ini->ReadInteger("Syntax","colorTrackLabel",clGreen);
   trackstop = ini->ReadInteger("Syntax","colorTrackStop",clRed);
   trackmacros = ini->ReadInteger("Syntax","colorTrackMacros",clBlue);

  /* for(int i=0; i < 9; i++)
   {
       if(ini->ValueExists("Recent",i)){
          AnsiString tmp = ini->ReadString("Recent",i,"").c_str();
          recentPath.push_back(tmp);
       }
       else
           break;
   } */

   SetAssociation();

   delete ini;
   return false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_settings::bt_builderDialogClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBArchitect Builder|Builder.exe";
   if(settings_opendialog->Execute())
   {
       edt_builderPath->Text = settings_opendialog->FileName;
       builderPath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::FormClose(TObject *Sender,
      TCloseAction &Action)
{

    saveSettings();
    SetAssociation();    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_defaultSyntaxColorsClick(TObject *Sender)
{
    color_comp->Selected = clGreen;
    comp = clGreen;
    color_cond->Selected = clRed;
    cond = clRed;
    color_condvars->Selected = clFuchsia;
    condvars = clFuchsia;
    color_macros->Selected = clBlue;
    macros = clBlue;
    color_numbers->Selected = clMaroon;
    numbers = clMaroon;
    color_comments->Selected = clTeal;
    comments = clTeal;

    color_tracklabel->Selected = clGreen;
    tracklabel = clGreen;
    color_trackstop->Selected = clRed;
    trackstop = clRed;
    color_trackmacros->Selected = clBlue;
    trackmacros = clBlue;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_3DModelDialogClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Story Coder Model Viewer|ModelViewer.exe";
   if(settings_opendialog->Execute())
   {
       edt_modelViewerPath->Text = settings_opendialog->FileName;
       modelViewerPath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_spritesDialogClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Story Coder Sprite Viewer|SpriteViewer.exe";
   if(settings_opendialog->Execute())
   {
       edt_spritesViewerPath->Text = settings_opendialog->FileName;
       spriteViewerPath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_entetiesDialogClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Models Enteties|File3D.HQR";
   if(settings_opendialog->Execute())
   {
       edt_entitiesPath->Text = settings_opendialog->FileName;
       entitiesPath = settings_opendialog->FileName;
       if(!entitiesPath.IsEmpty())
          entitiesStruct = parseEntities();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_bodyPathClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Models|Body.HQR";
   if(settings_opendialog->Execute())
   {
       edt_bodyPath->Text = settings_opendialog->FileName;
       bodyPath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::bt_spritesHQRDialogClick(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Sprites|Sprites.HQR";
   if(settings_opendialog->Execute())
   {
       edt_spritesPath->Text = settings_opendialog->FileName;
       spritePath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_lastsceneClick(TObject *Sender)
{
   lastSceneCheck = cb_lastscene->Checked;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_roomdesignClick(TObject *Sender)
{
    displayRoom = cb_roomdesign->Checked;
    if(displayRoom)
    {
        cb_stayontop->Enabled = True;
        cb_stayontop->Checked = True;
        stayOnTop = true;
    }
    else
    {
        cb_stayontop->Enabled = False;
        stayOnTop = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_brickcoordClick(TObject *Sender)
{
    useBrickCoord = cb_brickcoord->Checked;

    if(useBrickCoord)
    {
        cb_brickcoordActors->Enabled = True;
        cb_brickcoordTracks->Enabled = True;
        cb_brickcoordZones->Enabled = True;

        if(useBrickCoordActors)
        {
            frm_lba->edt_actorX->Increment = 512;
            frm_lba->edt_actorY->Increment = 256;
            frm_lba->edt_actorZ->Increment = 512;
        }
        else
        {
            frm_lba->edt_actorX->Increment = 1;
            frm_lba->edt_actorY->Increment = 1;
            frm_lba->edt_actorZ->Increment = 1;
        }

        if(useBrickCoordTracks)
        {
            frm_lba->edt_trackX->Increment = 512;
            frm_lba->edt_trackY->Increment = 256;
            frm_lba->edt_trackZ->Increment = 512;
        }
        else
        {
            frm_lba->edt_trackX->Increment = 1;
            frm_lba->edt_trackY->Increment = 1;
            frm_lba->edt_trackZ->Increment = 1;
        }

        if(useBrickCoordActors)
        {
            frm_lba->edt_bzoneX->Increment = 512;
            frm_lba->edt_bzoneY->Increment = 256;
            frm_lba->edt_bzoneZ->Increment = 512;
            frm_lba->edt_zonedimX->Increment = 512;
            frm_lba->edt_zonedimY->Increment = 256;
            frm_lba->edt_zonedimZ->Increment = 512;
        }
        else
        {
            frm_lba->edt_bzoneX->Increment = 1;
            frm_lba->edt_bzoneY->Increment = 1;
            frm_lba->edt_bzoneZ->Increment = 1;
            frm_lba->edt_zonedimX->Increment = 1;
            frm_lba->edt_zonedimY->Increment = 1;
            frm_lba->edt_zonedimZ->Increment = 1;
        }
    }
    else
    {
        cb_brickcoordActors->Enabled = False;
        cb_brickcoordTracks->Enabled = False;
        cb_brickcoordZones->Enabled = False;

        frm_lba->edt_actorX->Increment = 1;
        frm_lba->edt_actorY->Increment = 1;
        frm_lba->edt_actorZ->Increment = 1;
        frm_lba->edt_trackX->Increment = 1;
        frm_lba->edt_trackY->Increment = 1;
        frm_lba->edt_trackZ->Increment = 1;
        frm_lba->edt_bzoneX->Increment = 1;
        frm_lba->edt_bzoneY->Increment = 1;
        frm_lba->edt_bzoneZ->Increment = 1;
        frm_lba->edt_zonedimX->Increment = 1;
        frm_lba->edt_zonedimY->Increment = 1;
        frm_lba->edt_zonedimZ->Increment = 1;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_scpClick(TObject *Sender)
{
    scpType = cb_scp->Checked;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_ls1Click(TObject *Sender)
{
    ls1Type = cb_ls1->Checked;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_sceClick(TObject *Sender)
{
    sceType = cb_sce->Checked;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_syntaxClick(TObject *Sender)
{
    syntax = cb_syntax->Checked;
    if(!syntax)
    {
        frm_actorscript->LifeSyntax->DisableControl();
        frm_actorscript->TrackSyntax->DisableControl();
        frm_actorscript->LifeSyntax->RefreshAllControl();
        frm_actorscript->TrackSyntax->RefreshAllControl();
    }
    else
    {
        frm_actorscript->LifeSyntax->EnableControl();
        frm_actorscript->TrackSyntax->EnableControl();
        frm_actorscript->LifeSyntax->RefreshAllControl();
        frm_actorscript->TrackSyntax->RefreshAllControl();
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_compChange(TObject *Sender)
{
    comp = color_comp->Selected;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_condChange(TObject *Sender)
{
    cond = color_cond->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_condvarsChange(TObject *Sender)
{
    condvars = color_condvars->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_macrosChange(TObject *Sender)
{
    macros = color_macros->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_numbersChange(TObject *Sender)
{
    numbers = color_numbers->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_commentsChange(TObject *Sender)
{
    comments = color_comments->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_entitiesPathChange(TObject *Sender)
{
    entitiesPath = edt_entitiesPath->Text;
    if(!entitiesPath.IsEmpty())
      entitiesStruct = parseEntities();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_bodyPathChange(TObject *Sender)
{
    bodyPath = edt_bodyPath->Text;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_spritesPathChange(TObject *Sender)
{
    spritePath = edt_spritesPath->Text;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_builderPathChange(TObject *Sender)
{
    builderPath = edt_builderPath->Text;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_modelViewerPathChange(TObject *Sender)
{
    modelViewerPath = edt_modelViewerPath->Text;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::edt_spritesViewerPathChange(TObject *Sender)
{
    spriteViewerPath = edt_spritesViewerPath->Text;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_trackmacrosChange(TObject *Sender)
{
    trackmacros = color_trackmacros->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_tracklabelChange(TObject *Sender)
{
    tracklabel = color_tracklabel->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::color_trackstopChange(TObject *Sender)
{
    trackstop = color_trackstop->Selected;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_brickcoordActorsClick(TObject *Sender)
{
    useBrickCoordActors = cb_brickcoordActors->Checked;

    if(useBrickCoordActors && useBrickCoord)
    {
        frm_lba->edt_actorX->Increment = 512;
        frm_lba->edt_actorY->Increment = 256;
        frm_lba->edt_actorZ->Increment = 512;
    }
    else
    {
        frm_lba->edt_actorX->Increment = 1;
        frm_lba->edt_actorY->Increment = 1;
        frm_lba->edt_actorZ->Increment = 1;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_brickcoordTracksClick(TObject *Sender)
{
      useBrickCoordTracks = cb_brickcoordTracks->Checked;

    if(useBrickCoordTracks && useBrickCoord)
    {
        frm_lba->edt_trackX->Increment = 512;
        frm_lba->edt_trackY->Increment = 256;
        frm_lba->edt_trackZ->Increment = 512;
    }
    else
    {
        frm_lba->edt_trackX->Increment = 1;
        frm_lba->edt_trackY->Increment = 1;
        frm_lba->edt_trackZ->Increment = 1;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_brickcoordZonesClick(TObject *Sender)
{
    useBrickCoordZones = cb_brickcoordZones->Checked;

    if(useBrickCoordActors && useBrickCoord)
    {
        frm_lba->edt_bzoneX->Increment = 512;
        frm_lba->edt_bzoneY->Increment = 256;
        frm_lba->edt_bzoneZ->Increment = 512;
        frm_lba->edt_zonedimX->Increment = 512;
        frm_lba->edt_zonedimY->Increment = 256;
        frm_lba->edt_zonedimZ->Increment = 512;
    }
    else
    {
        frm_lba->edt_bzoneX->Increment = 1;
        frm_lba->edt_bzoneY->Increment = 1;
        frm_lba->edt_bzoneZ->Increment = 1;
        frm_lba->edt_zonedimX->Increment = 1;
        frm_lba->edt_zonedimY->Increment = 1;
        frm_lba->edt_zonedimZ->Increment = 1;
    }
}
//---------------------------------------------------------------------------

void Tfrm_settings::SetKey(AnsiString Key, AnsiString Icon, AnsiString Text){
   TRegIniFile *Rejestr = new TRegIniFile("");
   Rejestr->RootKey = HKEY_CLASSES_ROOT;
   Rejestr->WriteString("."+Key,"","LBA_"+Key+"_storycoder");
   Rejestr->WriteString("LBA_"+Key+"_storycoder","",Text);
   Rejestr->WriteString("LBA_"+Key+"_storycoder","Created by","LBA Story Coder");
   Rejestr->WriteString("LBA_"+Key+"_storycoder\\DefaultIcon","",Icon);
   Rejestr->WriteString("LBA_"+Key+"_storycoder\\shell","","open");
   Rejestr->WriteString("LBA_"+Key+"_storycoder\\shell\\open\\command","","\""+Application->ExeName+"\" "+"\"%1\"");
   Rejestr->Free();
}
//---------------------------------------------------------------------------
void Tfrm_settings::DelKey(AnsiString Key){
   TRegIniFile *Rejestr = new TRegIniFile("");
   Rejestr->RootKey = HKEY_CLASSES_ROOT;
   if(Rejestr->ReadString("LBA_"+Key+"_storycoder","Created by","") == "LBA Story Coder"){
       Rejestr->EraseSection("."+Key);
       Rejestr->EraseSection("LBA_"+Key+"_storycoder");
   }
   Rejestr->Free();
}
//---------------------------------------------------------------------------

void Tfrm_settings::SetAssociation(){
   (scpType) ? SetKey("scp",Application->ExeName+",1","LBA Story Coder project file") : DelKey("scp");
   (ls1Type) ? SetKey("ls1",Application->ExeName+",2","LBA1 Binary Scene file") : DelKey("ls1");
   (ls2Type) ? SetKey("ls2",Application->ExeName+",3","LBA2 Binary Scene file") : DelKey("ls2");
   (sceType) ? SetKey("sce",Application->ExeName+",4","LBA1 Text Scene file") : DelKey("sce");
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_ls2Click(TObject *Sender)
{
   ls2Type = cb_ls2->Checked; 
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::Button1Click(TObject *Sender)
{
   settings_opendialog->Filter = "LBA Animations|Anim.HQR";
   if(settings_opendialog->Execute())
   {
       edt_animPath->Text = settings_opendialog->FileName;
       animPath = settings_opendialog->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::FormShow(TObject *Sender)
{
   cb_lastscene->Checked = lastSceneCheck;
   cb_roomdesign->Checked = displayRoom;
   cb_stayontop->Checked = stayOnTop;
   cb_scp->Checked = scpType;
   cb_ls1->Checked = ls1Type;
   cb_ls2->Checked = ls2Type;
   cb_sce->Checked = sceType;
   edt_builderPath->Text = builderPath;
   edt_modelViewerPath->Text = modelViewerPath;
   edt_spritesViewerPath->Text = spriteViewerPath;
   edt_entitiesPath->Text = entitiesPath;
   edt_bodyPath->Text = bodyPath;
   edt_animPath->Text = animPath;
   edt_spritesPath->Text = spritePath;
  // cb_syntax->Checked = syntax;
  /* color_comp->Selected = comp;
   color_cond->Selected = cond;
   color_condvars->Selected = condvars;
   color_macros->Selected = macros;
   color_numbers->Selected = numbers;
   color_comments->Selected = comments;*/  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_settings::cb_stayontopClick(TObject *Sender)
{
    stayOnTop = cb_stayontop->Checked;
    if(stayOnTop)
    {
        frm_lba->FormStyle = fsStayOnTop;    
        frm_settings->FormStyle = fsStayOnTop;
    }
    else
    {
        frm_lba->FormStyle = fsNormal;
        frm_settings->FormStyle = fsNormal;
    }
   /* if(stayOnTop)
    {
        frm_lba->FormStyle = fsStayOnTop;
        frm_actorscript->FormStyle = fsStayOnTop;
        frm_settings->FormStyle = fsStayOnTop;
        frm_displayactor->FormStyle = fsStayOnTop;
        frm_selectroom->FormStyle = fsStayOnTop;
        frm_selectgrid->FormStyle = fsStayOnTop;
        frm_about->FormStyle = fsStayOnTop;
        frm_staticpar->FormStyle = fsStayOnTop;
    }
    else
    {
        frm_lba->FormStyle = fsNormal;
        frm_actorscript->FormStyle = fsNormal;
        frm_settings->FormStyle = fsNormal;
        frm_displayactor->FormStyle = fsNormal;
        frm_selectroom->FormStyle = fsNormal;
        frm_selectgrid->FormStyle = fsNormal;
        frm_about->FormStyle = fsNormal;
        frm_staticpar->FormStyle = fsNormal;
    } */
}
//---------------------------------------------------------------------------

