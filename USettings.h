//---------------------------------------------------------------------------

#ifndef USettingsH
#define USettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <Menus.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <Registry.hpp>
//---------------------------------------------------------------------------
class TFSettings : public TForm
{
__published:	// IDE-managed Components
        TTrayIcon *TrayIcon;
        TPopupMenu *PopupMenu;
        TMenuItem *NShow;
        TMenuItem *NSound;
        TMenuItem *NLine3;
        TMenuItem *NSettings;
        TMenuItem *NLine4;
        TMenuItem *NExit;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TButton *BOk;
        TButton *BCancel;
        TImageList *ImageList;
        TLabel *Label2;
        TEdit *Edit1;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        TEdit *Edit2;
        TMenuItem *NInf;
        TMenuItem *NStart;
        TMenuItem *NStop;
        TMenuItem *NLoad;
        TMenuItem *NLine2;
        TMenuItem *NLine1;
        TMenuItem *NReset;
        void __fastcall NExitClick(TObject *Sender);
        void __fastcall NSettingsClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall NShowClick(TObject *Sender);
        void __fastcall NSoundClick(TObject *Sender);
        void __fastcall BOkClick(TObject *Sender);
        void __fastcall BCancelClick(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall NInfClick(TObject *Sender);
        void __fastcall NLoadClick(TObject *Sender);
        void __fastcall NStartClick(TObject *Sender);
        void __fastcall NStopClick(TObject *Sender);
        void __fastcall NResetClick(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
void TFSettings::GetStyle();
void TFSettings::GetReg();
TRegistry* Reg;
int One, Two, valGeneral, valHelp, valTime;
bool isFlag1, isFlag2, isCan, isCheck, isShow, isInf;

        __fastcall TFSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFSettings *FSettings;
//---------------------------------------------------------------------------
#endif
