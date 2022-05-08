object frm_batchsaving: Tfrm_batchsaving
  Left = 229
  Top = 168
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Batch Saving...'
  ClientHeight = 356
  ClientWidth = 572
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object bar_savebatch: TCGauge
    Left = 104
    Top = 329
    Width = 361
    Height = 22
    Enabled = False
    ForeColor = clNavy
  end
  object bt_runbatch: TButton
    Left = 8
    Top = 328
    Width = 89
    Height = 25
    Caption = 'Run Batch'
    Enabled = False
    TabOrder = 0
    OnClick = bt_runbatchClick
  end
  object bt_closebatch: TButton
    Left = 472
    Top = 328
    Width = 89
    Height = 25
    Caption = 'Close'
    TabOrder = 1
    OnClick = bt_closebatchClick
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 572
    Height = 321
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = 'Step 1: Files'
      object Panel2: TPanel
        Left = 0
        Top = 8
        Width = 561
        Height = 281
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 0
        object Bevel1: TBevel
          Left = 8
          Top = 8
          Width = 545
          Height = 25
        end
        object Label1: TLabel
          Left = 16
          Top = 16
          Width = 129
          Height = 13
          Caption = 'Step 1: Choose source files'
        end
        object lb_numbatchlist: TLabel
          Left = 484
          Top = 16
          Width = 59
          Height = 13
          Alignment = taRightJustify
          Caption = '(0 files in list)'
        end
        object list_batchfiles: TListBox
          Left = 8
          Top = 40
          Width = 449
          Height = 233
          ItemHeight = 13
          MultiSelect = True
          TabOrder = 0
        end
        object bt_batchaddfiles: TButton
          Left = 464
          Top = 40
          Width = 89
          Height = 25
          Caption = 'Add Files...'
          TabOrder = 1
          OnClick = bt_batchaddfilesClick
        end
        object bt_batchremove: TButton
          Left = 464
          Top = 216
          Width = 89
          Height = 25
          Caption = 'Remove'
          TabOrder = 2
          OnClick = bt_batchremoveClick
        end
        object bt_batchremoveall: TButton
          Left = 464
          Top = 248
          Width = 89
          Height = 25
          Caption = 'Remove All'
          TabOrder = 3
          OnClick = bt_batchremoveallClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Step 2: Formats'
      ImageIndex = 1
      object Panel1: TPanel
        Left = 0
        Top = 8
        Width = 561
        Height = 281
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 0
        object Bevel2: TBevel
          Left = 8
          Top = 8
          Width = 545
          Height = 25
        end
        object Label2: TLabel
          Left = 16
          Top = 16
          Width = 154
          Height = 13
          Caption = 'Step 2: Choose output file format'
        end
        object rg_batchoutputformat: TRadioGroup
          Left = 8
          Top = 40
          Width = 545
          Height = 97
          Caption = 'Output format: '
          ItemIndex = 1
          Items.Strings = (
            '*.scp (LBA Story Coder Project)'
            '*.ls1 (LBA1 Binary Scene File)'
            '*.sce (Text Scene for TwinEngine)')
          TabOrder = 0
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Step 3: Destination'
      ImageIndex = 2
      object Panel3: TPanel
        Left = 0
        Top = 8
        Width = 561
        Height = 281
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 0
        object Bevel3: TBevel
          Left = 8
          Top = 8
          Width = 545
          Height = 25
        end
        object Label3: TLabel
          Left = 16
          Top = 16
          Width = 156
          Height = 13
          Caption = 'Step 3: Choose destination folder'
        end
        object Label4: TLabel
          Left = 8
          Top = 48
          Width = 88
          Height = 13
          Caption = 'Destination Folder:'
        end
        object edt_destfolder: TEdit
          Left = 8
          Top = 64
          Width = 457
          Height = 21
          TabOrder = 0
        end
        object Button1: TButton
          Left = 472
          Top = 62
          Width = 75
          Height = 22
          Caption = 'Browse'
          TabOrder = 1
          OnClick = Button1Click
        end
      end
    end
  end
  object dialog_addfiles: TOpenDialog
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 544
  end
  object dialog_folder: TFolderDialog
    Title = 'Choose Destination Folder'
    Directory = 'D:\XesF\LBA\LBA Story Coder'
    DialogX = 0
    DialogY = 0
    Version = '1.0.0.0'
    Left = 512
  end
end
