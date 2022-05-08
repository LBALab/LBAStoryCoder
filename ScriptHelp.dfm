object frm_scripthelp: Tfrm_scripthelp
  Left = 308
  Top = 185
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Game Descriptions Values'
  ClientHeight = 455
  ClientWidth = 674
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lb_list: TListBox
    Left = -1
    Top = 34
    Width = 674
    Height = 401
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 0
  end
  object sb_help: TStatusBar
    Left = 0
    Top = 436
    Width = 674
    Height = 19
    Panels = <
      item
        Text = 'Help: '
        Width = 50
      end>
    SimplePanel = False
  end
  object ComboBox1: TComboBox
    Left = 0
    Top = 8
    Width = 177
    Height = 21
    DropDownCount = 17
    ItemHeight = 13
    TabOrder = 2
    Text = 'Move Syntax'
    OnChange = ComboBox1Change
    Items.Strings = (
      'Game Flags'
      'Chapters'
      'Magic Levels'
      'Twinsen Behaviours'
      'Holomap Locations and Cube Zones'
      'Inventory'
      'Disappearing Grids'
      'FLA file names list'
      'Midis'
      'Samples'
      'Sprites'
      'Bodies'
      'Animations')
  end
end
