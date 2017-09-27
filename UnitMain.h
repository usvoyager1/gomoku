//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <NMMSG.hpp>
#include <Psock.hpp>
#include <ScktComp.hpp>
#include <NMSTRM.hpp>
#include <ActnList.hpp>
#include <AppEvnts.hpp>
#include <NMUDP.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImgPanels;
        TPanel *Panel1;
        TPaintBox *PaintBox1;
        TPanel *Panel2;
        TImageList *ImageList1;
        TMainMenu *MainMenu1;
        TMenuItem *Game1;
        TMenuItem *Help1;
        TMenuItem *About1;
        TMenuItem *Exit1;
        TMenuItem *New1;
        TMenuItem *N1;
        TClientSocket *ClientSocket1;
        TMenuItem *N2;
        TMenuItem *Connecttoserver1;
        TMenuItem *Playwith1;
        TActionList *ActionList1;
        TAction *ActionNew;
        TAction *ActionConnect;
        TAction *ActionDisconnect;
        TAction *ActionSelect;
        TAction *ActionExit;
        TMenuItem *N3;
        TMenuItem *N4;
        TPaintBox *PaintBox2;
        TTimer *Timer1;
        TImageList *ImgClocks;
        TPanel *Panel3;
        TPaintBox *PaintBox3;
        TPanel *Panel4;
        TPaintBox *PaintBox4;
        TApplicationEvents *ApplicationEvents1;
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ActionConnectExecute(TObject *Sender);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket1Lookup(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ActionDisconnectExecute(TObject *Sender);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ActionExitExecute(TObject *Sender);
        void __fastcall ActionSelectExecute(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall PaintBox2Paint(TObject *Sender);
        void __fastcall PaintBox3Paint(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall PaintBox4Paint(TObject *Sender);
        void __fastcall ActionNewExecute(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ApplicationEvents1Exception(TObject *Sender,
          Exception *E);
private:	// User declarations
public:
        int myID;		// User declarations
        int msx;
        int msy;
        bool msb;
        TCustomWinSocket* ServerSocket;
        int OpponentID;
        AnsiString OpponentName;		// User declarations
        __fastcall TFormMain(TComponent* Owner);
        void __fastcall DrawCell(TCanvas * c, int x, int y);
        void __fastcall Play(int id);
        void __fastcall CancelPlay();
        void __fastcall MakeTurn(int x, int y);
        void __fastcall ClickNew();
        void __fastcall GetTurn(int x, int y);
        void __fastcall MakeNew();
        void __fastcall FindWinner(int x, int y);
        void __fastcall EndGame(int who);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
