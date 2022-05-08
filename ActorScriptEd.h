/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
----------------------------[ ADctorScriptEd.h ]-----------------------------

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

#ifndef ActorScriptEdH
#define ActorScriptEdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "rsBNFParser.hpp"
#include "rsColorSyntax.hpp"
#include "rsParserAll.hpp"
#include "rsParserData.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class Tfrm_actorscript : public TForm
{
__published:	// IDE-managed Components
   TRichEdit *re_movescript;
   TLabel *Label2;
   TBitBtn *BitBtn1;
   TLabel *Label4;
   TBitBtn *BitBtn2;
   TCheckBox *cb_lifeWW;
   TCheckBox *cb_moveWW;
   TBitBtn *BitBtn3;
    TButton *Button1;
  TRichEdit *re_lifescript;
    TColorSyntax *LifeSyntax;
    TParserAll *LifeParser;
    TColorSyntax *TrackSyntax;
    TParserAll *TrackParser;
    TStatusBar *status_script;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall cb_lifeWWClick(TObject *Sender);
   void __fastcall cb_moveWWClick(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall re_lifescriptSelectionChange(TObject *Sender);
    void __fastcall re_movescriptSelectionChange(TObject *Sender);
    void __fastcall re_lifescriptKeyPress(TObject *Sender, char &Key);
    void __fastcall re_movescriptKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
   void loadLifeScript();
   void loadTrackScript();
   __fastcall Tfrm_actorscript(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_actorscript *frm_actorscript;
//---------------------------------------------------------------------------
#endif
