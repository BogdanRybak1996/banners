//---------------------------------------------------------------------------

#ifndef BannersH
#define BannersH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label1;
	TButton *SellectButton1;
	TOpenDialog *OpenDialog1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *SelectButton2;
	TButton *CreateButton;
	TOpenDialog *OpenDialog2;
	TButton *Button2;
	TLabel *Label3;
	TEdit *Edit3;
	TButton *Button3;
	TOpenDialog *OpenDialog3;
	TListBox *StatusListBox;
	TCheckBox *CheckBox1;
	void __fastcall SellectButton1Click(TObject *Sender);
	void __fastcall SelectButton2Click(TObject *Sender);
	void __fastcall CreateButtonClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
