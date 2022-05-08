//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScriptHelp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_scripthelp *frm_scripthelp;
extern AnsiString programPath;
//---------------------------------------------------------------------------
__fastcall Tfrm_scripthelp::Tfrm_scripthelp(TComponent* Owner)
    : TForm(Owner)
{
    char buffer[256];
    ComboBox1->ItemIndex=0;
    lb_list->Items->SetText(getDescriptions("--> GameFlags <--"));
    sb_help->Panels->Items[0]->Text = "Help: no content!";
}
//---------------------------------------------------------------------------
char* Tfrm_scripthelp::getDescriptions(char * descname)
{
   int size = 0;
   char buffer[256];
   int numLine = 0;
   FILE * sceneHandle;

   AnsiString tmp = programPath;
   tmp = tmp + "\\data\\LBASceneEditor.dat";

   sceneHandle = fopen(tmp.c_str(),"rt");
   assert(sceneHandle);

    char* ptr = (char*)malloc(1);

    *ptr = 0;
    while(1){
        fgets(buffer,256,sceneHandle);
        *strchr(buffer,0xA) = 0;
        if(!strcmp(buffer,descname))
            break;
    }

   while(1)
   {
       numLine++;
       fgets(buffer,256,sceneHandle);

       if(!strcmp(buffer,"--> END <--\n"))
           break;

       size+= strlen(buffer)+1;

       ptr = (char*)realloc(ptr,size);

       strcat(ptr,buffer);

       *strchr(buffer,0xA) = 0;

   }
   return ptr;
}

void Tfrm_scripthelp::getDescLine(char* script,char* buffer, int line)
{
    int i;
    char* temp;

    for(i=0;i<line;i++)
    {
        script = strchr(script,0x0A)+1;
    }

    temp = strchr(script,0x0A);
    *temp = 0;

    strcpy(buffer,script);

    *temp = 0xA;
}

void __fastcall Tfrm_scripthelp::ComboBox1Change(TObject *Sender)
{
    switch(ComboBox1->ItemIndex){
        case 0: lb_list->Items->SetText(getDescriptions("--> GameFlags <--")); break;
        case 1: lb_list->Items->SetText(getDescriptions("--> Chapters <--")); break;
        case 2: lb_list->Items->SetText(getDescriptions("--> MagicLevels <--")); break;
        case 3: lb_list->Items->SetText(getDescriptions("--> TwinsenBehaviours <--")); break;
        case 4: lb_list->Items->SetText(getDescriptions("--> Locations <--")); break;
        case 5: lb_list->Items->SetText(getDescriptions("--> Inventory <--")); break;
        case 6: lb_list->Items->SetText(getDescriptions("--> Grids <--")); break;
        case 7: lb_list->Items->SetText(getDescriptions("--> FLA <--")); break;
        case 8: lb_list->Items->SetText(getDescriptions("--> Midis <--")); break;
        case 9: lb_list->Items->SetText(getDescriptions("--> Samples <--")); break;
        case 10: lb_list->Items->SetText(getDescriptions("--> Sprites <--")); break;
        case 11: lb_list->Items->SetText(getDescriptions("--> Bodies <--")); break;
        case 12: lb_list->Items->SetText(getDescriptions("--> Animations <--")); break;
    }

    sb_help->Panels->Items[0]->Text = "Help: no content!";
}
//---------------------------------------------------------------------------
