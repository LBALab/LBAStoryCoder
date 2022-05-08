//---------------------------------------------------------------------------

#ifndef LifeScriptIntelliSenseH
#define LifeScriptIntelliSenseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_lifeIntelliSense : public TForm
{
__published:	// IDE-managed Components
    TListBox *list_lifecommands;
    void __fastcall FormDeactivate(TObject *Sender);
    void __fastcall list_lifecommandsDblClick(TObject *Sender);
    void __fastcall list_lifecommandsKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_lifeIntelliSense(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_lifeIntelliSense *frm_lifeIntelliSense;
//---------------------------------------------------------------------------
#endif
