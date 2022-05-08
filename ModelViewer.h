//---------------------------------------------------------------------------

#ifndef ModelViewerH
#define ModelViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_modelviewer : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall Tfrm_modelviewer(TComponent* Owner);
   void  _fastcall getDraw(TObject *o, bool &b);
   void  updateForm();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_modelviewer *frm_modelviewer;
//---------------------------------------------------------------------------
#endif
