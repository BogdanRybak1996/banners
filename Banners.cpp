// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Banners.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Unit2.h"
#include <vector>
#include <string>
#include <fstream>

void copy_banners(ifstream &, ifstream &, ofstream &);
// void put_banners(fstream &,fstream &,fstream &);
std::string startsave(ifstream &);
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::SellectButton1Click(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		Edit1->Text = OpenDialog1->FileName; // �������� ���� �� ����� � �����
	}

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::SelectButton2Click(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		Edit2->Text = OpenDialog1->FileName;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CreateButtonClick(TObject *Sender) {
	Form2->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender) {
	Form1->Close();
	Form2->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender) {
	if (OpenDialog3->Execute())
		Edit3->Text = OpenDialog3->FileName;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender) // ����� �� ����� �� default
{
	char buff;
	OpenDialog1->FileName = ExtractFilePath(Application->ExeName) +
	  "input.html";
	Edit1->Text = OpenDialog1->FileName;
	OpenDialog2->FileName = ExtractFilePath(Application->ExeName) +
	  "output.html";
	Edit2->Text = OpenDialog2->FileName;
	OpenDialog3->FileName = ExtractFilePath(Application->ExeName) +
	  "filters.txt";
	Edit3->Text = OpenDialog3->FileName;
	StatusListBox->Items->Add
	  ("������ ����� �� ����� �� �������� \"������\"");
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
	/* FILE *input;
	 FILE *output;
	 FILE *filters;
	 */
	std::ifstream input;
	std::ofstream inputOut;
	std::ifstream filters;
	std::ofstream output;
	bool health = 1;
	AnsiString inputfilename = OpenDialog1->FileName;

	input.open(inputfilename.c_str(), ios::nocreate);
	// ³�������� ������� ����
	inputOut.open(inputfilename.c_str(), ios::nocreate);

	if (!input.is_open()) {
		StatusListBox->Items->Add("���� " + inputfilename +
		  " ������� �� �������");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("���� " + inputfilename + " �������");
	}

	AnsiString outputfilename = OpenDialog2->FileName;

	output.open(outputfilename.c_str()); // ³�������� �������� ����

	if (!output.is_open()) {
		StatusListBox->Items->Add("���� " + outputfilename +
		  " ������� �� �������");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("���� " + outputfilename + " �������");
	}

	AnsiString filtersfilename = OpenDialog3->FileName;

	filters.open(filtersfilename.c_str(), ios::nocreate);
	// ³�������� ���� � ���������

	if (!filters.is_open()) {
		StatusListBox->Items->Add("���� " + filtersfilename +
		  " ������� �� �������");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("���� " + filtersfilename + " �������");
	}

	if (health) {
		if (!(CheckBox1->Checked))
			copy_banners(input, filters, output);
	}
	input.close();
	inputOut.close();
	output.close();
	filters.close();
}

// ---------------------------------------------------------------------------
void copy_banners(ifstream& input, ifstream& filters, ofstream &output)
{ // �������, ��� ����� ������ (��� ��������)
	std::vector<std::string>elements;
	char c = '\0';
	while (!input.eof()) { // ������� �����������, ������� "<"
		input.get(c);
		if (c == '<') // 60 - ��� ������� "<" � ASCII
			  elements.push_back(startsave(input));
	}
	for(int i=0;i<elements.size();i++){
		for(int j=0;j<elements[i].size();j++){
		  std::string link;
		  std::vector<std::string> links;		// �� ��������� �� ���������
		  int patty=0; 					//�����, ��� ���� ������� �����
		if(elements[i][j]=='"'){
			patty++;
		}
		if(patty%2!=0){
			link.push_back(elements[i][j]);
		}
		else{
			links.push_back(link);
			link.clear();
        }
	}
}
	}

std::string startsave(ifstream &input) { // �������, ��� �����'����� "<*>"
	std::string fragment;
	int temp1 = 1, temp2 = 0;
	char c;
	fragment.push_back('<');
	while (temp1 != temp2) {
		input.get(c);
		if(c=='\n')
			continue;
		fragment.push_back(c);
		if (c == '<')
			temp1++;
		if (c == '>')
			temp2++;
	}
	return fragment;
}
