object frm_lifeIntelliSense: Tfrm_lifeIntelliSense
  Left = 354
  Top = 272
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'LifeScriptIntelliSense'
  ClientHeight = 158
  ClientWidth = 205
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object list_lifecommands: TListBox
    Left = 0
    Top = 0
    Width = 205
    Height = 158
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 13
    Items.Strings = (
      '--> Conditions Commands <--'
      'ACTION'
      'ANIM'
      'ANIM_OBJ'
      'BODY'
      'BODY_OBJ'
      'CARRY_BY'
      'CDROM'
      'CHAPTER'
      'CHOICE'
      'COL'
      'COL_OBJ'
      'COMPORTEMENT_HERO'
      'CONE_VIEW'
      'DISTANCE'
      'DISTANCE_3D'
      'FLAG_CUBE'
      'FLAG_GAME'
      'FUEL'
      'HIT_BY'
      'LIFE_POINT'
      'LIFE_POINT_OBJ'
      'L_TRACK'
      'L_TRACK_OBJ'
      'NB_GOLD_PIECES'
      'NB_LITTLE_KEYS'
      'USE_INVENTORY'
      'ZONE'
      'ZONE_OBJ'
      ''
      '--> Normal Commands <--'
      'ADD_CHOICE'
      'ADD_FUEL'
      'ANIM'
      'ANIM_OBJ'
      'ANIM_SET'
      'ASK_CHOICE'
      'ASK_CHOICE_OBJ'
      'BETA'
      'BIG_MESSAGE'
      'BODY'
      'BODY_OBJ'
      'BRICK_COL'
      'BRUTAL_EXIT'
      'BULLE_OFF'
      'BULLE_ON'
      'CAM_FOLLOW'
      'CHANGE_CUBE'
      'CLEAR_TEXT'
      'CLR_HOLO_POS'
      'COMPORTEMENT'
      'COMPORTEMENT_HERO'
      'ELSE'
      'END'
      'ENDIF'
      'END_COMPORTEMENT'
      'END_LIFE'
      'EXPLODE_OBJ'
      'FADE_ALARM_PAL'
      'FADE_ALARM_RED'
      'FADE_PAL_ALARM'
      'FADE_PAL_RED'
      'FADE_RED_ALARM'
      'FADE_RED_PAL'
      'FALLABLE'
      'FOUND_OBJECT'
      'FULL_POINT'
      'GAME_OVER'
      'GIVE_BONUS'
      'GIVE_GOLD_PIECES'
      'GRM_OFF'
      'HIT_OBJ'
      'HOLOMAP_TRAJ'
      'IF'
      'INC_CHAPTER'
      'INC_CLOVER_BOX'
      'INIT_PINGOUIN'
      'INVISIBLE'
      'KILL_OBJ'
      'LABEL'
      'MESSAGE'
      'MESSAGE_OBJ'
      'MESSAGE_SENDELL'
      'MIDI_OFF'
      'NEVERIF'
      'NOP'
      'NO_IF'
      'OBJ_COL'
      'OFFSET'
      'ONEIF'
      'OR_IF'
      'PLAY_CD_TRACK'
      'PLAY_FLA'
      'PLAY_MIDI'
      'POS_POINT'
      'PROJ_3D'
      'PROJ_ISO'
      'RESTORE_L_TRACK'
      'RETURN'
      'SAY_MESSAGE'
      'SAY_MESSAGE_OBJ'
      'SET_COMPORTEMENT'
      'SET_COMPORTEMENT_OBJ'
      'SET_DARK_PAL'
      'SET_DIR'
      'SET_DIR_OBJ'
      'SET_DOOR_DOWN'
      'SET_DOOR_LEFT'
      'SET_DOOR_RIGHT'
      'SET_DOOR_UP'
      'SET_FLAG_CUBE'
      'SET_FLAG_GAME'
      'SET_GRM'
      'SET_HOLO_POS'
      'SET_LIFE'
      'SET_LIFE_OBJ'
      'SET_LIFE_POINT_OBJ'
      'SET_MAGIC_LEVEL'
      'SET_NORMAL_PAL'
      'SET_TRACK'
      'SET_TRACK_OBJ'
      'SET_USED_INVENTORY'
      'SNIF'
      'STOP_L_TRACK'
      'SUB_FUEL'
      'SUB_LIFE_POINT_OBJ'
      'SUB_MAGIC_POINT'
      'SUICIDE'
      'SWIF'
      'TEXT'
      'THE_END'
      'USE_ONE_LITTLE_KEY'
      'ZOOM')
    ParentFont = False
    TabOrder = 0
    OnDblClick = list_lifecommandsDblClick
    OnKeyPress = list_lifecommandsKeyPress
  end
end
