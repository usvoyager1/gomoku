//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitConnect.h"
#include "UnitConnecting.h"
#include "UnitSelect.h"
#include "UnitAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
extern TFormConnect *FormConnect;
extern TFormConnecting *FormConnecting;
extern TFormSelect *FormSelect;

#define SMILE_DOWN  0
#define SMILE_WIN   1
#define SMILE_BAD   2
#define SMILE_CLICK 3
#define SMILE_OK    4


enum GAMESTATUS {PLAY,WIN,LOST};
enum MYSTATUS {DISCONNECTED,CONNECTED,PLAYING};
MYSTATUS Status=DISCONNECTED;
GAMESTATUS GameStatus=PLAY;
enum TURN {MY_TURN,OPP_TURN};
TURN Turn;

int ppp[20][20];
char MyFig=1;
int GameTime=0;
int GameTimePic1=10,GameTimePic2=10,GameTimePic3=10;
int GameMoves=0;
int GameMovesPic1=10,GameMovesPic2=10,GameMovesPic3=10;
void SetTurn(TURN t)
{
	Turn=t;
	if(Turn==MY_TURN) {
		if(!FormMain->Timer1->Enabled)
			FormMain->Timer1->Enabled=true;
		FormMain->PaintBox1->Cursor=crDefault;
		Screen->Cursor=crDefault;
	}else{
		FormMain->PaintBox1->Cursor=GameStatus==PLAY ? crAppStart : crDefault;
		Screen->Cursor=FormMain->PaintBox1->Cursor;
	}
}
void SetGameTime(int t)
{
	GameTime=t;
	if(GameTime>999) GameTime=999;
	if(GameTime<0) GameTime=0;
	AnsiString s;
	s.sprintf("%3d",GameTime);
	if(s[1]==' ') GameTimePic1=10;
	else GameTimePic1=s[1]-'0';
	if(s[2]==' ') GameTimePic2=10;
	else GameTimePic2=s[2]-'0';
	if(s[3]==' ') GameTimePic3=10;
	else GameTimePic3=s[3]-'0';
	FormMain->PaintBox3->Refresh();
}
void SetGameMoves(int m)
{
	GameMoves=m;
	if(GameMoves>999) GameMoves=999;
	if(GameMoves<0) GameMoves=0;
	AnsiString s;
	s.sprintf("%3d",GameMoves);
	if(s[1]==' ') GameMovesPic1=10;
	else GameMovesPic1=s[1]-'0';
	if(s[2]==' ') GameMovesPic2=10;
	else GameMovesPic2=s[2]-'0';
	if(s[3]==' ') GameMovesPic3=10;
	else GameMovesPic3=s[3]-'0';
	FormMain->PaintBox4->Refresh();
}

void SendMsg(TCustomWinSocket *s,AnsiString str)
{
	s->SendText(str);
	s->SendBuf("\n",1);
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	OpponentID=-1;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PaintBox1Paint(TObject *Sender)
{
	TCanvas *c=PaintBox1->Canvas;
	c->CopyMode=cmSrcCopy;
	for(int i=0; i<20; i++)
		for(int j=0; j<20; j++) {
			DrawCell(c,j,i);
		}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintBox1MouseMove(TObject *Sender,
                                              TShiftState Shift, int X, int Y)
{
	int ox=msx,oy=msy;
	if(X/16!=msx || Y/16!=msy) {
		msx=X/16,msy=Y/16;
		if(msx<0) msx=0; if(msy<0) msy=0;
		if(msx>19) msx=19; if(msy>19) msy=19;
		DrawCell(PaintBox1->Canvas,ox,oy);
		DrawCell(PaintBox1->Canvas,msx,msy);
	}
}
//---------------------------------------------------------------------------
Graphics::TBitmap *bmp[9];

void __fastcall TFormMain::DrawCell(TCanvas * c, int j, int i)
{
	int n=ppp[i][j];
	if(msx==j && msy==i && ppp[i][j]==0 && Turn==MY_TURN) {
		if(Status==PLAYING && GameStatus==PLAY) {
			n+=3;
			if(msb) n+=3;
		}
	}
	c->Draw(j*16,i*16,bmp[n]);
//  ImgPanels->Draw(c,j*16,i*16,n,true);
}
void __fastcall TFormMain::PaintBox1MouseDown(TObject *Sender,
                                              TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button!=mbLeft) return;
	if(GameStatus!=PLAY || Status!=PLAYING || Turn!=MY_TURN) return;
	msb=true;
	DrawCell(PaintBox1->Canvas,msx,msy);
	Mouse->Capture=WindowFromDC(PaintBox1->Canvas->Handle);
	ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_CLICK,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintBox1MouseUp(TObject *Sender,
                                            TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button!=mbLeft || msb==false) return;
	msb=false;
	DrawCell(PaintBox1->Canvas,msx,msy);
	ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_OK,true);
	Mouse->Capture=NULL;
	if(X>=0&&Y>=0&&X<PaintBox1->Width&&Y<PaintBox1->Height) {
		MakeTurn(msx,msy);
//    Timer1->Enabled=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionConnectExecute(TObject *Sender)
{
	if(ClientSocket1->Active) {
		ShowMessage("Before disconnect!");
		return;
	}
	if(FormConnect->ShowModal()==mrOk)
	{
		FormSelect->PlayersList->Items->Clear();
		FormSelect->Label1->Caption="Выберите соперника из списка";
		Application->ProcessMessages();
		myID=-1;
		int i=1;
		for(; i<=FormConnect->Edit2->Text.Length(); i++)
			if((FormConnect->Edit2->Text[i]<'0'||FormConnect->Edit2->Text[i]>'9') && FormConnect->Edit2->Text[i]!='.')
				break;
		if(i<FormConnect->Edit2->Text.Length())
			ClientSocket1->Host=FormConnect->Edit2->Text;
		else{
			ClientSocket1->Host="";
			ClientSocket1->Address=FormConnect->Edit2->Text;
		}
		ClientSocket1->Open();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocket1Connect(TObject *Sender,
                                                TCustomWinSocket *Socket)
{
	ActionConnect->Enabled=false;
	ActionDisconnect->Enabled=true;
	FormConnecting->Hide();
	ServerSocket=Socket;
	ActionSelect->Enabled=true;
	Enabled=true;
/*  if(!FormSelect->Visible){
    Enabled=false;
    FormSelect->Show();
   }
   if(ClientSocket1->Host!="")
    Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Host;
   else
    Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Address;
   PaintBox2->Hint="Выбрать оппонента";
   Status=CONNECTED;*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocket1Connecting(TObject *Sender,
                                                   TCustomWinSocket *Socket)
{
	FormConnecting->Label1->Caption=
		AnsiString("Connecting to ")+FormConnect->Edit2->Text+" ...";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocket1Error(TObject *Sender,
                                              TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
	switch(ErrorEvent) {
	case eeConnect:
		FormConnecting->Hide();
		Enabled=true;
		ActionConnect->Enabled=true;
		if(ErrorCode==10061)
			ShowMessage(AnsiString("Cannot connect to ")+FormConnect->Edit2->Text+"\n\nGoServer on this machine not started!");
		else if(ErrorCode==10049)
			ShowMessage(AnsiString("Cannot connect to ")+FormConnect->Edit2->Text+"\n\nHost not found.");
		else
			ShowMessage(AnsiString("Error while connecting: #")+ErrorCode);
		break;
	case eeDisconnect:
		if(ErrorCode==10053) {
			if(!ClientSocket1->Active) return;
			ClientSocket1->Active=false;
		}else
			ShowMessage(AnsiString("Unknown (type=disconnect) error: #")+ErrorCode);
		break;
	default:
		ShowMessage(AnsiString("Unknown (type=")+ErrorEvent+") error: #"+ErrorCode);
	}
	ErrorCode=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocket1Lookup(TObject *Sender,
                                               TCustomWinSocket *Socket)
{
	FormConnecting->Label1->Caption=
		AnsiString("Lookup for ")+FormConnect->Edit2->Text +" ...";
	Enabled=false;
	FormConnecting->Show();
	ActionConnect->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocket1Disconnect(TObject *Sender,
                                                   TCustomWinSocket *Socket)
{
	if(FormConnecting->Visible) {
		FormConnecting->Hide();
		Enabled=true;
		return;
	}
	ActionDisconnect->Enabled=false;
	ActionConnect->Enabled=true;
	ActionSelect->Enabled=false;
	FormSelect->Button1->Enabled=true;
	FormSelect->Button2->Enabled=false;
	OpponentID=-1;
	ActionNew->Enabled=false;
	PaintBox1->Cursor=crDefault;
	Timer1->Enabled=false;
	Status=DISCONNECTED;
	if(FormSelect->Visible) FormSelect->Hide();
	Enabled=true;
	Caption="Gomoku - not connected";
	PaintBox2->Hint="Подсоединиться к серверу";
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(ClientSocket1->Active) {
		ClientSocket1->Close();
		while(ClientSocket1->Active) {}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionDisconnectExecute(TObject *Sender)
{
	if(!ClientSocket1->Active) return;
	ClientSocket1->Close();
	Caption="Gomoku - not connected";
	PaintBox2->Hint="Подсоединиться к серверу";
}
//---------------------------------------------------------------------------
AnsiString bufAll="";
void __fastcall TFormMain::ClientSocket1Read(TObject *Sender,
                                             TCustomWinSocket *Socket)
{
/*  int pos=0;
   while(Socket->ReceiveLength()==0 && pos<10){
    Application->ProcessMessages();
    pos++;
   }*/
	if(Socket->ReceiveLength()==0) return;
	bufAll=bufAll+Socket->ReceiveText();
	AnsiString buf;
	int ppp;
	do {
		ppp=bufAll.Pos("\n");
		if(ppp) {
			buf=bufAll.SubString(1,ppp-1);
			bufAll=bufAll.SubString(ppp+1,bufAll.Length()-ppp);
		}else break; //buf=bufAll;
		if(buf=="") break;
		AnsiString left,right;
		int p;
		if((p=buf.Pos("="))!=0) {
			left=buf.SubString(1,p-1);
			right=buf.SubString(p+1,buf.Length()-p);
		}else{left=buf; right="";}

		if(left=="CONNECTED") {
			if(!FormSelect->Visible) {
				Enabled=false;
				FormSelect->Show();
			}
			if(ClientSocket1->Host!="")
				Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Host;
			else
				Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Address;
			PaintBox2->Hint="Выбрать оппонента";
			myID=StrToInt(right);
			Status=CONNECTED;
			SendMsg(ServerSocket,AnsiString("NAME=")+FormConnect->Edit1->Text);
		}else if(myID==-1) { // if we are not connected to server
			bufAll="";
			Caption="Gomoku - not connected";
			PaintBox2->Hint="Подсоединиться к серверу";
			ActionDisconnectExecute(ActionDisconnect);
			ShowMessage(buf);
//    Socket->Close();
			return;
		}else
		if(left=="ADD_OPPONENT") {
			int n=StrToInt(right.SubString(1,right.Pos(",")-1));
			if(n!=myID) {
				if(FormSelect->PlayersList->Items->Count==0) {
					if(FormSelect->Label1->Caption!="Ждите ответа от игрока")
						FormSelect->Label1->Caption="Выберите соперника из списка";
				}
				TListItem *it=FormSelect->PlayersList->Items->Add();
				it->Caption=right.SubString(right.Pos(",")+1,right.Length()-right.Pos(","));
				it->Data=(void*)n;
				it->SubItems->Add("-");
			}
		}else if(left=="DEL_OPPONENT") {
			void *n=(void*)StrToInt(right);
			if(OpponentID==(int)n) {
				OpponentID=-1;
				ActionNew->Enabled=false;
				PaintBox1->Cursor=crDefault;
				FormSelect->Label1->Caption="Выберите соперника из списка";
				FormSelect->Button1->Enabled=true;
				FormSelect->Button2->Enabled=false;
				ActionSelect->Enabled=true;
				SendMsg(ClientSocket1->Socket,"PLAY_CANCEL");
			}
			for(int i=0; i<FormSelect->PlayersList->Items->Count; i++)
				if(FormSelect->PlayersList->Items->Item[i]->Data==n) {
					FormSelect->PlayersList->Items->Delete(i);
					break;
				}
			if(FormSelect->PlayersList->Items->Count==0) {
				FormSelect->Label1->Caption="Подождите подсоединения других игроков";
			}
		}else if(left=="MOD_OPPONENT") {
			void *n=(void*)StrToInt(right.SubString(1,right.Pos(",")-1));
			for(int i=0; i<FormSelect->PlayersList->Items->Count; i++)
				if(FormSelect->PlayersList->Items->Item[i]->Data==n) {
					FormSelect->PlayersList->Items->Item[i]->Caption=
						right.SubString(right.Pos(",")+1,right.Length()-right.Pos(","));
					break;
				}
		}else if(left=="PLAY")
		{
			void *n=(void*)StrToInt(right);
			for(int i=0; i<FormSelect->PlayersList->Items->Count; i++)
				if(FormSelect->PlayersList->Items->Item[i]->Data==n) {
					FormSelect->PlayersList->Items->Item[i]->SubItems->Strings[0]=
						"ask for play";
					break;
				}
		}else if(left=="PLAY_CANCELWAIT")
		{
			void *n=(void*)StrToInt(right);
			for(int j=0; j<FormSelect->PlayersList->Items->Count; j++)
				if(FormSelect->PlayersList->Items->Item[j]->Data==n) {
					FormSelect->PlayersList->Items->Item[j]->SubItems->Strings[0]="-";
					break;
				}
		}else if(left=="PLAY_CANCEL")
		{
			if(!FormSelect->Visible) {
				Enabled=false;
				FormSelect->Show();
			}
			FormSelect->Button1->Enabled=true;
			FormSelect->Button2->Enabled=false;
			ActionSelect->Enabled=true;
			Status=CONNECTED;
			OpponentID=-1;
			ActionNew->Enabled=false;
			PaintBox1->Cursor=crDefault;
			Timer1->Enabled=false;
			FormSelect->Label1->Caption="Выберите соперника из списка";
		}else if(left=="PLAY_OK")
		{
			if(FormSelect->Visible) FormSelect->Hide();
			Enabled=true;
			Status=PLAYING;
			ActionNew->Enabled=true;
			MyFig=right[1]-'0';
			if(right[2]=='F') SetTurn(MY_TURN); else SetTurn(OPP_TURN);
			MakeNew();
			Caption=AnsiString("Gomoku - playing with ")+OpponentName;
			PaintBox2->Hint="Новая игра";
		}else if(left=="TURN")
		{
			AnsiString x=right.SubString(1,right.Pos(",")-1);
			AnsiString y=right.SubString(right.Pos(",")+1,right.Length()-right.Pos(","));
			GetTurn(StrToInt(x),StrToInt(y));
		}else if(left=="START_NEW")
		{
			MakeNew();
		}else
			ShowMessage(buf);
	} while(ppp);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionExitExecute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionSelectExecute(TObject *Sender)
{
	if(!FormSelect->Visible) {
		if(Status==PLAYING) {
			if(MessageDlg("Хотите закончить игру и выбрать другого оппонента?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
				CancelPlay();
				FormSelect->Button1->Enabled=true;
				FormSelect->Button2->Enabled=false;
				Enabled=false;
				FormSelect->Show();
			}
		}else{
			Enabled=false;
			FormSelect->Show();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Play(int id)
{
	if(!ClientSocket1->Active) return;
	OpponentName=FormSelect->PlayersList->Selected->Caption;
	OpponentID=id;
	PaintBox1->Cursor=crDefault;
	SendMsg(ServerSocket,AnsiString("PLAY=")+id);
	FormSelect->Label1->Caption="Ждите ответа от игрока";
}

void __fastcall TFormMain::CancelPlay()
{
	SendMsg(ServerSocket,AnsiString("PLAY_CANCEL"));
	OpponentID=-1;
	ActionNew->Enabled=false;
	Timer1->Enabled=false;
	PaintBox1->Cursor=crDefault;
	Status=CONNECTED;
	if(FormSelect->PlayersList->Items->Count==0)
		FormSelect->Label1->Caption="Подождите подсоединения других игроков";
	else
		FormSelect->Label1->Caption="Выберите соперника из списка";
	if(ClientSocket1->Host!="")
		Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Host;
	else
		Caption=AnsiString("Gomoku - connected to ")+ClientSocket1->Address;
	PaintBox2->Hint="Выбрать оппонента";
}
static bool ImageClickDown=false;
void __fastcall TFormMain::Image1MouseDown(TObject *Sender,
                                           TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button!=mbLeft) return;
	Mouse->Capture=WindowFromDC(PaintBox2->Canvas->Handle);
	ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_DOWN,true);
	ImageClickDown=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Image1MouseUp(TObject *Sender,
                                         TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button!=mbLeft||!ImageClickDown) return;
	Mouse->Capture=NULL;
	ImageClickDown=false;
	if(X>=0 && X<24 && Y>=0 && Y<24) {
		ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_OK,true);
		ClickNew();
	}else
		ImageList1->Draw(PaintBox2->Canvas,0,0,GameStatus==PLAY ? SMILE_OK : (GameStatus==WIN ? SMILE_WIN : SMILE_BAD),true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Image1MouseMove(TObject *Sender,
                                           TShiftState Shift, int X, int Y)
{
	if(!ImageClickDown) return;
	if(X>=0 && X<24 && Y>=0 && Y<24)
		ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_DOWN,true);
	else
		ImageList1->Draw(PaintBox2->Canvas,0,0,GameStatus==PLAY ? SMILE_OK : (GameStatus==WIN ? SMILE_WIN : SMILE_BAD),true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PaintBox2Paint(TObject *Sender)
{
	ImageList1->Draw(PaintBox2->Canvas,
	                 0,0,
	                 (GameStatus==PLAY) ? SMILE_OK : ((GameStatus==WIN) ? SMILE_WIN : SMILE_BAD),
	                 true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PaintBox3Paint(TObject *Sender)
{
	ImgClocks->Draw(PaintBox3->Canvas,0,0,GameTimePic1,true);
	ImgClocks->Draw(PaintBox3->Canvas,13,0,GameTimePic2,true);
	ImgClocks->Draw(PaintBox3->Canvas,26,0,GameTimePic3,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintBox4Paint(TObject *Sender)
{
	ImgClocks->Draw(PaintBox4->Canvas,0,0,GameMovesPic1,true);
	ImgClocks->Draw(PaintBox4->Canvas,13,0,GameMovesPic2,true);
	ImgClocks->Draw(PaintBox4->Canvas,26,0,GameMovesPic3,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
	if(Turn==MY_TURN && GameStatus==PLAY && Status==PLAYING)
		SetGameTime(GameTime+1);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClickNew()
{
	switch(Status) {
	case DISCONNECTED:
		try{
			ActionConnectExecute(NULL);
		}catch(...) {}
		break;
	case CONNECTED:
		ActionSelectExecute(NULL);
		break;
	case PLAYING:
		ActionNewExecute(NULL);
		break;
	}
}
void __fastcall TFormMain::ActionNewExecute(TObject *Sender)
{
	MakeNew();
	SendMsg(ServerSocket,"START_NEW");
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::MakeTurn(int x, int y)
{
	if(ppp[y][x]) return;
	SetGameMoves(GameMoves+1);
	ppp[y][x]=MyFig;
	DrawCell(PaintBox1->Canvas,x,y);
	FindWinner(x,y);
	SetTurn(OPP_TURN);
	SendMsg(ServerSocket,AnsiString("TURN=")+x+","+y);
}

void __fastcall TFormMain::GetTurn(int x, int y)
{
	if(MyFig==1) ppp[y][x]=2; else ppp[y][x]=1;
	DrawCell(PaintBox1->Canvas,x,y);
	SetTurn(MY_TURN);
	FindWinner(x,y);
}

void __fastcall TFormMain::MakeNew()
{
	for(int i=0; i<20; i++)
		for(int j=0; j<20; j++)
		{
			ppp[i][j]=0;
			DrawCell(PaintBox1->Canvas,j,i);
		}
	SetGameMoves(0);
	SetGameTime(0);
	GameStatus=PLAY;
	Timer1->Enabled=false;
	PaintBox2->Refresh();
}


int idir[]={1,1,1,0};
int jdir[]={-1,0,1,1};
//int ccc[]={36,64,100,81,112,121,169};

void __fastcall TFormMain::FindWinner(int j, int i)
{
	int a,b,k,m,n,p;
	struct {
		int x,y;
	} save[6];
	p=ppp[i][j];
	i++; j++;
	for(n=1; n<=4; n++)
	{
		k=0;
		for(m=-4; m<=4; m++)
		{
			a=i+m*idir[n-1];
			b=j+m*jdir[n-1];
			if(a>=1 && a<=20 && b>=1 && b<=20 ) {
				if(ppp[a-1][b-1]==p) {
					k=k+1;
					save[k].x=b-1; save[k].y=a-1;
					if(k>=5) {
						for(k=1; k<=5; k++) {
							ppp[save[k].y][save[k].x]+=3;
							DrawCell(PaintBox1->Canvas,save[k].x,save[k].y);
						}
						EndGame(p);
						return;
					}
				}else k=0;
			}
		}
	}
}

void __fastcall TFormMain::EndGame(int who)
{
	if(who==MyFig) {
		GameStatus=WIN;
		PaintBox2->Refresh();
	}else{
		GameStatus=LOST;
		PaintBox2->Refresh();
	}
}

void __fastcall TFormMain::About1Click(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormShow(TObject *Sender)
{
	ImageList1->Draw(PaintBox2->Canvas,0,0,SMILE_OK,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	ClientWidth=16*20+2;
	ClientHeight=16*20+2+32;
	for(int i=0; i<9; i++) {
		bmp[i]=new Graphics::TBitmap();
		ImgPanels->GetBitmap(i,bmp[i]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	for(int i=0; i<9; i++) delete bmp[i];
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ApplicationEvents1Exception(TObject *Sender,
                                                       Exception *E)
{
	if(E->Message.Pos("(10043)"))
		ShowMessage("Протокол TCP/IP не поддерживается на этом компьютере!");
	else if(E->Message.Pos("(1009"))
		ShowMessage("Этот компьютер не поддерживает работу в сети!");
	else if(E->Message.Pos("(11001")) {
		ClientSocket1->Open();
	}else
		ShowMessage(AnsiString(E->ClassName())+ E->Message);
}
//---------------------------------------------------------------------------

