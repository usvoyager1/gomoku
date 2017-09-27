//---------------------------------------------------------------------------

#ifndef UnitConnectingH
#define UnitConnectingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormConnecting : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TAnimate *Animate1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormConnecting(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormConnecting *FormConnecting;
//---------------------------------------------------------------------------
#endif
