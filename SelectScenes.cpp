//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectScenes.h"
#include "LBAStoryCoder_main.h"
#include "SceneLib.h"
#include "HQRLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_selectroom *frm_selectroom;

extern bool isLBA2;
extern TScene Scene;
extern int sceneIdx;
extern AnsiString Path;
extern filesize;

//---------------------------------------------------------------------------
__fastcall Tfrm_selectroom::Tfrm_selectroom(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_selectroom::Button1Click(TObject *Sender)
{
    if(!isLBA2) // LBA1 scenes
      Scene = loadBinaryScene(Path.c_str(), sceneIdx);
    else // LBA2 scenes
      Scene = loadBinaryScene2(Path.c_str(), sceneIdx);

    if(filesize!=-1){
      frm_lba->putInitScene();
      frm_lba->bt_reload->Enabled = True;
      frm_lba->menu_reload->Enabled = True;
      frm_lba->bt_close->Enabled = True;
      frm_lba->menu_close->Enabled = True;
      frm_lba->bt_save->Enabled = True;
      frm_lba->menu_save->Enabled = True;
      frm_lba->bt_saveas->Enabled = True;
      frm_lba->menu_saveas->Enabled = True;
      frm_lba->menu_builder->Enabled = True;
      frm_lba->pl_scene->Visible = True;
    }
    Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_selectroom::Button2Click(TObject *Sender)
{
    Close();  
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_selectroom::cb_lba1scenesChange(TObject *Sender)
{
    sceneIdx = cb_lba1scenes->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_selectroom::cb_lba2scenesChange(TObject *Sender)
{
    sceneIdx = cb_lba2scenes->ItemIndex + 1;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_selectroom::FormShow(TObject *Sender)
{
    if(!isLBA2)
    {
        cb_lba1scenes->Visible = True;
        cb_lba2scenes->Visible = False;
        sceneIdx = cb_lba1scenes->ItemIndex;
    }
    else
    {
        cb_lba1scenes->Visible = False;
        cb_lba2scenes->Visible = True;
        sceneIdx = cb_lba2scenes->ItemIndex + 1;
    }
}
//---------------------------------------------------------------------------

