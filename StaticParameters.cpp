/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
---------------------------[ StaticParamters.cpp ]---------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Thu Aug 26 2004
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

#include "StaticParameters.h"
#include "SceneLib.h"
#include "LBAStoryCoder_main.h"
#include "Commands.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_staticpar *frm_staticpar;
extern TScene Scene;
unsigned short value;
extern bool stayOnTop;
//---------------------------------------------------------------------------
__fastcall Tfrm_staticpar::Tfrm_staticpar(TComponent* Owner)
   : TForm(Owner)
{
    if(stayOnTop)
        frm_staticpar->FormStyle = fsStayOnTop;
    else
        frm_staticpar->FormStyle = fsNormal;
}
//---------------------------------------------------------------------------

void Tfrm_staticpar::loadValues(unsigned short staticValue)
{
   if(staticValue & 0x1) // ComputeCollisionWithObj
       cb1->State = cbChecked;
   else
       cb1->State = cbUnchecked;

   if(staticValue & 0x2) // ComputeCollisionWithBricks
       cb2->State = cbChecked;
   else
       cb2->State = cbUnchecked;

   if(staticValue & 0x4) // IsZonable
       cb3->State = cbChecked;
   else
       cb3->State = cbUnchecked;

   if(staticValue & 0x8) // IsUsingClipping
       cb4->State = cbChecked;
   else
       cb4->State = cbUnchecked;

   if(staticValue & 0x10) // Can Push
       cb5->State = cbChecked;
   else
       cb5->State = cbUnchecked;

   if(staticValue & 0x20) // IsDead
       cb6->State = cbChecked;
   else
       cb6->State = cbUnchecked;

   if(staticValue & 0x40) // CanDrown
       cb7->State = cbChecked;
   else
       cb7->State = cbUnchecked;

   if(staticValue & 0x80) // Unk80
       cb8->State = cbChecked;
   else
       cb8->State = cbUnchecked;

   if(staticValue & 0x100) // Unk0100
       cb9->State = cbChecked;
   else
       cb9->State = cbUnchecked;

   if(staticValue & 0x200) // Hidden
       cb10->State = cbChecked;
   else
       cb10->State = cbUnchecked;

   if(staticValue & 0x400) // Is Sprite Actor
       cb11->State = cbChecked;
   else
       cb11->State = cbUnchecked;

   if(staticValue & 0x800) // Can Fall
       cb12->State = cbChecked;
   else
       cb12->State = cbUnchecked;

   if(staticValue & 0x1000) // DoesntCastShadow
       cb13->State = cbChecked;
   else
       cb13->State = cbUnchecked;

   if(staticValue & 0x2000) // IsBackgrounded
       cb14->State = cbChecked;
   else
       cb14->State = cbUnchecked;

   if(staticValue & 0x4000) // IsCarrier
       cb15->State = cbChecked;
   else
       cb15->State = cbUnchecked;

   if(staticValue & 0x8000) // IsUsingMiniZv
       cb16->State = cbChecked;
   else
       cb16->State = cbUnchecked;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb1Click(TObject *Sender)
{
   if(cb1->State == cbChecked)
       value |= 0x1; // Bit On
   else
       value &= ~0x1; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb2Click(TObject *Sender)
{
   if(cb2->State == cbChecked)
       value |= 0x2; // Bit On
   else
       value &= ~0x2; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb3Click(TObject *Sender)
{
   if(cb3->State == cbChecked)
       value |= 0x4; // Bit On
   else
       value &= ~0x4; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb4Click(TObject *Sender)
{
   if(cb4->State == cbChecked)
       value |= 0x8; // Bit On
   else
       value &= ~0x8; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb5Click(TObject *Sender)
{
   if(cb5->State == cbChecked)
       value |= 0x10; // Bit On
   else
       value &= ~0x10; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb6Click(TObject *Sender)
{
   if(cb6->State == cbChecked)
       value |= 0x20; // Bit On
   else
       value &= ~0x20; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb7Click(TObject *Sender)
{
   if(cb7->State == cbChecked)
       value |= 0x40; // Bit On
   else
       value &= ~0x40; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb8Click(TObject *Sender)
{
   if(cb8->State == cbChecked)
       value |= 0x80; // Bit On
   else
       value &= ~0x80; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb9Click(TObject *Sender)
{
   if(cb9->State == cbChecked)
       value |= 0x100; // Bit On
   else
       value &= ~0x100; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb10Click(TObject *Sender)
{
   if(cb10->State == cbChecked)
       value |= 0x200; // Bit On
   else
       value &= ~0x200; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb11Click(TObject *Sender)
{
   if(cb11->State == cbChecked)
       value |= 0x400; // Bit On
   else
       value &= ~0x400; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;

   if(frm_lba->edt_staticflag->Caption.ToInt() & 0x400){
           frm_lba->bt_staticpar->Enabled = True;
           frm_lba->edt_entity->Enabled = False;
           frm_lba->edt_body->Enabled = False;
           frm_lba->edt_animation->Enabled = False;
           frm_lba->edt_sprite->Enabled = True;
           frm_lba->edt_hit->Enabled = False;
           frm_lba->edt_bonus->Enabled = False;
           frm_lba->cb_bonus->Enabled = False;
           frm_lba->edt_speed->Enabled = False;
           frm_lba->edt_amount->Enabled = False;
           frm_lba->edt_talkcolor->Enabled = False;
           frm_lba->edt_armour->Enabled = False;
           frm_lba->edt_points->Enabled = False;
           frm_lba->scroll_angle->Enabled = False;
           frm_lba->edt_angle->Enabled = False;
           frm_lba->edt_cropleft->Enabled = True;
           frm_lba->edt_croptop->Enabled = True;
           frm_lba->edt_cropright->Enabled = True;
           frm_lba->edt_cropbottom->Enabled = True;
           if(frm_lba->edt_sprite->Value > frm_lba->edt_sprite->MaxValue)
              frm_lba->edt_sprite->Value = 0;
    }
    else
    {
           frm_lba->bt_staticpar->Enabled = True;
           frm_lba->edt_entity->Enabled = True;
           frm_lba->edt_body->Enabled = True;
           frm_lba->edt_animation->Enabled = True;
           frm_lba->edt_sprite->Enabled = False;
           frm_lba->edt_hit->Enabled = True;
           frm_lba->edt_bonus->Enabled = True;
           frm_lba->cb_bonus->Enabled = True;
           frm_lba->edt_speed->Enabled = True;
           frm_lba->edt_amount->Enabled = True;
           frm_lba->edt_talkcolor->Enabled = True;
           frm_lba->edt_armour->Enabled = True;
           frm_lba->edt_points->Enabled = True;
           frm_lba->scroll_angle->Enabled = True;
           frm_lba->edt_angle->Enabled = True;
           frm_lba->edt_cropleft->Enabled = False;
           frm_lba->edt_croptop->Enabled = False;
           frm_lba->edt_cropright->Enabled = False;
           frm_lba->edt_cropbottom->Enabled = False;
           if(frm_lba->edt_entity->Value > frm_lba->edt_entity->MaxValue)
              frm_lba->edt_entity->Value = 0;
    }

    SetActorCommand(Scene.Actors[frm_lba->edt_actors->Value-1],frm_lba->edt_actors->Value);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb12Click(TObject *Sender)
{
   if(cb12->State == cbChecked)
       value |= 0x800; // Bit On
   else
       value &= ~0x800; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb13Click(TObject *Sender)
{
   if(cb13->State == cbChecked)
       value |= 0x1000; // Bit On
   else
       value &= ~0x1000; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb14Click(TObject *Sender)
{
   if(cb14->State == cbChecked)
       value |= 0x2000; // Bit On
   else
       value &= ~0x2000; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb15Click(TObject *Sender)
{
   if(cb15->State == cbChecked)
       value |= 0x4000; // Bit On
   else
       value &= ~0x4000; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::cb16Click(TObject *Sender)
{
   if(cb16->State == cbChecked)
       value |= 0x8000; // Bit On
   else
       value &= ~0x8000; // Bit Off
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_staticpar::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag = value;
   frm_lba->edt_staticflag->Caption = value;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_staticpar::FormShow(TObject *Sender)
{
   value = Scene.Actors[frm_lba->edt_actors->Value - 1].staticFlag;
   loadValues(value);
}
//---------------------------------------------------------------------------

