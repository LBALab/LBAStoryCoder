object frm_settings: Tfrm_settings
  Left = 305
  Top = 287
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Settings'
  ClientHeight = 256
  ClientWidth = 512
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 513
    Height = 257
    ActivePage = TabSheet1
    MultiLine = True
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'General'
      object GroupBox2: TGroupBox
        Left = 8
        Top = 8
        Width = 249
        Height = 153
        Caption = 'Main Settings: '
        TabOrder = 0
        object cb_lastscene: TCheckBox
          Left = 8
          Top = 16
          Width = 161
          Height = 17
          Caption = 'Open last scene at startup.'
          Checked = True
          State = cbChecked
          TabOrder = 0
          OnClick = cb_lastsceneClick
        end
        object cb_roomdesign: TCheckBox
          Left = 8
          Top = 40
          Width = 225
          Height = 17
          Caption = 'Display room design when scene is loaded.'
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = cb_roomdesignClick
        end
        object cb_brickcoord: TCheckBox
          Left = 8
          Top = 80
          Width = 233
          Height = 17
          Caption = 'Use brick coordinates (X+512,Y+256,Z+256)'
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = cb_brickcoordClick
        end
        object cb_brickcoordActors: TCheckBox
          Left = 24
          Top = 96
          Width = 97
          Height = 17
          Caption = 'In Actors'
          Checked = True
          State = cbChecked
          TabOrder = 3
          OnClick = cb_brickcoordActorsClick
        end
        object cb_brickcoordTracks: TCheckBox
          Left = 24
          Top = 112
          Width = 97
          Height = 17
          Caption = 'In Tracks'
          Checked = True
          State = cbChecked
          TabOrder = 4
          OnClick = cb_brickcoordTracksClick
        end
        object cb_brickcoordZones: TCheckBox
          Left = 24
          Top = 128
          Width = 97
          Height = 17
          Caption = 'In Zones'
          Checked = True
          State = cbChecked
          TabOrder = 5
          OnClick = cb_brickcoordZonesClick
        end
        object cb_stayontop: TCheckBox
          Left = 40
          Top = 56
          Width = 193
          Height = 17
          Caption = 'Stay On Top when displaying rooms.'
          Checked = True
          State = cbChecked
          TabOrder = 6
          OnClick = cb_stayontopClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 264
        Top = 8
        Width = 233
        Height = 121
        Caption = 'File Association: '
        TabOrder = 1
        object cb_ls1: TCheckBox
          Left = 40
          Top = 48
          Width = 169
          Height = 17
          Caption = '*.ls1 (LBA1 Binary Scene File)'
          Checked = True
          State = cbChecked
          TabOrder = 0
          OnClick = cb_ls1Click
        end
        object cb_sce: TCheckBox
          Left = 40
          Top = 96
          Width = 185
          Height = 17
          Caption = '*.sce (Text Scene for TwinEngine)'
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = cb_sceClick
        end
        object cb_scp: TCheckBox
          Left = 40
          Top = 24
          Width = 177
          Height = 17
          Caption = '*.scp (LBA Story Coder Project)'
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = cb_scpClick
        end
        object cb_ls2: TCheckBox
          Left = 40
          Top = 72
          Width = 177
          Height = 17
          Caption = '*.ls2 (LBA2 Binary Scene File)'
          Checked = True
          State = cbChecked
          TabOrder = 3
          OnClick = cb_ls2Click
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Programs Paths'
      ImageIndex = 1
      object Label8: TLabel
        Left = 8
        Top = 4
        Width = 176
        Height = 13
        Caption = 'You always need to set up this paths.'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object Label6: TLabel
        Left = 8
        Top = 32
        Width = 210
        Height = 13
        Caption = 'Set the path for LBArchitect Builder program:'
      end
      object Label3: TLabel
        Left = 8
        Top = 88
        Width = 223
        Height = 13
        Caption = 'Set the path for Story Coder 3D Models Viewer:'
        Enabled = False
      end
      object Label7: TLabel
        Left = 8
        Top = 128
        Width = 204
        Height = 13
        Caption = 'Set the path for Story Coder Sprites Viewer:'
        Enabled = False
      end
      object edt_builderPath: TEdit
        Left = 8
        Top = 48
        Width = 473
        Height = 21
        TabOrder = 0
        OnChange = edt_builderPathChange
      end
      object edt_spritesViewerPath: TEdit
        Left = 8
        Top = 144
        Width = 473
        Height = 21
        Enabled = False
        TabOrder = 1
        OnChange = edt_spritesViewerPathChange
      end
      object edt_modelViewerPath: TEdit
        Left = 8
        Top = 104
        Width = 473
        Height = 21
        Enabled = False
        TabOrder = 2
        OnChange = edt_modelViewerPathChange
      end
      object bt_spritesDialog: TButton
        Left = 461
        Top = 146
        Width = 18
        Height = 18
        Caption = '...'
        Enabled = False
        TabOrder = 3
        OnClick = bt_spritesDialogClick
      end
      object bt_3DModelDialog: TButton
        Left = 461
        Top = 106
        Width = 18
        Height = 18
        Caption = '...'
        Enabled = False
        TabOrder = 4
        OnClick = bt_3DModelDialogClick
      end
      object bt_builderDialog: TButton
        Left = 461
        Top = 50
        Width = 18
        Height = 18
        Caption = '...'
        TabOrder = 5
        OnClick = bt_builderDialogClick
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'HQR Paths'
      ImageIndex = 3
      object Label4: TLabel
        Left = 8
        Top = 4
        Width = 176
        Height = 13
        Caption = 'You always need to set up this paths.'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object Label9: TLabel
        Left = 8
        Top = 32
        Width = 89
        Height = 13
        Caption = 'LBA1 File3D.HQR:'
      end
      object Label10: TLabel
        Left = 8
        Top = 72
        Width = 83
        Height = 13
        Caption = 'LBA1 Body.HQR:'
        Enabled = False
      end
      object Label11: TLabel
        Left = 8
        Top = 152
        Width = 91
        Height = 13
        Caption = 'LBA1 Sprites.HQR:'
        Enabled = False
      end
      object Label1: TLabel
        Left = 8
        Top = 112
        Width = 82
        Height = 13
        Caption = 'LBA1 Anim.HQR:'
        Enabled = False
      end
      object edt_entitiesPath: TEdit
        Left = 8
        Top = 48
        Width = 473
        Height = 21
        TabOrder = 0
        OnChange = edt_entitiesPathChange
      end
      object edt_bodyPath: TEdit
        Left = 8
        Top = 88
        Width = 473
        Height = 21
        Enabled = False
        TabOrder = 1
        OnChange = edt_bodyPathChange
      end
      object edt_spritesPath: TEdit
        Left = 8
        Top = 168
        Width = 473
        Height = 21
        Enabled = False
        TabOrder = 2
        OnChange = edt_spritesPathChange
      end
      object bt_spritesHQRDialog: TButton
        Left = 461
        Top = 170
        Width = 18
        Height = 18
        Caption = '...'
        Enabled = False
        TabOrder = 3
        OnClick = bt_spritesHQRDialogClick
      end
      object bt_bodyPath: TButton
        Left = 461
        Top = 90
        Width = 18
        Height = 18
        Caption = '...'
        Enabled = False
        TabOrder = 4
        OnClick = bt_bodyPathClick
      end
      object bt_entetiesDialog: TButton
        Left = 461
        Top = 50
        Width = 18
        Height = 18
        Caption = '...'
        TabOrder = 5
        OnClick = bt_entetiesDialogClick
      end
      object edt_animPath: TEdit
        Left = 8
        Top = 128
        Width = 473
        Height = 21
        Enabled = False
        TabOrder = 6
        OnChange = edt_spritesPathChange
      end
      object Button1: TButton
        Left = 461
        Top = 130
        Width = 18
        Height = 18
        Caption = '...'
        Enabled = False
        TabOrder = 7
        OnClick = Button1Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Syntax Highlight'
      ImageIndex = 2
      object cb_syntax: TCheckBox
        Left = 8
        Top = 8
        Width = 321
        Height = 17
        Caption = 
          'Display scripts with syntax highlight. (Can slow a bit script lo' +
          'ad)'
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = cb_syntaxClick
      end
      object bt_defaultSyntaxColors: TButton
        Left = 408
        Top = 0
        Width = 97
        Height = 25
        Caption = 'Default Colors'
        Enabled = False
        TabOrder = 1
        OnClick = bt_defaultSyntaxColorsClick
      end
      object GroupBox1: TGroupBox
        Left = 264
        Top = 32
        Width = 233
        Height = 113
        Caption = 'Track Script Colors: '
        Enabled = False
        TabOrder = 2
        object Label17: TLabel
          Left = 8
          Top = 20
          Width = 50
          Height = 13
          Caption = 'Label/End'
          Enabled = False
        end
        object Label18: TLabel
          Left = 8
          Top = 68
          Width = 22
          Height = 13
          Caption = 'Stop'
          Enabled = False
        end
        object Label19: TLabel
          Left = 120
          Top = 20
          Width = 35
          Height = 13
          Caption = 'Macros'
          Enabled = False
        end
        object color_tracklabel: TColorBox
          Left = 8
          Top = 36
          Width = 97
          Height = 22
          Selected = clGreen
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 0
          OnChange = color_tracklabelChange
        end
        object color_trackstop: TColorBox
          Left = 8
          Top = 84
          Width = 97
          Height = 22
          Selected = clRed
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 1
          OnChange = color_trackstopChange
        end
        object color_trackmacros: TColorBox
          Left = 120
          Top = 36
          Width = 97
          Height = 22
          Selected = clBlue
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 2
          OnChange = color_trackmacrosChange
        end
      end
      object GroupBox4: TGroupBox
        Left = 8
        Top = 32
        Width = 249
        Height = 113
        Caption = 'Life Script Colors: '
        Enabled = False
        TabOrder = 3
        object Label5: TLabel
          Left = 8
          Top = 20
          Width = 73
          Height = 13
          Caption = 'Comportaments'
          Enabled = False
        end
        object Label12: TLabel
          Left = 8
          Top = 68
          Width = 49
          Height = 13
          Caption = 'Conditions'
          Enabled = False
        end
        object Label13: TLabel
          Left = 128
          Top = 68
          Width = 95
          Height = 13
          Caption = 'Conditions Variables'
          Enabled = False
        end
        object Label14: TLabel
          Left = 128
          Top = 20
          Width = 35
          Height = 13
          Caption = 'Macros'
          Enabled = False
        end
        object color_comp: TColorBox
          Left = 8
          Top = 36
          Width = 97
          Height = 22
          Selected = clGreen
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 0
          OnChange = color_compChange
        end
        object color_cond: TColorBox
          Left = 8
          Top = 84
          Width = 97
          Height = 22
          Selected = clRed
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 1
          OnChange = color_condChange
        end
        object color_condvars: TColorBox
          Left = 128
          Top = 84
          Width = 97
          Height = 22
          Selected = clFuchsia
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 2
          OnChange = color_condvarsChange
        end
        object color_macros: TColorBox
          Left = 128
          Top = 36
          Width = 97
          Height = 22
          Selected = clBlue
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 3
          OnChange = color_macrosChange
        end
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 152
        Width = 489
        Height = 65
        Caption = 'Common Colors: '
        Enabled = False
        TabOrder = 4
        object Label15: TLabel
          Left = 8
          Top = 16
          Width = 42
          Height = 13
          Caption = 'Numbers'
          Enabled = False
        end
        object Label16: TLabel
          Left = 128
          Top = 16
          Width = 212
          Height = 13
          Caption = 'Comments ( ex: REM This is a comment line )'
          Enabled = False
        end
        object color_numbers: TColorBox
          Left = 8
          Top = 35
          Width = 97
          Height = 22
          Selected = clMaroon
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 0
          OnChange = color_numbersChange
        end
        object color_comments: TColorBox
          Left = 128
          Top = 35
          Width = 97
          Height = 22
          Selected = clTeal
          Style = [cbStandardColors, cbIncludeDefault, cbCustomColor, cbPrettyNames]
          Enabled = False
          ItemHeight = 16
          TabOrder = 1
          OnChange = color_commentsChange
        end
      end
    end
  end
  object settings_opendialog: TOpenDialog
    Filter = 'Scene.hqr|Scene.hqr'
    Title = 'Load High Quality Resource file'
    Left = 360
    Top = 24
  end
end
