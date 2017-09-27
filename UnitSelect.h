//---------------------------------------------------------------------------

#ifndef UnitSelectH
#define UnitSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSelect : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TButton *Button1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TListView *PlayersList;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall PlayersListCustomDrawItem(TCustomListView *Sender,
          TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
        void __fastcall PlayersListDblClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSelect *FormSelect;
//---------------------------------------------------------------------------
#endif
