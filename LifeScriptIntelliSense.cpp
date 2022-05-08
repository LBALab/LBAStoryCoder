//---------------------------------------------------------------------------

#include <vcl.h>
#include <conio.h>
#pragma hdrstop

#include "LifeScriptIntelliSense.h"
#include "ActorScriptEd.h"
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_lifeIntelliSense *frm_lifeIntelliSense;

extern bool syntax;

//---------------------------------------------------------------------------
__fastcall Tfrm_lifeIntelliSense::Tfrm_lifeIntelliSense(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_lifeIntelliSense::FormDeactivate(TObject *Sender)
{
    frm_lifeIntelliSense->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_lifeIntelliSense::list_lifecommandsDblClick(TObject *Sender)
{
    AnsiString cmd = list_lifecommands->Items->Strings[list_lifecommands->ItemIndex];
    if(cmd != "--> Conditions Commands <--" && cmd != "--> Normal Commands <--" && cmd != "")
    {
        int lifesel = frm_actorscript->re_lifescript->SelStart;
        int lensel = frm_actorscript->re_lifescript->SelLength;
        frm_actorscript->re_lifescript->Text = frm_actorscript->re_lifescript->Text.SubString(1,frm_actorscript->re_lifescript->SelStart) + cmd + frm_actorscript->re_lifescript->Text.SubString(frm_actorscript->re_lifescript->SelStart+1+lensel,frm_actorscript->re_lifescript->GetTextLen());
        if(syntax)
            frm_actorscript->LifeSyntax->RefreshAllControl();
        frm_actorscript->re_lifescript->SelStart = lifesel+cmd.Length();
        frm_lifeIntelliSense->Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_lifeIntelliSense::list_lifecommandsKeyPress(
      TObject *Sender, char &Key)
{
    if(Key==0x0D) // ENTER Key
    {
        AnsiString cmd = list_lifecommands->Items->Strings[list_lifecommands->ItemIndex];
        if(cmd != "--> Conditions Commands <--" && cmd != "--> Normal Commands <--" && cmd != "")
        {
            int lifesel = frm_actorscript->re_lifescript->SelStart;
            int lensel = frm_actorscript->re_lifescript->SelLength;

            frm_actorscript->re_lifescript->Text = frm_actorscript->re_lifescript->Text.SubString(1,frm_actorscript->re_lifescript->SelStart) + cmd + frm_actorscript->re_lifescript->Text.SubString(frm_actorscript->re_lifescript->SelStart+1+lensel,frm_actorscript->re_lifescript->GetTextLen());
            if(syntax)
                frm_actorscript->LifeSyntax->RefreshAllControl();
            frm_actorscript->re_lifescript->SelStart = lifesel+cmd.Length();
            frm_lifeIntelliSense->Close();
        }
    }
    else
        frm_lifeIntelliSense->Close();                                
}
//---------------------------------------------------------------------------

