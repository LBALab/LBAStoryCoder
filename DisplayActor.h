//---------------------------------------------------------------------------

#ifndef DisplayActorH
#define DisplayActorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_displayactor : public TForm
{
__published:	// IDE-managed Components
  TImage *img_fullactor;
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_displayactor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_displayactor *frm_displayactor;
//---------------------------------------------------------------------------
#endif
