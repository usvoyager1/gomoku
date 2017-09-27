//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#define MAX_COMPS 3

#include "UnitMain.h"
#include "UnitSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSelect *FormSelect;
extern TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormSelect::TFormSelect(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSelect::Button1Click(TObject *Sender)
{
	if(!PlayersList->Selected) return;
	FormMain->Play((int)PlayersList->Selected->Data);
	PlayersList->Refresh();
	Button1->Enabled=false;
	Button2->Enabled=true;
//  Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelect::Button2Click(TObject *Sender)
{
	FormMain->CancelPlay();
	Button1->Enabled=true;
	Button2->Enabled=false;
	PlayersList->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormSelect::PlayersListCustomDrawItem(
	TCustomListView *Sender, TListItem *Item, TCustomDrawState State,
	bool &DefaultDraw)
{
	if(!Item) return;
	if((int)Item->Data==FormMain->OpponentID) {
		PlayersList->Canvas->Font->Color=clBlue;
		PlayersList->Canvas->Font->Style=PlayersList->Font->Style<<fsBold;
	}else{
		PlayersList->Canvas->Font->Color=clBlack;
		PlayersList->Canvas->Font->Style=PlayersList->Font->Style>>fsBold;
	}
	if((int)Item->Data<MAX_COMPS)
		PlayersList->Canvas->Font->Style=PlayersList->Font->Style<<fsItalic;
	else
		PlayersList->Canvas->Font->Style=PlayersList->Font->Style>>fsItalic;

}
//---------------------------------------------------------------------------


void __fastcall TFormSelect::PlayersListDblClick(TObject *Sender)
{
	Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormSelect::FormClose(TObject *Sender,
                                       TCloseAction &Action)
{
	FormMain->Enabled=true;
}
//---------------------------------------------------------------------------

