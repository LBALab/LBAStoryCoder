//---------------------------------------------------------------------------

#ifndef TrackScriptIntelliSenseH
#define TrackScriptIntelliSenseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_trackIntelliSense : public TForm
{
__published:	// IDE-managed Components
    TListBox *list_trackcommands;
    void __fastcall FormDeactivate(TObject *Sender);
    void __fastcall list_trackcommandsDblClick(TObject *Sender);
    void __fastcall list_trackcommandsKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_trackIntelliSense(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_trackIntelliSense *frm_trackIntelliSense;
//---------------------------------------------------------------------------
#endif
