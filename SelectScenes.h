//---------------------------------------------------------------------------

#ifndef SelectScenesH
#define SelectScenesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_selectroom : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TComboBox *cb_lba1scenes;
  TButton *Button1;
  TButton *Button2;
  TComboBox *cb_lba2scenes;
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall cb_lba1scenesChange(TObject *Sender);
  void __fastcall cb_lba2scenesChange(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_selectroom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_selectroom *frm_selectroom;
//---------------------------------------------------------------------------
#endif
