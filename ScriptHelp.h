//---------------------------------------------------------------------------

#ifndef ScriptHelpH
#define ScriptHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <stdio.h>
#include <fstream.h>
#include <assert.h>
//---------------------------------------------------------------------------
class Tfrm_scripthelp : public TForm
{
__published:	// IDE-managed Components
    TListBox *lb_list;
    TStatusBar *sb_help;
    TComboBox *ComboBox1;
    void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
   char* getDescriptions(char * descname);
   void getDescLine(char* script,char* buffer, int line);
    __fastcall Tfrm_scripthelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_scripthelp *frm_scripthelp;
//---------------------------------------------------------------------------
#endif
