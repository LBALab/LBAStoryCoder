//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("LBAStoryCoder_main.cpp", frm_lba);
USEFORM("Settings.cpp", frm_settings);
USEFORM("StaticParameters.cpp", frm_staticpar);
USEFORM("about.cpp", frm_about);
USEFORM("ActorScriptEd.cpp", frm_actorscript);
USEFORM("ScriptHelp.cpp", frm_scripthelp);
USEFORM("DisplayActor.cpp", frm_displayactor);
USEFORM("SelectScenes.cpp", frm_selectroom);
USEFORM("SelectGrid.cpp", frm_selectgrid);
USEFORM("LifeScriptIntelliSense.cpp", frm_lifeIntelliSense);
USEFORM("TrackScriptIntelliSense.cpp", frm_trackIntelliSense);
USEFORM("BatchSaving.cpp", frm_batchsaving);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "LBA Story Coder";
     Application->HelpFile = "D:\\XesF\\LBA\\LBA Story Coder\\help\\StoryCoderHelpProject.hlp";
     Application->CreateForm(__classid(Tfrm_lba), &frm_lba);
         Application->CreateForm(__classid(Tfrm_settings), &frm_settings);
         Application->CreateForm(__classid(Tfrm_staticpar), &frm_staticpar);
         Application->CreateForm(__classid(Tfrm_about), &frm_about);
         Application->CreateForm(__classid(Tfrm_actorscript), &frm_actorscript);
         Application->CreateForm(__classid(Tfrm_scripthelp), &frm_scripthelp);
         Application->CreateForm(__classid(Tfrm_displayactor), &frm_displayactor);
         Application->CreateForm(__classid(Tfrm_selectroom), &frm_selectroom);
         Application->CreateForm(__classid(Tfrm_selectgrid), &frm_selectgrid);
         Application->CreateForm(__classid(Tfrm_trackIntelliSense), &frm_trackIntelliSense);
         Application->CreateForm(__classid(Tfrm_batchsaving), &frm_batchsaving);
         Application->CreateForm(__classid(Tfrm_lifeIntelliSense), &frm_lifeIntelliSense);
         Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
