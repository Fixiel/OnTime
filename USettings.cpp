//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "USettings.h"
#include "UMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFSettings *FSettings;
//---------------------------------------------------------------------------
__fastcall TFSettings::TFSettings(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::FormCreate(TObject *Sender)
{
One=GetTickCount();
FSettings->Top=Screen->Height/2-FSettings->Height/2;
FSettings->Left=Screen->Width/2-FSettings->Width/2-340;
valTime=60000;
valGeneral=30;
valHelp=5;
isCan=false;
isShow=false;
isInf=false;
isCheck=false;
isFlag1=false;
isFlag2=false;

GetReg();
Reg->OpenKeyReadOnly("Software\\OnTime\\Settings");

  //General
if (Reg->ValueExists("General")==true)
  UpDown1->Position=Reg->ReadInteger("General");
else
  UpDown1->Position=valGeneral;

  //Help
if (Reg->ValueExists("Help")==true)
  UpDown2->Position=Reg->ReadInteger("Help");
else
  UpDown2->Position=valHelp;

  //Infinity
if (Reg->ValueExists("Infinity")==true)
  NInf->Checked=Reg->ReadBool("Infinity");
else
  NInf->Checked=true;

  //Show
if (Reg->ValueExists("Show")==true)
  NShow->Checked=Reg->ReadBool("Show");
else
  NShow->Checked=false;

  //Sound
if (Reg->ValueExists("Sound")==true)
  NSound->Checked=Reg->ReadBool("Sound");
else
  NSound->Checked=false;

  //Load
if (Reg->ValueExists("Load")==true)
  NLoad->Checked=Reg->ReadBool("Load");
else
  NLoad->Checked=false;

GetStyle();
Reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::FormPaint(TObject *Sender)
{
if (isShow==false)
{
  FSettings->Hide();
  isShow=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::FormClose(TObject *Sender, TCloseAction &Action)
{
if (isCan==true)
  Action=caFree;
else
{
  Action=caNone;
  FSettings->Hide();
  ShowWindow(FSettings->Handle, 0);
}
}
//---------------------------------------------------------------------------
//Трей-----------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFSettings::NStartClick(TObject *Sender)
{
if (isCheck==true)
{
  FMessage->Timer1->Enabled=true;
  NStart->Checked=true;
  isCheck=false;
  isInf=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NStopClick(TObject *Sender)
{
if (isCheck==false)
{
  Two=GetTickCount();
  FMessage->Timer1->Enabled=false;
  FMessage->Timer1->Interval-=Two-One;
  NStop->Checked=true;
  isFlag1=true;
  isCheck=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NResetClick(TObject *Sender)
{
isFlag1=true;
isFlag2=true;
UpDown1->Position=valGeneral;
UpDown2->Position=valHelp;
NInf->Checked=true;
NShow->Checked=false;
NSound->Checked=false;
NLoad->Checked=false;
if (isInf==true)
  FMessage->Timer1->Interval=UpDown1->Position*valTime;
GetStyle();
GetReg();
Reg->DeleteKey("Software\\OnTime");
Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
Reg->DeleteValue("OnTime");
Reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NInfClick(TObject *Sender)
{
GetReg();
Reg->OpenKey("Software\\OnTime\\Settings", true);
Reg->WriteBool("Infinity", NInf->Checked);
Reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NShowClick(TObject *Sender)
{
GetStyle();     
GetReg();
Reg->OpenKey("Software\\OnTime\\Settings", true);
Reg->WriteBool("Show", NShow->Checked);
Reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NSoundClick(TObject *Sender)
{
GetReg();
Reg->OpenKey("Software\\OnTime\\Settings", true);
Reg->WriteBool("Sound", NSound->Checked);
Reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NLoadClick(TObject *Sender)
{
GetReg();
Reg->OpenKey("Software\\OnTime\\Settings", true);
Reg->WriteBool("Load", NLoad->Checked);
Reg->CloseKey();
if (NLoad->Checked==true)
{
  GetReg();
  Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);
  Reg->WriteString("OnTime", Application->ExeName);
  Reg->CloseKey();
}
else
{
  GetReg();
  Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
  Reg->DeleteValue("OnTime");
  Reg->CloseKey();
}
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NSettingsClick(TObject *Sender)
{
FSettings->Show();
FSettings->TrayIcon->Restore();
FSettings->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::NExitClick(TObject *Sender)
{
isCan=true;
FSettings->Close();
}
//---------------------------------------------------------------------------
//Форма----------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFSettings::Edit1KeyPress(TObject *Sender, char &Key)
{
if (Key>='0' && Key<='9' || Key==8)
  return;
Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::BOkClick(TObject *Sender)
{
isFlag1=true;
isFlag2=true;
if (Edit1->Text.ToInt()>UpDown1->Max || Edit2->Text.ToInt()>UpDown2->Max)
{
  Edit1->Text=UpDown1->Position;
  Edit2->Text=UpDown2->Position;
}
if (isInf==true)
  FMessage->Timer1->Interval=UpDown1->Position*valTime;
GetReg();
Reg->OpenKey("Software\\OnTime\\Settings", true);
Reg->WriteInteger("General", UpDown1->Position);
Reg->WriteInteger("Help", UpDown2->Position);
Reg->CloseKey();
FSettings->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::BCancelClick(TObject *Sender)
{
FSettings->Hide();
}
//---------------------------------------------------------------------------

void TFSettings::GetReg()
{
Reg=new TRegistry;
Reg->RootKey=HKEY_CURRENT_USER;
}
//---------------------------------------------------------------------------

void TFSettings::GetStyle()
{
if (NShow->Checked==true)
  FSettings->FormStyle=fsStayOnTop;
else
  FSettings->FormStyle=fsNormal;
}
//---------------------------------------------------------------------------

