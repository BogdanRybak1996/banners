// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Banners.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::SelectButton3Click(TObject *Sender) {
	UnicodeString way = "c:\\\\"; // ¬казуЇмо папку, де будемо створювати файл
	if (SelectDirectory("¬каж≥ть шл€х до папки", "", way))
		Edit1->Text = way;
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender) {
	Form2->Close();
	Form1->Edit2->Text = (Edit1->Text + "\\\\" + Edit2->Text + ".html");
	Form1->OpenDialog2->FileName = (Edit1->Text + "\\\\" + Edit2->Text + ".html");
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender) {
	Form2->Close();
}
// ---------------------------------------------------------------------------
