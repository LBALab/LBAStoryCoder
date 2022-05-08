/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
---------------------------[ ActorScriptEd.cpp ]-----------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Sun Dec 26 2004
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

#pragma hdrstop

#include "ActorScriptEd.h"
#include "SceneLib.h"
#include "LBAStoryCoder_main.h"
#include "Settings.h"
#include "ScriptHelp.h"
#include "TrackScriptIntelliSense.h"
#include "LifeScriptIntelliSense.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rsBNFParser"
#pragma link "rsColorSyntax"
#pragma link "rsParserAll"
#pragma link "rsParserData"
#pragma link "rsBNFParser"
#pragma link "rsColorSyntax"
#pragma link "rsParserAll"
#pragma link "rsParserData"
#pragma link "rsBNFParser"
#pragma link "rsColorSyntax"
#pragma link "rsParserAll"
#pragma link "rsParserData"
#pragma resource "*.dfm"
Tfrm_actorscript *frm_actorscript;

//-----------
extern bool syntaxHighlight;
extern TScene Scene;

extern TColor comp;
extern TColor cond;
extern TColor condvars;
extern TColor macros;
extern TColor numbers;
extern TColor comments;
extern TColor tracklabel;
extern TColor trackstop;
extern TColor trackmacros;
extern bool isLBA2;

int reselection;

//---------------------------------------------------------------------------
__fastcall Tfrm_actorscript::Tfrm_actorscript(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void Tfrm_actorscript::loadLifeScript()
{
   if(frm_lba->edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
           re_lifescript->Clear();
           re_lifescript->Text = Scene.Actors[frm_lba->edt_actors->Value-1].lifeScript;
       }
   }
   else{
       re_lifescript->Clear();
       re_lifescript->Text = Scene.Hero.lifeScript;
   }
   LifeSyntax->RefreshAllControl();
}
//---------------------------------------------------------------------------

void Tfrm_actorscript::loadTrackScript()
{
   if(frm_lba->edt_actors->Value!=0){
       if(!Scene.Actors.empty()){
           re_movescript->Clear();
           re_movescript->Text = Scene.Actors[frm_lba->edt_actors->Value-1].trackScript;
       }
   }
   else{
       re_movescript->Clear();
       re_movescript->Text = Scene.Hero.trackScript;
   }
   TrackSyntax->RefreshAllControl();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::FormShow(TObject *Sender)
{
   loadTrackScript();
   loadLifeScript();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::BitBtn2Click(TObject *Sender)
{
   re_lifescript->Undo();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::BitBtn1Click(TObject *Sender)
{
   re_movescript->Undo();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::cb_lifeWWClick(TObject *Sender)
{
   if(cb_lifeWW->Checked)
       re_lifescript->WordWrap = True;
   else
       re_lifescript->WordWrap = False;
   }
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::cb_moveWWClick(TObject *Sender)
{
   if(cb_moveWW->Checked)
       re_movescript->WordWrap = True;
   else
       re_movescript->WordWrap = False;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::BitBtn3Click(TObject *Sender)
{
   // code to replace carriaged return from the edited text ;)
   AnsiString tmp, tmp2;
   tmp = StringReplace(re_lifescript->Text, "\r\n", "\n", TReplaceFlags() << rfReplaceAll);
   tmp2 = StringReplace(re_movescript->Text, "\r\n", "\n", TReplaceFlags() << rfReplaceAll);
   re_lifescript->Text = tmp;
   re_movescript->Text = tmp2;
   // -------------------

   if(frm_lba->edt_actors->Value!=0){
       Scene.Actors[frm_lba->edt_actors->Value-1].lifeScript = new char[ re_lifescript->Text.Length() + 1 ];
       strcpy(Scene.Actors[frm_lba->edt_actors->Value-1].lifeScript, re_lifescript->Text.c_str() );
   }
   else{
       Scene.Hero.lifeScript = new char[ re_lifescript->Text.Length() + 1 ];
       strcpy(Scene.Hero.lifeScript, re_lifescript->Text.c_str() );
   }

   if(frm_lba->edt_actors->Value!=0){
       Scene.Actors[frm_lba->edt_actors->Value-1].trackScript = new char[ re_movescript->Text.Length() + 1 ];
       strcpy(Scene.Actors[frm_lba->edt_actors->Value-1].trackScript, re_movescript->Text.c_str() );
   }
   else{
       Scene.Hero.trackScript = new char[ re_movescript->Text.Length() + 1 ];
       strcpy(Scene.Hero.trackScript, re_movescript->Text.c_str() );
   }

   LifeSyntax->RefreshAllControl();
   TrackSyntax->RefreshAllControl();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::Button1Click(TObject *Sender)
{
    if(!isLBA2)
      frm_scripthelp->Show();
    else
      ShowMessage("The current script help is only for LBA1 scene files!");
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::re_lifescriptSelectionChange(
      TObject *Sender)
{
    TPoint p = re_lifescript->CaretPos;
    status_script->Panels->Items[0]->Text = p.y;
    status_script->Panels->Items[0]->Text += ": ";
    status_script->Panels->Items[0]->Text +=  p.x;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::re_movescriptSelectionChange(
      TObject *Sender)
{
    TPoint p = re_movescript->CaretPos;
    status_script->Panels->Items[2]->Text = p.y;
    status_script->Panels->Items[2]->Text += ": ";
    status_script->Panels->Items[2]->Text +=  p.x;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::re_lifescriptKeyPress(TObject *Sender,
      char &Key)
{
    TShiftState Shift = KeyboardStateToShiftState();

    if(Shift.Contains(ssCtrl) && Key==' ')
    {
        Key = '\0';
        // get scroll position
        TPoint pt = TPoint(0,0);
        SendMessage(re_lifescript->Handle, WM_USER+221, 0, (LPARAM) &pt);

        // put IntelliSense in the right place
        TPoint p = re_lifescript->CaretPos;
        int x = p.x*8 + 12;
        int y = p.y*16 + 45 - pt.y;
        frm_lifeIntelliSense->Left = frm_actorscript->Left+re_lifescript->Left+x;
        frm_lifeIntelliSense->Top = frm_actorscript->Top+re_lifescript->Top+y;
        frm_lifeIntelliSense->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_actorscript::re_movescriptKeyPress(TObject *Sender,
      char &Key)
{
    TShiftState Shift = KeyboardStateToShiftState();

    if(Shift.Contains(ssCtrl) && Key==' ')
    {
        Key = '\0';
        // get scroll position
        TPoint pt = TPoint(0,0);
        SendMessage(re_movescript->Handle, WM_USER+221, 0, (LPARAM) &pt);

        // put IntelliSense in the right place
        TPoint p = re_movescript->CaretPos;
        int x = p.x*8 + 12;
        int y = p.y*16 + 45 - pt.y;
        frm_trackIntelliSense->Left = frm_actorscript->Left+re_movescript->Left+x;
        frm_trackIntelliSense->Top = frm_actorscript->Top+re_movescript->Top+y;
        frm_trackIntelliSense->Show();
    }
}
//---------------------------------------------------------------------------

