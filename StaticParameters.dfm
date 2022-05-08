object frm_staticpar: Tfrm_staticpar
  Left = 423
  Top = 185
  HelpContext = 227
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Flags - LBA Story Coder'
  ClientHeight = 200
  ClientWidth = 339
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object cb1: TCheckBox
    Left = 8
    Top = 8
    Width = 177
    Height = 17
    HelpContext = 228
    Caption = 'Compute collisions with objects'
    TabOrder = 0
    OnClick = cb1Click
  end
  object cb2: TCheckBox
    Left = 8
    Top = 32
    Width = 169
    Height = 17
    HelpContext = 229
    Caption = 'Compute collisions with bricks'
    TabOrder = 1
    OnClick = cb2Click
  end
  object cb3: TCheckBox
    Left = 8
    Top = 56
    Width = 81
    Height = 17
    HelpContext = 230
    Caption = 'Is zonable'
    TabOrder = 2
    OnClick = cb3Click
  end
  object cb4: TCheckBox
    Left = 8
    Top = 80
    Width = 97
    Height = 17
    HelpContext = 231
    Caption = 'Uses clipping'
    TabOrder = 3
    OnClick = cb4Click
  end
  object cb5: TCheckBox
    Left = 8
    Top = 104
    Width = 105
    Height = 17
    HelpContext = 232
    Caption = 'Can be pushed'
    TabOrder = 4
    OnClick = cb5Click
  end
  object cb6: TCheckBox
    Left = 8
    Top = 128
    Width = 129
    Height = 17
    HelpContext = 233
    Caption = 'Compute low collison'
    TabOrder = 5
    OnClick = cb6Click
  end
  object cb7: TCheckBox
    Left = 8
    Top = 152
    Width = 129
    Height = 17
    HelpContext = 234
    Caption = 'Can test the floor type'
    TabOrder = 6
    OnClick = cb7Click
  end
  object cb8: TCheckBox
    Left = 8
    Top = 176
    Width = 73
    Height = 17
    HelpContext = 235
    Caption = 'Unused'
    Enabled = False
    TabOrder = 7
    OnClick = cb8Click
  end
  object cb9: TCheckBox
    Left = 208
    Top = 8
    Width = 73
    Height = 17
    HelpContext = 236
    Caption = 'Unused'
    Enabled = False
    TabOrder = 8
    OnClick = cb9Click
  end
  object cb10: TCheckBox
    Left = 208
    Top = 32
    Width = 65
    Height = 17
    HelpContext = 237
    Caption = 'Hidden'
    TabOrder = 9
    OnClick = cb10Click
  end
  object cb11: TCheckBox
    Left = 208
    Top = 56
    Width = 89
    Height = 17
    HelpContext = 238
    Caption = 'Is sprite actor'
    TabOrder = 10
    OnClick = cb11Click
  end
  object cb12: TCheckBox
    Left = 208
    Top = 80
    Width = 65
    Height = 17
    HelpContext = 239
    Caption = 'Can fall'
    TabOrder = 11
    OnClick = cb12Click
  end
  object cb13: TCheckBox
    Left = 208
    Top = 104
    Width = 129
    Height = 17
    HelpContext = 240
    Caption = 'Doens'#39't cast shadow'
    TabOrder = 12
    OnClick = cb13Click
  end
  object cb14: TCheckBox
    Left = 208
    Top = 128
    Width = 113
    Height = 17
    HelpContext = 241
    Caption = 'Is backgrounded'
    TabOrder = 13
    OnClick = cb14Click
  end
  object cb15: TCheckBox
    Left = 208
    Top = 152
    Width = 121
    Height = 17
    HelpContext = 242
    Caption = 'Is a carrier actor'
    TabOrder = 14
    OnClick = cb15Click
  end
  object cb16: TCheckBox
    Left = 208
    Top = 176
    Width = 89
    Height = 17
    HelpContext = 243
    Caption = 'Use mini ZV'
    TabOrder = 15
    OnClick = cb16Click
  end
end
