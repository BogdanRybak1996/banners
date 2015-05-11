// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Banners.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Unit2.h"
#include "Unit3.h"
#include <vector>
#include <string>
#include <fstream>
#include <Masks.hpp>

void copy_banners(ifstream &, ifstream &, ofstream &);
void put_banners(ifstream &, ifstream &, ofstream &, ofstream &);
std::string startsave(ifstream &);
bool match_my(std::vector<std::string>, ifstream &);

struct links { // ��������������� � ������� "put_banners"

	int pos;
	int long_link;

	std::string link;
};

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
	if (OpenDialog2->Execute()) {
		Edit2->Text = OpenDialog2->FileName;
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
	Form3->Close();
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
	std::ifstream input;
	std::ofstream inputOut;
	std::ifstream filters;
	std::ofstream output;
	StatusListBox->Clear();
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
		if (!(Form3->CheckBox1->Checked)) {
			copy_banners(input, filters, output);
		}
		else {
			put_banners(input, filters, output, inputOut);
		}
	}
	input.close();
	inputOut.close();
	output.close();
	filters.close();
	StatusListBox->Items->Add("������ ���������");
}

// ---------------------------------------------------------------------------
void copy_banners(ifstream &input, ifstream &filters, ofstream &output)
{ // �������, ��� ����� ������ (��� ��������)
	std::vector<std::string>elements;
	char c = '\0';
	while (!input.eof()) { // ������� �����������, ������� "<"
		input.get(c);
		if (c == '<')
			elements.push_back(startsave(input));
	}
	for (int i = 0; i < elements.size(); i++) {
		int patty = 0; // �����, � ��� �����'��������� ������� �����
		std::string link;
		std::vector<std::string>links; // �� ��������� �� ���������
		for (int j = 0; j < elements[i].length(); j++) {
			if (elements[i][j] == '"') {
				patty++;
				continue;
			}
			if (patty % 2 != 0) {
				link.push_back(elements[i][j]);
			}
			else {
				if (link.empty()) // ���� ����� �� �����'�������
					  continue;
				links.push_back(link);
				link.clear();
			}
		}
		if (match_my(links, filters)) {
			output << elements[i];
			Form1->StatusListBox->Items->Add
			  ("������ ���������� � �������� ����");
			output << std::endl;
		}
	}
}

std::string startsave(ifstream &input) { // �������, ��� �����'����� "<*>"
	std::string fragment;
	if (Form3->CheckBox2->Checked) {
		int temp1 = 1, temp2 = 0;
		char c;
		fragment.push_back('<');
		while (temp1 != temp2) {
			input.get(c);
			if (c == '\n')
				continue;
			fragment.push_back(c);
			if (c == '<')
				temp1++;
			if (c == '>')
				temp2++;
			if (input.eof())
				break;
		}
	}
	else {
		std::string start;
		std::string end;
		char c;
		fragment.push_back('<');
		while (c != ' ' || c == '\n' || c == '\t') { // �������� ������� ����
			input.get(c);
			fragment.push_back(c);
			start.push_back(c);
			if (input.eof())
				break; // ���� ����� ��� � �� ������� - ��������
		}

		bool startend = 0;
		bool prevend = 0;
		while (start != (end + ' ')) {
			input.get(c);
			if (c == '\n')
				continue;
			fragment.push_back(c);
			if (c == '<') {
				prevend = 1;
			}
			if ((c == '/') && prevend) {
				startend = 1;
				continue;
			}
			if (c == '>')
			{ // ���� ����������� ��� �� ������� � ����������� - ������ �����
				startend = 0;
				end.clear();
			}
			if (startend) { // �������� ����������� ���
				end.push_back(c);
			}
			if (input.eof()) {
				break;
			}
		}
		fragment.push_back('>');
	}
	return fragment;
}

bool match_my(std::vector<std::string>links, ifstream &filters)
  // �������, ��� �������� �� ������� ���� � ���� ��������� � ������
{
	bool t = 0;
	for (int i = 0; i < links.size(); i++) {
		while (!filters.eof()) {
			std::string filter;
			filters >> filter;
			TMask *Mask = new TMask(filter.c_str());
			if (Mask->Matches(links[i].c_str()))
				t = 1;
			delete Mask;
		}
	}
	filters.clear();
	filters.seekg(0);
	// ����������� �� ������� ����� ��� ���� ������������ � ����������
	return t;
}

void __fastcall TForm1::Button4Click(TObject *Sender) {
	Form3->Show();
}

// ---------------------------------------------------------------------------
void put_banners(ifstream &input, ifstream &filters, ofstream &output,
  ofstream &inputOut) {
	std::vector<links>links_in_str; 		   // ��� ������ �������� ���� ���������
	links temp;
	copy_banners(input, filters, output); 	// ������� ������ � ����� ������
	std::string inputstr;
	while (!input.eof()) { 				// ��������� ����� ������ ����� � string
		inputstr.push_back(input.get());
	}
	bool save = 0;
	int patty = 0;
	temp.long_link = 0;
	for (int i = 0; i < inputstr.length(); i++) { 		// �������� �� ���������
		if (inputsrt[i] == '"' && patty % 2 == 0) {
			patty++;
			temp.pos = i;
			continue;
		}
		if (patty % 2 != 0 && inputsrt[i] != '"') {
			temp.link.push_back(inputstr[i]);
			temp.long_link++;
		}
		if (patty % 2 != 0 && inputsrt[i] == '"') {
			links_in_str.push_back(temp);
			temp.link.clear();
			temp.long_link = 0;
		}
	}

}
