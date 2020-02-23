//---------------------------------------------------------------------------

#ifndef UMessageH
#define UMessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFMessage : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TPanel *Panel1;
        TButton *BGood;
        TButton *BAfter;
        TTimer *Timer2;
        TTimer *Timer1;
        TApplicationEvents *ApplicationEvents;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BGoodClick(TObject *Sender);
        void __fastcall BAfterClick(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ApplicationEventsDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
void TFMessage::GetReport();
        __fastcall TFMessage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMessage *FMessage;
//---------------------------------------------------------------------------
#endif
