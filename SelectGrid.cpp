//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectGrid.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_selectgrid *frm_selectgrid;
extern bool isLBA2;
extern int sceneIdx;
//---------------------------------------------------------------------------
__fastcall Tfrm_selectgrid::Tfrm_selectgrid(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_selectgrid::bt_closegridClick(TObject *Sender)
{
    sceneIdx = -1;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_selectgrid::bt_selectgridClick(TObject *Sender)
{
    if(!isLBA2)
        sceneIdx = cb_lba1grids->ItemIndex;
    else
        sceneIdx = cb_lba2grids->ItemIndex + 1;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_selectgrid::FormShow(TObject *Sender)
{
    if(!isLBA2)
    {
        cb_lba1grids->Visible = True;
        cb_lba2grids->Visible = False;
        sceneIdx = cb_lba1grids->ItemIndex;
    }
    else
    {
        cb_lba1grids->Visible = False;
        cb_lba2grids->Visible = True;
        sceneIdx = cb_lba2grids->ItemIndex + 1;
    }
}
//---------------------------------------------------------------------------

