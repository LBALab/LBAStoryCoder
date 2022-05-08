//---------------------------------------------------------------------------

#include <vcl.h>
#include <conio.h>
#pragma hdrstop

#include "TrackScriptIntelliSense.h"
#include "ActorScriptEd.h"
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_trackIntelliSense *frm_trackIntelliSense;
extern bool syntax;

//---------------------------------------------------------------------------
__fastcall Tfrm_trackIntelliSense::Tfrm_trackIntelliSense(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trackIntelliSense::FormDeactivate(TObject *Sender)
{
    frm_trackIntelliSense->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trackIntelliSense::list_trackcommandsDblClick(TObject *Sender)
{
    int tracksel = frm_actorscript->re_movescript->SelStart;
    int lensel = frm_actorscript->re_movescript->SelLength;
    AnsiString cmd = list_trackcommands->Items->Strings[list_trackcommands->ItemIndex];
    frm_actorscript->re_movescript->Text = frm_actorscript->re_movescript->Text.SubString(1,frm_actorscript->re_movescript->SelStart) + cmd + frm_actorscript->re_movescript->Text.SubString(frm_actorscript->re_movescript->SelStart+1+lensel,frm_actorscript->re_movescript->GetTextLen());
    if(syntax)
        frm_actorscript->TrackSyntax->RefreshAllControl();
    frm_actorscript->re_movescript->SelStart = tracksel+cmd.Length();
    frm_trackIntelliSense->Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trackIntelliSense::list_trackcommandsKeyPress(
      TObject *Sender, char &Key)
{
    if(Key==0x0D) // ENTER Key
    {
        int tracksel = frm_actorscript->re_movescript->SelStart;
        int lensel = frm_actorscript->re_movescript->SelLength;
        AnsiString cmd = list_trackcommands->Items->Strings[list_trackcommands->ItemIndex];
        frm_actorscript->re_movescript->Text = frm_actorscript->re_movescript->Text.SubString(1,frm_actorscript->re_movescript->SelStart) + cmd + frm_actorscript->re_movescript->Text.SubString(frm_actorscript->re_movescript->SelStart+1+lensel,frm_actorscript->re_movescript->GetTextLen());
        if(syntax)
            frm_actorscript->TrackSyntax->RefreshAllControl();
        frm_actorscript->re_movescript->SelStart = tracksel+cmd.Length();
        frm_trackIntelliSense->Close();
    }
    else
        frm_trackIntelliSense->Close();                                
}
//---------------------------------------------------------------------------

