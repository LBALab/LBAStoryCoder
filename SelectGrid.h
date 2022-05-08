//---------------------------------------------------------------------------

#ifndef SelectGridH
#define SelectGridH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_selectgrid : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TComboBox *cb_lba2grids;
  TComboBox *cb_lba1grids;
  TButton *bt_selectgrid;
  TButton *bt_closegrid;
  void __fastcall bt_closegridClick(TObject *Sender);
  void __fastcall bt_selectgridClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_selectgrid(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_selectgrid *frm_selectgrid;
//---------------------------------------------------------------------------
#endif
