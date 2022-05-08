object frm_trackIntelliSense: Tfrm_trackIntelliSense
  Left = 354
  Top = 272
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'TrackScriptIntelliSense'
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
  object list_trackcommands: TListBox
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
      'ANGLE'
      'ANGLE_RND'
      'ANIM'
      'BACKGROUND'
      'BETA'
      'BODY'
      'CLOSE'
      'END'
      'FACE_TWINKEL'
      'GOTO'
      'GOTO_POINT'
      'GOTO_POINT_3D'
      'GOTO_SYM_POINT'
      'LABEL'
      'LOOP'
      'NOP'
      'NO_BODY'
      'OPEN_DOWN'
      'OPEN_LEFT'
      'OPEN_RIGHT'
      'OPEN_UP'
      'PLAY_FLA'
      'POS_POINT'
      'REPEAT_SAMPLE'
      'SAMPLE'
      'SAMPLE_ALWAYS'
      'SAMPLE_RND '
      'SAMPLE_STOP'
      'SIMPLE_SAMPLE'
      'SPEED '
      'STOP'
      'WAIT_ANIM'
      'WAIT_DOOR'
      'WAIT_NB_ANIM'
      'WAIT_NB_SECOND')
    ParentFont = False
    TabOrder = 0
    OnDblClick = list_trackcommandsDblClick
    OnKeyPress = list_trackcommandsKeyPress
  end
end
