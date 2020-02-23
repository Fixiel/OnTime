//---------------------------------------------------------------------------

#include <vcl.h>
#include <mmsystem.h>
#pragma resource "Resources\\resMusic.res"
#pragma hdrstop

#include "USettings.h"
#include "UMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFMessage *FMessage;
//---------------------------------------------------------------------------
__fastcall TFMessage::TFMessage(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFMessage::FormCreate(TObject *Sender)
{
Timer1->Interval=FSettings->UpDown1->Position*FSettings->valTime;
Timer2->Interval=FSettings->UpDown2->Position*FSettings->valTime;
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFMessage::BGoodClick(TObject *Sender)
{
FMessage->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TFMessage::BAfterClick(TObject *Sender)
{
if (FSettings->isFlag2==true)
{
  FSettings->isFlag2=false;
  Timer2->Interval=FSettings->UpDown2->Position*FSettings->valTime;
}
Timer2->Enabled=true;
BAfter->Enabled=false;
FMessage->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFMessage::Timer1Timer(TObject *Sender)
{
if (FSettings->isFlag1==true)
{
  FSettings->isFlag1=false;
  Timer1->Interval=FSettings->UpDown1->Position*FSettings->valTime;
}
if (FSettings->NInf->Checked==false)
{
  Timer1->Enabled=false;
  FSettings->NStop->Checked=true;
  FSettings->isCheck=true;
  FSettings->isInf=true;
}
FSettings->One=GetTickCount();
Timer2->Enabled=false;
BAfter->Enabled=true;
GetReport();
}
//---------------------------------------------------------------------------

void __fastcall TFMessage::Timer2Timer(TObject *Sender)
{
Timer2->Enabled=false;
GetReport();
}
//---------------------------------------------------------------------------

void TFMessage::GetReport()
{
static AnsiString arrWords[5]={"Прошло много времени, отдохни!", "Кофе само себя не заварит!",
                  "Утро вечера мудренее!", "На голодный желудок ничего не сделаешь!",
                  "Сейчас самое время для отдыха!"};
static int k;
Randomize();
k=rand()%5;
switch (k)
{
  case 0: BGood->Caption="Хорошо";
  break;
  case 1: BGood->Caption="Согласен";
  break;
  case 2: BGood->Caption="Понятно";
  break;
  case 3: BGood->Caption="Согласен";
  break;
  case 4: BGood->Caption="Хорошо";
  break;
}
Label1->Caption=arrWords[k];
FMessage->Show();
FSettings->TrayIcon->Restore();
FMessage->BringToFront();
if (FSettings->NSound->Checked==true)
  PlaySound("playNotify", 0, SND_RESOURCE | SND_ASYNC);
}
//---------------------------------------------------------------------------

void __fastcall TFMessage::ApplicationEventsDeactivate(TObject *Sender)
{
if (FSettings->NShow->Checked==true)
  SetForegroundWindow(Application->Handle);
}
//---------------------------------------------------------------------------
