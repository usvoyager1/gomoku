object FormConnecting: TFormConnecting
  Left = 486
  Top = 311
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Connect to server'
  ClientHeight = 48
  ClientWidth = 296
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 16
    Width = 69
    Height = 13
    Caption = 'Connecting to '
  end
  object Animate1: TAnimate
    Left = 8
    Top = 16
    Width = 16
    Height = 16
    Active = False
    CommonAVI = aviFindComputer
    StopFrame = 8
    Timers = True
  end
end
