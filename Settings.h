/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
-------------------------------[ Settings.h ]--------------------------------

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

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_settings : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TGroupBox *GroupBox2;
    TCheckBox *cb_lastscene;
    TCheckBox *cb_roomdesign;
    TGroupBox *GroupBox3;
  TCheckBox *cb_ls1;
    TCheckBox *cb_sce;
    TOpenDialog *settings_opendialog;
  TCheckBox *cb_scp;
  TLabel *Label8;
  TCheckBox *cb_ls2;
  TTabSheet *TabSheet4;
  TLabel *Label4;
  TCheckBox *cb_syntax;
  TLabel *Label9;
  TEdit *edt_entitiesPath;
  TLabel *Label10;
  TEdit *edt_bodyPath;
  TLabel *Label11;
  TEdit *edt_spritesPath;
  TButton *bt_spritesHQRDialog;
  TButton *bt_bodyPath;
  TButton *bt_entetiesDialog;
  TLabel *Label6;
  TEdit *edt_builderPath;
  TLabel *Label3;
  TLabel *Label7;
  TEdit *edt_spritesViewerPath;
  TEdit *edt_modelViewerPath;
  TButton *bt_spritesDialog;
  TButton *bt_3DModelDialog;
  TButton *bt_builderDialog;
  TButton *bt_defaultSyntaxColors;
  TCheckBox *cb_brickcoord;
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox4;
  TColorBox *color_comp;
  TLabel *Label5;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label14;
  TColorBox *color_cond;
  TColorBox *color_condvars;
  TColorBox *color_macros;
  TGroupBox *GroupBox5;
  TColorBox *color_numbers;
  TLabel *Label15;
  TColorBox *color_comments;
  TLabel *Label16;
  TLabel *Label17;
  TColorBox *color_tracklabel;
  TLabel *Label18;
  TColorBox *color_trackstop;
  TLabel *Label19;
  TColorBox *color_trackmacros;
  TCheckBox *cb_brickcoordActors;
  TCheckBox *cb_brickcoordTracks;
  TCheckBox *cb_brickcoordZones;
  TLabel *Label1;
  TEdit *edt_animPath;
  TButton *Button1;
    TCheckBox *cb_stayontop;
   void __fastcall bt_builderDialogClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall bt_defaultSyntaxColorsClick(TObject *Sender);
  void __fastcall bt_3DModelDialogClick(TObject *Sender);
  void __fastcall bt_spritesDialogClick(TObject *Sender);
  void __fastcall bt_entetiesDialogClick(TObject *Sender);
  void __fastcall bt_bodyPathClick(TObject *Sender);
  void __fastcall bt_spritesHQRDialogClick(TObject *Sender);
  void __fastcall cb_lastsceneClick(TObject *Sender);
  void __fastcall cb_roomdesignClick(TObject *Sender);
  void __fastcall cb_brickcoordClick(TObject *Sender);
  void __fastcall cb_scpClick(TObject *Sender);
  void __fastcall cb_ls1Click(TObject *Sender);
  void __fastcall cb_sceClick(TObject *Sender);
  void __fastcall cb_syntaxClick(TObject *Sender);
  void __fastcall color_compChange(TObject *Sender);
  void __fastcall color_condChange(TObject *Sender);
  void __fastcall color_condvarsChange(TObject *Sender);
  void __fastcall color_macrosChange(TObject *Sender);
  void __fastcall color_numbersChange(TObject *Sender);
  void __fastcall color_commentsChange(TObject *Sender);
  void __fastcall edt_entitiesPathChange(TObject *Sender);
  void __fastcall edt_bodyPathChange(TObject *Sender);
  void __fastcall edt_spritesPathChange(TObject *Sender);
  void __fastcall edt_builderPathChange(TObject *Sender);
  void __fastcall edt_modelViewerPathChange(TObject *Sender);
  void __fastcall edt_spritesViewerPathChange(TObject *Sender);
  void __fastcall color_trackmacrosChange(TObject *Sender);
  void __fastcall color_tracklabelChange(TObject *Sender);
  void __fastcall color_trackstopChange(TObject *Sender);
  void __fastcall cb_brickcoordActorsClick(TObject *Sender);
  void __fastcall cb_brickcoordTracksClick(TObject *Sender);
  void __fastcall cb_brickcoordZonesClick(TObject *Sender);
  void __fastcall cb_ls2Click(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
    void __fastcall cb_stayontopClick(TObject *Sender);
private:	// User declarations
   void SetKey(AnsiString Key, AnsiString Icon, AnsiString Text);
   void DelKey(AnsiString Key);
   void SetAssociation();
public:		// User declarations
   __fastcall Tfrm_settings(TComponent* Owner);
   void saveSettings();
   bool loadSettings();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_settings *frm_settings;
//---------------------------------------------------------------------------
#endif
