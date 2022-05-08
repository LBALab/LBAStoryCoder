/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
----------------------------[ ModelViewer.cpp ]------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Sun Jun 24 2004
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

#include "ModelViewer.h"
#include "ModelLib.h"
#include "LBAStoryCoder_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_modelviewer *frm_modelviewer;
//---------------------------------------------------------------------------
__fastcall Tfrm_modelviewer::Tfrm_modelviewer(TComponent* Owner)
   : TForm(Owner)
{
   /*if(!glCreate(Panel1)){
     MessageBox(NULL, "Can't Create A GL Device Context", "Error", MB_OK);
     Close();
   }
   glInit(Panel1->Width, Panel1->Height);
   setModel(frm_lba->edt_entity->Value);
   start(Panel1, frm_lba->edt_entity->Value);
   if(frm_modelviewer->Active)
        Application->OnIdle = getDraw; */
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_modelviewer::FormDestroy(TObject *Sender)
{
  // glShutDwn(Panel1);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_modelviewer::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // glShutDwn(Panel1);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_modelviewer::FormResize(TObject *Sender)
{
  /* glInit(Panel1->Width, Panel1->Height);
   setModel(frm_lba->edt_entity->Value);
   start(Panel1, frm_lba->edt_entity->Value);
   if(frm_modelviewer->Active)
        Application->OnIdle = getDraw; */
}
//---------------------------------------------------------------------------

void _fastcall Tfrm_modelviewer::getDraw(TObject *o, bool &b)
{
 /*  Draw();
   b = false;  */
}
//---------------------------------------------------------------------------

void Tfrm_modelviewer::updateForm()
{
  /* glInit(Panel1->Width, Panel1->Height);
   setModel(frm_lba->edt_entity->Value);
   start(Panel1, frm_lba->edt_entity->Value);
   if(frm_modelviewer->Active)
        Application->OnIdle = getDraw;     */
}
