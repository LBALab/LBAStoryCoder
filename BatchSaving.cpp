//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BatchSaving.h"
#include "SceneLib.h"
#include "ProjectLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma link "FolderDialog"
#pragma link "FolderDialog"
#pragma link "CGAUGES"
#pragma resource "*.dfm"
Tfrm_batchsaving *frm_batchsaving;
int numFiles=0;
AnsiString defPath;

//---------------------------------------------------------------------------
__fastcall Tfrm_batchsaving::Tfrm_batchsaving(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchsaving::bt_batchaddfilesClick(TObject *Sender)
{
    dialog_addfiles->Title = "Select scene files to add in batch list";
    dialog_addfiles->Filter = "All known files (*.spc, *.ls1, *.sce)|*.scp;*.ls1;*.sce;|LBA1 Binary Scene files (*.ls1)|*.ls1|LBA1 Text Scene files (*.sce)|*.sce";

    if(dialog_addfiles->Execute())
    {
        numFiles += dialog_addfiles->Files->Count;

        if(dialog_addfiles->Files->Count==1)
        {
            list_batchfiles->Items->Add(dialog_addfiles->FileName);
        }
        else
        {
            for(int i=0; i < dialog_addfiles->Files->Count; i++)
            {
                list_batchfiles->Items->Add(dialog_addfiles->Files->Strings[i]);
            }
        }

        if(numFiles==1)
        {
            lb_numbatchlist->Caption = "(";
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + numFiles;
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + " file in list)";
        }
        else
        {
            lb_numbatchlist->Caption = "(";
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + numFiles;
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + " files in list)";
        }
        bt_runbatch->Enabled = True;
        edt_destfolder->Text = ExtractFileDir(list_batchfiles->Items->Strings[0]);
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_batchsaving::bt_batchremoveClick(TObject *Sender)
{
    if(list_batchfiles->SelCount!=0)
    {
        list_batchfiles->DeleteSelected();

        numFiles = list_batchfiles->Count;
        if(numFiles==1)
        {
            lb_numbatchlist->Caption = "(";
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + numFiles;
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + " file in list)";
        }
        else
        {
            lb_numbatchlist->Caption = "(";
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + numFiles;
            lb_numbatchlist->Caption = lb_numbatchlist->Caption + " files in list)";
        }
        if(numFiles == 0)
        {
            bt_runbatch->Enabled = False;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_batchsaving::bt_batchremoveallClick(TObject *Sender)
{
    list_batchfiles->SelectAll();
    list_batchfiles->DeleteSelected();
    numFiles = 0;
    lb_numbatchlist->Caption = "(";
    lb_numbatchlist->Caption = lb_numbatchlist->Caption + numFiles;
    lb_numbatchlist->Caption = lb_numbatchlist->Caption + " files in list)";
    bt_runbatch->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_batchsaving::bt_closebatchClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_batchsaving::bt_runbatchClick(TObject *Sender)
{
    if(numFiles > 0)
    {
        bt_runbatch->Enabled = False;
        bar_savebatch->Enabled = True;
        bar_savebatch->MaxValue = numFiles;
        bar_savebatch->Progress = 0;
        for(int i=0; i < numFiles; i++)
        {
            bar_savebatch->Progress++;
            
            TScene Scene;
            AnsiString Path = dialog_addfiles->Files->Strings[i];
            AnsiString fileName = ExtractFileName(Path);

            if(StrPos(LowerCase(Path).c_str(),".scp")){  // LBA Story Coder Project
                Scene = loadSceneProject(Path.c_str());
            }
            else if(StrPos(LowerCase(Path).c_str(),".ls1")){  // LBA1 Binary mode
                Scene = loadBinaryScene(Path.c_str(),-1);
            }
            else if(StrPos(LowerCase(Path).c_str(),".sce")){ // LBA1 Text mode
                Scene = loadTextScene(Path.c_str());
            }

            AnsiString savePath = edt_destfolder->Text;
            savePath += "\\";
            savePath += fileName.SubString(1, fileName.Length()-3);

            if(rg_batchoutputformat->ItemIndex==0) // scp
            {
                savePath += "scp";
                saveSceneProject(Scene,savePath.c_str());
            }
            else if(rg_batchoutputformat->ItemIndex==1) // ls1
            {
                savePath += "ls1";
                saveBinaryScene(Scene,savePath.c_str());
            }
            else if(rg_batchoutputformat->ItemIndex==2) // sce
            {
                savePath += "sce";
                saveTextScene(Scene,savePath.c_str());
            }
        }
        ShowMessage("Batch saving completed!!");
        bt_runbatch->Enabled = True;
        bar_savebatch->Enabled = False;
        bar_savebatch->Progress = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_batchsaving::Button1Click(TObject *Sender)
{
    dialog_folder->Directory = edt_destfolder->Text;
    if(dialog_folder->Execute())
    {
        edt_destfolder->Text = dialog_folder->Directory;
    }
}
//---------------------------------------------------------------------------

