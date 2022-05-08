//---------------------------------------------------------------------------

#ifndef LBAStoryCoder_mainH
#define LBAStoryCoder_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "CGAUGES.h"
#include "CSPIN.h"
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <HTTPApp.hpp>
#include <HTTPProd.hpp>
#include <DB.hpp>
#include <DBXpress.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include "ehsbase.hpp"
#include "ehscontextmap.hpp"
#include "ehswhatsthis.hpp"
//---------------------------------------------------------------------------
class Tfrm_lba : public TForm
{
__published:	// IDE-managed Components
    TImageList *img_icons;
    TImageList *img_tabs;
    TPageControl *pl_scene;
    TTabSheet *Atmosphere;
    TTabSheet *Actors;
    TTabSheet *Zones;
    TTabSheet *Tracks;
    TGroupBox *GroupBox1;
    TLabel *Label4;
    TLabel *Label5;
    TCSpinEdit *edt_cube;
    TComboBox *cb_textbank;
    TLabel *Label7;
    TCSpinEdit *edt_actors;
    TGroupBox *GroupBox2;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label17;
    TCGauge *bar_hit;
    TCGauge *bar_speed;
    TCGauge *bar_points;
    TCGauge *bar_armour;
    TCGauge *bar_amount;
    TShape *shape_talkcolor;
    TCSpinEdit *edt_entity;
    TCSpinEdit *edt_body;
    TCSpinEdit *edt_animation;
    TCSpinEdit *edt_sprite;
    TCSpinEdit *edt_hit;
    TCSpinEdit *edt_speed;
    TCSpinEdit *edt_amount;
    TCSpinEdit *edt_talkcolor;
    TCSpinEdit *edt_armour;
    TCSpinEdit *edt_points;
    TStaticText *edt_staticflag;
    TPanel *Panel3;
    TImage *img_posxy;
    TImage *img_actorpos;
    TImage *Image3;
    TImage *img_actorY;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label27;
    TLabel *Label25;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label30;
    TEdit *edt_cropbottom;
    TEdit *edt_cropright;
    TEdit *edt_croptop;
    TEdit *edt_cropleft;
    TEdit *edt_angle;
    TCSpinEdit *edt_actorX;
    TCSpinEdit *edt_actorY;
    TCSpinEdit *edt_actorZ;
    TComboBox *cb_bonus;
    TCSpinEdit *edt_bonus;
    TButton *bt_actorscript;
    TButton *bt_staticpar;
    TButton *Button1;
    TEdit *edt_actorName;
    TButton *bt_newactor;
    TButton *bt_newspriteactor;
    TButton *bt_clone;
    TButton *bt_remove;
    TLabel *Label35;
    TGroupBox *GroupBox4;
    TCSpinEdit *edt_tracks;
    TImage *Image2;
    TMainMenu *MainMenu1;
    TMenuItem *File2;
    TMenuItem *menu_new;
    TMenuItem *menu_load;
    TMenuItem *menu_reload;
    TMenuItem *menu_save;
    TMenuItem *menu_saveas;
    TMenuItem *menu_close;
    TMenuItem *N2;
    TMenuItem *menu_exit;
    TMenuItem *View2;
    TMenuItem *menu_settings;
    TMenuItem *Help3;
    TMenuItem *About2;
    TMenuItem *Help4;
    TToolBar *ToolBar1;
    TPanel *Panel1;
    TToolButton *bt_new;
    TToolButton *bt_load;
    TToolButton *bt_reload;
    TToolButton *bt_save;
    TToolButton *bt_saveas;
    TToolButton *bt_close;
    TToolButton *ToolButton7;
    TToolButton *bt_settings;
    TStatusBar *StatusBar1;
  TLabel *lb_realBodyIdx;
  TLabel *lb_realAnimIdx;
  TLabel *lb_realBody;
    TLabel *lb_realAnim;
    TLabel *Label8;
    TCSpinEdit *edt_zones;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TImage *img_bzonepos;
    TImage *Image5;
    TImage *Image7;
    TImage *img_bzoneY;
    TLabel *Label33;
    TLabel *Label32;
    TLabel *Label31;
    TCSpinEdit *edt_bzoneX;
    TCSpinEdit *edt_bzoneY;
    TCSpinEdit *edt_bzoneZ;
    TGroupBox *GroupBox8;
    TCSpinEdit *edt_info0;
    TCSpinEdit *edt_info1;
    TCSpinEdit *edt_info2;
    TCSpinEdit *edt_info3;
    TComboBox *cb_zonetype;
    TLabel *Label39;
    TLabel *lb_info0;
    TLabel *lb_info1;
    TLabel *lb_info2;
    TLabel *lb_info3;
    TComboBox *cb_zonebonus;
    TComboBox *cb_snap;
  TGroupBox *GroupBox3;
  TLabel *Label6;
  TLabel *Label40;
  TLabel *Label41;
  TLabel *Label42;
  TLabel *Label43;
  TLabel *Label44;
  TLabel *Label45;
  TLabel *Label46;
  TLabel *Label47;
  TLabel *Label48;
  TLabel *Label49;
  TLabel *Label50;
  TLabel *Label51;
  TLabel *Label52;
  TLabel *Label53;
  TLabel *Label54;
  TLabel *Label55;
  TComboBox *cb_cubemusic;
  TCSpinEdit *edt_amb23;
  TCSpinEdit *edt_amb22;
  TCSpinEdit *edt_amb21;
  TCSpinEdit *edt_amb03;
  TCSpinEdit *edt_amb02;
  TCSpinEdit *edt_amb01;
  TCSpinEdit *edt_amb11;
  TCSpinEdit *edt_amb12;
  TCSpinEdit *edt_amb13;
  TCSpinEdit *edt_amb31;
  TCSpinEdit *edt_amb32;
  TCSpinEdit *edt_amb33;
  TCSpinEdit *edt_secondmin;
  TCSpinEdit *edt_secondecart;
  TCSpinEdit *edt_beta;
  TCSpinEdit *edt_alpha;
  TOpenDialog *OpenDialog1;
  TSaveDialog *SaveDialog1;
  TLabel *lb_amb04;
  TCSpinEdit *edt_amb04;
  TLabel *lb_amb05;
  TCSpinEdit *edt_amb05;
  TLabel *lb_amb24;
  TCSpinEdit *edt_amb24;
  TLabel *lb_amb25;
  TCSpinEdit *edt_amb25;
  TLabel *lb_amb14;
  TCSpinEdit *edt_amb14;
  TLabel *lb_amb15;
  TCSpinEdit *edt_amb15;
  TLabel *lb_amb34;
  TCSpinEdit *edt_amb34;
  TLabel *lb_amb35;
  TCSpinEdit *edt_amb35;
  TMenuItem *Checknewversion1;
  TMenuItem *TheSacredCarrotwebsite1;
  TMenuItem *LBACommunityHomePage1;
  TMenuItem *N1;
  TMenuItem *N3;
  TMenuItem *BugTrackingSystem1;
  TLabel *Label2;
  TComboBox *cb_controlmode;
  TWhatsThis *WhatsThis1;
  TMenuItem *Whatsthis2;
  TToolButton *bt_help;
  TToolButton *ToolButton2;
    TTimer *TimeOut;
    TToolButton *menu_builder;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TTrackBar *scroll_bzoneY;
    TLabel *Label3;
    TTrackBar *scroll_bzoneZ;
    TTrackBar *scroll_bzoneX;
    TLabel *Label56;
    TLabel *Label57;
    TLabel *Label64;
    TTrackBar *scroll_actorX;
    TLabel *Label65;
    TTrackBar *scroll_actorZ;
    TLabel *Label66;
    TTrackBar *scroll_actorY;
    TTrackBar *scroll_angle;
    TLabel *Label67;
    TGroupBox *GroupBox7;
    TCSpinEdit *edt_zonedimX;
    TLabel *Label68;
    TCSpinEdit *edt_zonedimY;
    TLabel *Label69;
    TLabel *Label70;
    TCSpinEdit *edt_zonedimZ;
    TButton *bt_newtrack;
    TButton *bt_clonetrack;
    TButton *bt_removetrack;
    TButton *bt_newzone;
    TButton *bt_clonezone;
    TButton *bt_removezone;
    TGroupBox *GroupBox9;
    TImage *Image1;
    TImage *img_trackpos;
    TImage *Image4;
    TImage *img_trackY;
    TLabel *Label1;
    TLabel *Label22;
    TLabel *Label34;
    TLabel *Label61;
    TLabel *Label62;
    TLabel *Label63;
    TCSpinEdit *edt_trackZ;
    TCSpinEdit *edt_trackY;
    TCSpinEdit *edt_trackX;
    TTrackBar *scroll_trackZ;
    TTrackBar *scroll_trackX;
    TTrackBar *scroll_trackY;
    TMenuItem *menu_batchsaving;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall menu_settings2Click(TObject *Sender);
    void __fastcall bt_staticparClick(TObject *Sender);
    void __fastcall bt_actorscriptClick(TObject *Sender);
    void __fastcall bt_newactorClick(TObject *Sender);
    void __fastcall bt_newspriteactorClick(TObject *Sender);
    void __fastcall bt_removeClick(TObject *Sender);
    void __fastcall edt_actorsChange(TObject *Sender);
    void __fastcall edt_entityChange(TObject *Sender);
    void __fastcall edt_bodyChange(TObject *Sender);
    void __fastcall edt_animationChange(TObject *Sender);
    void __fastcall edt_spriteChange(TObject *Sender);
    void __fastcall edt_hitChange(TObject *Sender);
    void __fastcall edt_bonusChange(TObject *Sender);
    void __fastcall cb_bonusChange(TObject *Sender);
    void __fastcall edt_amountChange(TObject *Sender);
    void __fastcall edt_speedChange(TObject *Sender);
    void __fastcall edt_talkcolorChange(TObject *Sender);
    void __fastcall edt_armourChange(TObject *Sender);
    void __fastcall edt_pointsChange(TObject *Sender);
    void __fastcall edt_angleChange(TObject *Sender);
    void __fastcall edt_actorXChange(TObject *Sender);
    void __fastcall edt_actorYChange(TObject *Sender);
    void __fastcall edt_actorZChange(TObject *Sender);
    void __fastcall edt_cropleftChange(TObject *Sender);
    void __fastcall edt_croptopChange(TObject *Sender);
    void __fastcall edt_croprightChange(TObject *Sender);
    void __fastcall edt_cropbottomChange(TObject *Sender);
    void __fastcall edt_tracksChange(TObject *Sender);
    void __fastcall edt_trackXChange(TObject *Sender);
    void __fastcall edt_trackYChange(TObject *Sender);
    void __fastcall edt_trackZChange(TObject *Sender);
    void __fastcall bt_clonetrackClick(TObject *Sender);
    void __fastcall bt_removetrackClick(TObject *Sender);
    void __fastcall bt_newtrackClick(TObject *Sender);
    void __fastcall menu_settingsClick(TObject *Sender);
    void __fastcall menu_closeClick(TObject *Sender);
    void __fastcall menu_saveasClick(TObject *Sender);
    void __fastcall edt_bzoneXChange(TObject *Sender);
    void __fastcall edt_bzoneZChange(TObject *Sender);
    void __fastcall edt_bzoneYChange(TObject *Sender);
    void __fastcall cb_zonetypeChange(TObject *Sender);
    void __fastcall edt_info0Change(TObject *Sender);
    void __fastcall edt_info1Change(TObject *Sender);
    void __fastcall edt_info2Change(TObject *Sender);
    void __fastcall edt_info3Change(TObject *Sender);
    void __fastcall edt_zonesChange(TObject *Sender);
    void __fastcall cb_zonebonusChange(TObject *Sender);
    void __fastcall cb_snapChange(TObject *Sender);
    void __fastcall bt_newzoneClick(TObject *Sender);
    void __fastcall bt_clonezoneClick(TObject *Sender);
    void __fastcall bt_removezoneClick(TObject *Sender);
  void __fastcall edt_actorNameChange(TObject *Sender);
  void __fastcall menu_loadClick(TObject *Sender);
  void __fastcall menu_reloadClick(TObject *Sender);
  void __fastcall menu_saveClick(TObject *Sender);
  void __fastcall edt_cubeChange(TObject *Sender);
  void __fastcall cb_textbankChange(TObject *Sender);
  void __fastcall cb_cubemusicChange(TObject *Sender);
  void __fastcall edt_alphaChange(TObject *Sender);
  void __fastcall edt_betaChange(TObject *Sender);
  void __fastcall edt_secondminChange(TObject *Sender);
  void __fastcall edt_secondecartChange(TObject *Sender);
  void __fastcall edt_amb01Change(TObject *Sender);
  void __fastcall edt_amb02Change(TObject *Sender);
  void __fastcall edt_amb03Change(TObject *Sender);
  void __fastcall edt_amb21Change(TObject *Sender);
  void __fastcall edt_amb22Change(TObject *Sender);
  void __fastcall edt_amb23Change(TObject *Sender);
  void __fastcall edt_amb11Change(TObject *Sender);
  void __fastcall edt_amb12Change(TObject *Sender);
  void __fastcall edt_amb13Change(TObject *Sender);
  void __fastcall edt_amb31Change(TObject *Sender);
  void __fastcall edt_amb32Change(TObject *Sender);
  void __fastcall edt_amb33Change(TObject *Sender);
  void __fastcall About2Click(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall menu_newClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall Help4Click(TObject *Sender);
  void __fastcall Checknewversion1Click(TObject *Sender);
  void __fastcall BugTrackingSystem1Click(TObject *Sender);
  void __fastcall TheSacredCarrotwebsite1Click(TObject *Sender);
  void __fastcall LBACommunityHomePage1Click(TObject *Sender);
  void __fastcall cb_controlmodeChange(TObject *Sender);
  void __fastcall WhatsThis1Help(TObject *Sender, TObject *HelpItem,
          bool IsMenu, THelpContext HContext, int X, int Y,
          bool &CallHelp);
  void __fastcall menu_exitClick(TObject *Sender);
    void __fastcall TimeOutTimer(TObject *Sender);
    void __fastcall ToolButton5Click(TObject *Sender);
    void __fastcall menu_builderClick(TObject *Sender);
    void __fastcall scroll_bzoneYChange(TObject *Sender);
    void __fastcall scroll_bzoneZChange(TObject *Sender);
    void __fastcall scroll_bzoneXChange(TObject *Sender);
    void __fastcall scroll_trackYChange(TObject *Sender);
    void __fastcall scroll_trackZChange(TObject *Sender);
    void __fastcall scroll_trackXChange(TObject *Sender);
    void __fastcall scroll_actorXChange(TObject *Sender);
    void __fastcall scroll_actorZChange(TObject *Sender);
    void __fastcall scroll_actorYChange(TObject *Sender);
    void __fastcall scroll_angleChange(TObject *Sender);
    void __fastcall edt_zonedimXChange(TObject *Sender);
    void __fastcall edt_zonedimYChange(TObject *Sender);
    void __fastcall edt_zonedimZChange(TObject *Sender);
    void __fastcall menu_batchsavingClick(TObject *Sender);
    void __fastcall bt_cloneClick(TObject *Sender);
    void __fastcall pl_sceneChange(TObject *Sender);
private:	// User declarations
   MESSAGE void DropFile(TMessage &Message);
   MESSAGE TWMCopyData CopyData(TWMCopyData &Message);
   void loadPaletteFromResource();
public:		// User declarations
   __fastcall Tfrm_lba(TComponent* Owner);
   void putInitScene();
   void initScene();
   void clearScene();

   void NewTrack(int x, int y, int z);
   void NewActor(int x, int y, int z);
   void NewSpriteActor(int x, int y, int z);
   void CloneActor(int x, int y, int z);
   void NewZone(int x1, int y1, int z1, int x2, int y2, int z2);
   void CloneZone(int x1, int y1, int z1, int x2, int y2, int z2);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_DROPFILES, TMessage, DropFile);
  MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, CopyData);
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_lba *frm_lba;
//---------------------------------------------------------------------------
#endif
