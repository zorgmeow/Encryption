//---------------------------------------------------------------------------

#ifndef FormH
#define FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include "cgauges.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "Control.h"
//---------------------------------------------------------------------------
class TMForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *b_lock;
	TBitBtn *b_unlock;
	TOpenDialog *OpenD;
	TBitBtn *b_open;
	TBitBtn *b_help;
	TLabel *l_pass;
	TEdit *password;
	TEdit *fpass;
	TImage *y;
	TImage *n;
	void __fastcall b_helpClick(TObject *Sender);
	void __fastcall b_openClick(TObject *Sender);
	void __fastcall b_lockClick(TObject *Sender);
	void __fastcall b_unlockClick(TObject *Sender);
	void __fastcall passwordChange(TObject *Sender);

private:	// User declarations
public:
	  AnsiString filen;
	  void fCoDec(AnsiString Pt1, AnsiString Pt2, bool enco);
	  inline int cmppass();
// User declarations
	__fastcall TMForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMForm *MForm;
//---------------------------------------------------------------------------
#endif
