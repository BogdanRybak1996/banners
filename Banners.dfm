object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1042#1080#1088#1110#1079#1072#1095' '#1073#1072#1085#1077#1088#1110#1074
  ClientHeight = 540
  ClientWidth = 606
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 184
    Top = 8
    Width = 229
    Height = 19
    Caption = #1064#1083#1103#1093' '#1076#1086' '#1074#1093#1110#1076#1085#1086#1075#1086' .html '#1092#1072#1081#1083#1091':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 175
    Top = 128
    Width = 238
    Height = 19
    Caption = #1064#1083#1103#1093' '#1076#1086' '#1074#1080#1093#1110#1076#1085#1086#1075#1086' .html '#1092#1072#1081#1083#1091':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 184
    Top = 264
    Width = 213
    Height = 19
    Caption = #1064#1083#1103#1093' '#1076#1086' '#1092#1072#1081#1083#1091' '#1079' '#1092#1110#1083#1100#1090#1088#1072#1084#1080':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 461
    Top = 408
    Width = 121
    Height = 41
    Caption = #1055#1086#1095#1072#1090#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object SellectButton1: TButton
    Left = 440
    Top = 48
    Width = 75
    Height = 25
    Caption = #1042#1080#1073#1088#1072#1090#1080
    TabOrder = 1
    OnClick = SellectButton1Click
  end
  object Edit1: TEdit
    Left = 109
    Top = 50
    Width = 325
    Height = 21
    Enabled = False
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 109
    Top = 175
    Width = 325
    Height = 21
    Enabled = False
    TabOrder = 3
  end
  object SelectButton2: TButton
    Left = 440
    Top = 173
    Width = 75
    Height = 25
    Caption = #1042#1080#1073#1088#1072#1090#1080
    TabOrder = 4
    OnClick = SelectButton2Click
  end
  object CreateButton: TButton
    Left = 440
    Top = 202
    Width = 75
    Height = 25
    Caption = #1057#1090#1074#1086#1088#1080#1090#1080
    TabOrder = 5
    OnClick = CreateButtonClick
  end
  object Button2: TButton
    Left = 523
    Top = 507
    Width = 75
    Height = 25
    Caption = #1042#1080#1081#1090#1080
    TabOrder = 6
    OnClick = Button2Click
  end
  object Edit3: TEdit
    Left = 109
    Top = 303
    Width = 325
    Height = 21
    Enabled = False
    TabOrder = 7
  end
  object Button3: TButton
    Left = 440
    Top = 301
    Width = 75
    Height = 25
    Caption = #1042#1080#1073#1088#1072#1090#1080
    TabOrder = 8
    OnClick = Button3Click
  end
  object StatusListBox: TListBox
    Left = 8
    Top = 344
    Width = 426
    Height = 156
    ItemHeight = 13
    TabOrder = 9
  end
  object Button4: TButton
    Left = 16
    Top = 506
    Width = 99
    Height = 30
    Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
    TabOrder = 10
    OnClick = Button4Click
  end
  object OpenDialog1: TOpenDialog
    Filter = 'HTML|*.html|HTM|*.htm'
    Left = 544
    Top = 48
  end
  object OpenDialog2: TOpenDialog
    Filter = 'HTML|*.html|HTM|*.htm'
    Left = 544
    Top = 168
  end
  object OpenDialog3: TOpenDialog
    Filter = 'TXT|*.txt'
    Left = 536
    Top = 304
  end
end
