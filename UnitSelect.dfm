object FormSelect: TFormSelect
  Left = 631
  Top = 123
  ActiveControl = PlayersList
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = '����� ���������'
  ClientHeight = 218
  ClientWidth = 287
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    0000800080008080000080808000C0C0C0000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00888888888888888808888888888888888888
    88CCCCC88888088888888888888888888C0CCC0C888808888888888888888888
    CCC888CCC8880888888888888888888CC8888888CC880888888888888888888C
    C8888888CC88088888888888888888CC888888888CC8088888888888888888CC
    888888888CC8088888888888888888CC888888888CC80888888888888888888C
    C8888888CC880888888888888888888CC8888888CC8808888888888888888888
    CCC888CCC888088888888888888888888C0CCC0C888808888888888888888888
    88CCCCC888880888888888888888888888888888888808888888888888888000
    0000000000000000000000000000888888888888888808888888888888888899
    888888888998088888CCCCC88888889998888888999808888C0CCC0C88888889
    9988888999880888CCC888CCC8888888999888999888088CC8888888CC888888
    899989998888088CC8888888CC88888888999998888808CC888888888CC88888
    88899988888808CC888888888CC8888888999998888808CC888888888CC88888
    899989998888088CC8888888CC888888999888999888088CC8888888CC888889
    9988888999880888CCC888CCC888889998888888999808888C0CCC0C88888899
    888888888998088888CCCCC88888888888888888888808888888888888888888
    8888888888888888888888888888000000000000000002200000000000000000
    0000000000000000000000000000000000000000000000000000000000000220
    0000000000000000000000000000000000000000000000000220000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0220000000000000000000000000280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    00000080800080000000800080008080000080808000C0C0C0000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF008888888808888888888C
    CC880888888888C888C80888888888C888C80888888888C888C808888888888C
    CC88088888888888888808888888800000000000000088888888088888888898
    8898088CCC888889898808C888C88888988808C888C88889898808C888C88898
    8898088CCC888888888808888888888888888888888800000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    00000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 56
    Width = 273
    Height = 121
    Caption = '������'
    TabOrder = 0
    object PlayersList: TListView
      Left = 8
      Top = 16
      Width = 257
      Height = 94
      Columns = <
        item
          Caption = 'Name'
          Width = 150
        end
        item
          AutoSize = True
          Caption = 'Status'
        end>
      ColumnClick = False
      FlatScrollBars = True
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      ShowColumnHeaders = False
      TabOrder = 0
      ViewStyle = vsReport
      OnCustomDrawItem = PlayersListCustomDrawItem
      OnDblClick = PlayersListDblClick
    end
  end
  object Button1: TButton
    Left = 8
    Top = 184
    Width = 75
    Height = 25
    Caption = '������'
    Default = True
    TabOrder = 2
    OnClick = Button1Click
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 8
    Width = 273
    Height = 41
    Caption = '����������'
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 161
      Height = 13
      Caption = '�������� ��������� �� ������'
      Color = clBtnFace
      ParentColor = False
    end
  end
  object Button2: TButton
    Left = 96
    Top = 184
    Width = 75
    Height = 25
    Cancel = True
    Caption = '������'
    Enabled = False
    TabOrder = 3
    OnClick = Button2Click
  end
end
