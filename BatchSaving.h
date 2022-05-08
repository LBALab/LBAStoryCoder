//---------------------------------------------------------------------------

#ifndef BatchSavingH
#define BatchSavingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>
#include <FileCtrl.hpp>
#include <FolderDialog.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class Tfrm_batchsaving : public TForm
{
__published:	// IDE-managed Components
    TButton *bt_runbatch;
    TButton *bt_closebatch;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TPanel *Panel2;
    TBevel *Bevel1;
    TLabel *Label1;
    TListBox *list_batchfiles;
    TButton *bt_batchaddfiles;
    TButton *bt_batchremove;
    TButton *bt_batchremoveall;
    TPanel *Panel1;
    TRadioGroup *rg_batchoutputformat;
    TBevel *Bevel2;
    TLabel *Label2;
    TPanel *Panel3;
    TBevel *Bevel3;
    TLabel *Label3;
    TEdit *edt_destfolder;
    TButton *Button1;
    TLabel *Label4;
    TOpenDialog *dialog_addfiles;
    TLabel *lb_numbatchlist;
    TFolderDialog *dialog_folder;
    TCGauge *bar_savebatch;
    void __fastcall bt_batchaddfilesClick(TObject *Sender);
    void __fastcall bt_batchremoveClick(TObject *Sender);
    void __fastcall bt_batchremoveallClick(TObject *Sender);
    void __fastcall bt_closebatchClick(TObject *Sender);
    void __fastcall bt_runbatchClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_batchsaving(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_batchsaving *frm_batchsaving;
//---------------------------------------------------------------------------
#endif
