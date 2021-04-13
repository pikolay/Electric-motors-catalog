//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <math.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
typedef struct
{
        char type[20];
        char model[20];
        short I;
        short U;
        short N;
        short kpd;

} ELECTRO;

ELECTRO base[500];
int D=0;
int Z=0;
//---------------------------------------------------------------------------
__fastcall TForm1::Function()
{
        Tabl->Items->Clear();
for (int i = 0; i < D; i++)
        {
                char buf[150];
                TListItem * ListItem = Tabl->Items->Add();
                ListItem->Caption = i+1;
                ListItem->SubItems->Add(base[i].type);
                ListItem->SubItems->Add(base[i].model);
                ListItem->SubItems->Add(base[i].I);
                ListItem->SubItems->Add(base[i].U);
                ListItem->SubItems->Add(base[i].N);
                ListItem->SubItems->Add(base[i].kpd);

        }
}
//----------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if(!OpenDialog1->Execute()) return;
        FILE* sv = fopen("inf.txt", "r");
        D = 0;
        while(!feof(sv))
        {
                memset(&base[D], 0, sizeof(ELECTRO));
                fscanf(sv, " %20s %20s %d %d %d %d\n ",
                &base[D].type, &base[D].model, &base[D].I,
                &base[D].U, &base[D].N, &base[D].kpd);
                D++;
        }
fclose(sv);
TForm1::Function();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
if(!SaveDialog1->Execute()) return;
        FILE* cl = fopen(SaveDialog1->FileName.c_str(), "w");
        for(int i = 0; i <D; i++)
                {
                        fprintf(cl, " %20s %20s %d %d %d %d\n",
                         base[i].type,base[i].model,base[i].I,
                         base[i].U,base[i].N,base[i].kpd);

                }
        fclose(cl);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Tabl->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
int index;
 new_engine->Visible = true;
        if(Tabl->Selected)

       {
            index = Tabl->Selected->Index;

            Z=index;
             
            Edit1->Text=base[Z].type;
            Edit2->Text=base[Z].model;
            Edit3->Text=base[Z].I;
            Edit4->Text=base[Z].U ;
            Edit5->Text=base[Z].N;
            Edit6->Text=base[Z].kpd;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{
new_engine->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
 new_engine->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{

    sscanf( Edit1->Text.c_str(),"%20s",&base[D].type);
    sscanf( Edit2->Text.c_str(),"%20s",&base[D].model );
    try{
    if (sscanf( Edit3->Text.c_str(),"%d",&base[D].I) == 0) throw 1;
    if (sscanf( Edit4->Text.c_str(),"%d",&base[D].U) == 0) throw 1;
    if (sscanf( Edit5->Text.c_str(),"%d",&base[D].N) == 0) throw 1;
    if (sscanf( Edit6->Text.c_str(),"%d",&base[D].kpd) == 0) throw 1;
        }
                   catch(int i)
        {
            ShowMessage("Введены неверные данные в поля");
            return;
        }

    ++D;

    Function();
    Edit1->Text = "";
    Edit2->Text  = "";
    Edit3->Text = "";
    Edit4->Text = "";
    Edit5->Text = "";
    Edit6->Text = "";

    new_engine->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
    sscanf( Edit1->Text.c_str(),"%20s",&base[Z].type);
    sscanf( Edit2->Text.c_str(),"%20s",&base[Z].model );
   try{
    if (sscanf( Edit3->Text.c_str(),"%d",&base[Z].I) == 0) throw 1;
    if (sscanf( Edit4->Text.c_str(),"%d",&base[Z].U) == 0) throw 1;
    if (sscanf( Edit5->Text.c_str(),"%d",&base[Z].N) == 0) throw 1;
    if (sscanf( Edit6->Text.c_str(),"%d",&base[Z].kpd) == 0) throw 1;
        }
              catch(int i)
        {
            ShowMessage("Введены неверные данные в поля ");
            return;
        }
    ++Z;

    Function();
    Edit1->Text = "";
    Edit2->Text  = "";
    Edit3->Text = "";
    Edit4->Text = "";
    Edit5->Text = "";
    Edit6->Text = "";

    new_engine->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
if (MessageDlg("Вы уверены что хотите выйти?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes)
            {
                        Close();
            }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button4Click(TObject *Sender)
{
  int index;

        if(!Tabl->Selected)
        { return;}
        index = Tabl->Selected->Index;
        char buf[200];
        sprintf(buf, "Удалить строку под номером %d ?", index+1);

        int say = MessageDlg(buf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0);

        if(say != mrYes)
        {return;}
        for(int i = Tabl->Selected->Index; i < D-1; i++)

        {
                base[i]= base[i+1];
        }

        D--;

       Function();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
int kp=0;
        int KPD;

        int h=0;
           for(int i=0; i<D ;i++)

                {
                        h++;
                        kp+=base[i].kpd;
                }
       KPD = kp/h;
        Edit7->Text  = KPD;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
 int max=0;

        int t=0;

                for (int i=0; i<=D; i++)
                {

                          if(base[i].N>max)
                           max=base[i].N;
                            t=max;
        }

    Edit9->Text  = t;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
int index;
int U=0;
int I=0;
int P=0;

        index = Tabl->Selected->Index;
        char buf[200];
        sprintf(buf, "Выбрать строку под номером %d?", index+1);

        int say = MessageDlg(buf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0);

        if(say != mrYes)
        {return;}
        for(int i = Tabl->Selected->Index; i < D; i++)

        {
                   I=base[i].I;
                    U=base[i].U;
                    P=U*I;
        }

       Function();
       Edit8->Text  = P;
       }
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
Series1->Clear();
        int kp=0;
        for(int i=0; i<=D ;i++)
        {
                kp=base[i].kpd;
        Series1->AddXY(i,kp);
        }
}
//---------------------------------------------------------------------------
