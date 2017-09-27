object FormConnect: TFormConnect
  Left = 337
  Top = 399
  ActiveControl = Button2
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Connect to server'
  ClientHeight = 123
  ClientWidth = 390
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button2: TButton
    Left = 296
    Top = 16
    Width = 83
    Height = 25
    Caption = 'Соединиться'
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 296
    Top = 48
    Width = 83
    Height = 25
    Cancel = True
    Caption = 'Отмена'
    ModalResult = 2
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 273
    Height = 49
    Caption = 'Ваше имя'
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 257
      Height = 21
      TabOrder = 0
      Text = 'Player 1'
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 64
    Width = 273
    Height = 49
    Caption = 'Сетевой адрес сервера'
    TabOrder = 1
    object Edit2: TEdit
      Left = 8
      Top = 20
      Width = 225
      Height = 21
      TabOrder = 0
      Text = '127.0.0.1'
    end
    object Panel1: TPanel
      Left = 240
      Top = 19
      Width = 23
      Height = 23
      BorderStyle = bsSingle
      Caption = '...'
      TabOrder = 1
      OnMouseDown = Panel1MouseDown
    end
  end
  object PopupMenu1: TPopupMenu
    Alignment = paCenter
    AutoHotkeys = maManual
    TrackButton = tbLeftButton
    Left = 304
    Top = 80
    object localhost1: TMenuItem
      Caption = 'localhost'
      OnClick = PopupClick
    end
  end
end
