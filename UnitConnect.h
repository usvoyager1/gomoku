//---------------------------------------------------------------------------

#ifndef UnitConnectH
#define UnitConnectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormConnect : public TForm
{
__published:	// IDE-managed Components
        TButton *Button2;
        TButton *Button3;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TEdit *Edit1;
        TEdit *Edit2;
        TPopupMenu *PopupMenu1;
        TMenuItem *localhost1;
        TPanel *Panel1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Panel1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall PopupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormConnect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormConnect *FormConnect;
//---------------------------------------------------------------------------
#endif
