/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
----------------------------[ StaticParamters.h ]----------------------------

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

#ifndef StaticParametersH
#define StaticParametersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrm_staticpar : public TForm
{
__published:	// IDE-managed Components
   TCheckBox *cb1;
   TCheckBox *cb2;
   TCheckBox *cb3;
   TCheckBox *cb4;
   TCheckBox *cb5;
   TCheckBox *cb6;
   TCheckBox *cb7;
   TCheckBox *cb8;
   TCheckBox *cb9;
   TCheckBox *cb10;
   TCheckBox *cb11;
   TCheckBox *cb12;
   TCheckBox *cb13;
   TCheckBox *cb14;
   TCheckBox *cb15;
   TCheckBox *cb16;
   void __fastcall cb1Click(TObject *Sender);
   void __fastcall cb2Click(TObject *Sender);
   void __fastcall cb3Click(TObject *Sender);
   void __fastcall cb4Click(TObject *Sender);
   void __fastcall cb5Click(TObject *Sender);
   void __fastcall cb6Click(TObject *Sender);
   void __fastcall cb7Click(TObject *Sender);
   void __fastcall cb8Click(TObject *Sender);
   void __fastcall cb9Click(TObject *Sender);
   void __fastcall cb10Click(TObject *Sender);
   void __fastcall cb11Click(TObject *Sender);
   void __fastcall cb12Click(TObject *Sender);
   void __fastcall cb13Click(TObject *Sender);
   void __fastcall cb14Click(TObject *Sender);
   void __fastcall cb15Click(TObject *Sender);
   void __fastcall cb16Click(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
   void loadValues(unsigned short staticValue);
   __fastcall Tfrm_staticpar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_staticpar *frm_staticpar;
//---------------------------------------------------------------------------
#endif
