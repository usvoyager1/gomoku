//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitConnecting.h"
//---------------------------------------------------------------------------
extern TFormMain *FormMain;
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormConnecting *FormConnecting;
//---------------------------------------------------------------------------
__fastcall TFormConnecting::TFormConnecting(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormConnecting::FormShow(TObject *Sender)
{
	Animate1->Top=ClientHeight/2-Animate1->Height/2;
	Label1->Left=Animate1->Left+Animate1->Width+8;
	Animate1->Active=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormConnecting::FormHide(TObject *Sender)
{
	Animate1->Active=false;
}
//---------------------------------------------------------------------------


