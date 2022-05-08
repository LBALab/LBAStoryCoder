//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DisplayActor.h"
#include "LBAStoryCoder_main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_displayactor *frm_displayactor;

//---------------------------------------------------------------------------
__fastcall Tfrm_displayactor::Tfrm_displayactor(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_displayactor::FormShow(TObject *Sender)
{
    img_fullactor->Picture->Assign(frm_lba->img_actorpos->Picture);
}
//---------------------------------------------------------------------------
