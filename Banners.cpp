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

struct links { // Використовується в функції "put_banners"

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
		Edit1->Text = OpenDialog1->FileName; // Записуємо шлях до файлу у рядку
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

void __fastcall TForm1::FormShow(TObject *Sender) // Шляши до файлів по default
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
	  ("Вкажіть шляхи до файлів та натисніть \"Почати\"");
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
	// Відкриваємо вхідний файл
	inputOut.open(inputfilename.c_str(), ios::nocreate);

	if (!input.is_open()) {
		StatusListBox->Items->Add("Файл " + inputfilename +
		  " відкрити не вдалося");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("Файл " + inputfilename + " відкрито");
	}

	AnsiString outputfilename = OpenDialog2->FileName;

	output.open(outputfilename.c_str()); // Відкриваємо вихідний файл

	if (!output.is_open()) {
		StatusListBox->Items->Add("Файл " + outputfilename +
		  " відкрити не вдалося");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("Файл " + outputfilename + " відкрито");
	}

	AnsiString filtersfilename = OpenDialog3->FileName;

	filters.open(filtersfilename.c_str(), ios::nocreate);
	// Відкриваємо файл з фільтрами

	if (!filters.is_open()) {
		StatusListBox->Items->Add("Файл " + filtersfilename +
		  " відкрити не вдалося");
		health = 0;
	}
	else {
		StatusListBox->Items->Add("Файл " + filtersfilename + " відкрито");
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
	StatusListBox->Items->Add("Роботу завершено");
}

// ---------------------------------------------------------------------------
void copy_banners(ifstream &input, ifstream &filters, ofstream &output)
{ // Функція, яка копіює банери (без вирізання)
	std::vector<std::string>elements;
	char c = '\0';
	while (!input.eof()) { // Зчитуємо посимвольно, шукаючи "<"
		input.get(c);
		if (c == '<')
			elements.push_back(startsave(input));
	}
	for (int i = 0; i < elements.size(); i++) {
		int patty = 0; // Змінна, в якій запам'ятовується кількість лапок
		std::string link;
		std::vector<std::string>links; // Всі посилання із фрагменту
		for (int j = 0; j < elements[i].length(); j++) {
			if (elements[i][j] == '"') {
				patty++;
				continue;
			}
			if (patty % 2 != 0) {
				link.push_back(elements[i][j]);
			}
			else {
				if (link.empty()) // Пусті рядки не запам'ятовуємо
					  continue;
				links.push_back(link);
				link.clear();
			}
		}
		if (match_my(links, filters)) {
			output << elements[i];
			Form1->StatusListBox->Items->Add
			  ("Баннер перенесено в вихідний файл");
			output << std::endl;
		}
	}
}

std::string startsave(ifstream &input) { // Функція, яка запам'ятовує "<*>"
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
		while (c != ' ' || c == '\n' || c == '\t') { // Записуємо початок тега
			input.get(c);
			fragment.push_back(c);
			start.push_back(c);
			if (input.eof())
				break; // Якщо пробіл так і не знайшли - виходимо
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
			{ // Якщо закриваючий тег не співпадає з відкриваючим - шукаємо новий
				startend = 0;
				end.clear();
			}
			if (startend) { // Записуємо закриваючий тег
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
  // Функція, яка перевіряє чи співпадає хоча б одне посилання з маскою
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
	// Повертаємося на початок файлу для його використання в подальшому
	return t;
}

void __fastcall TForm1::Button4Click(TObject *Sender) {
	Form3->Show();
}

// ---------------------------------------------------------------------------
void put_banners(ifstream &input, ifstream &filters, ofstream &output,
  ofstream &inputOut) {
	std::vector<links>links_in_str; 		   // Тут будемо зберігати наші посилання
	links temp;
	copy_banners(input, filters, output); 	// Копіюємо банери в новий файлик
	std::string inputstr;
	while (!input.eof()) { 				// Вигружаємо вмість всього файлу в string
		inputstr.push_back(input.get());
	}
	bool save = 0;
	int patty = 0;
	temp.long_link = 0;
	for (int i = 0; i < inputstr.length(); i++) { 		// Записуємо всі посилання
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
