//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitConnect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormConnect *FormConnect;
//---------------------------------------------------------------------------
__fastcall TFormConnect::TFormConnect(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormConnect::FormShow(TObject *Sender)
{
	ActiveControl=Button2;
	if(PopupMenu1->Items->Count==0) {
		Panel1->Enabled=false;
	}else{
		while(PopupMenu1->Items->Count>5)
			PopupMenu1->Items->Delete(0);
		Panel1->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormConnect::PopupClick(TObject *Sender)
{
	AnsiString s1=((TMenuItem*)Sender)->Caption;
	if(s1.Pos("&")) s1.Delete(s1.Pos("&"),1);
	Edit2->Text=s1;
}

void __fastcall TFormConnect::Panel1MouseDown(TObject *Sender,
                                              TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button!=mbLeft) return;
	TPoint a=Panel1->ClientToScreen(TPoint(X,Y));
	PopupMenu1->Popup(a.x,a.y);
}
//---------------------------------------------------------------------------

void __fastcall TFormConnect::Button2Click(TObject *Sender)
{
	AnsiString s1;
	for(int i=0; i<PopupMenu1->Items->Count; i++) {
		s1=PopupMenu1->Items->Items[i]->Caption;
		if(s1.Pos("&")) s1.Delete(s1.Pos("&"),1);
		if(s1==Edit2->Text) return;
	}
	TMenuItem *item=new TMenuItem(PopupMenu1);
	item->Caption=Edit2->Text;
	item->OnClick=PopupClick;
	PopupMenu1->Items->Add(item);
}
//---------------------------------------------------------------------------

