//---------------------------------------------------------------------------

#include <vcl.h>
#include  <iostream>
#include  <fstream>
#include <sys\stat.h>
#pragma hdrstop
#include "Form.h"
#include "CryptONPCH1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
TMForm *MForm;
//---------------------------------------------------------------------------
__fastcall TMForm::TMForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TMForm::b_helpClick(TObject *Sender)
{
ShellExecuteA(NULL, "open", "http://sites.google.com/site/cryptoninf/home/info", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TMForm::b_openClick(TObject *Sender)
{
	if (OpenD->Execute()) {
filen = OpenD->FileName;
int file_name_l = filen.Length();//определяет длину имени файла(+путь)
//char *ex = new char[4];//хранит расширение файла
char ex[5];//хранит расширение файла
int k = 0;//первую букву расширения присваивает ex
for (int i = file_name_l - 3; i <= file_name_l; i++) {
ex[k] = filen[i];
k++;
}
l_pass->Enabled=true;
fpass->Enabled=true;
password->Enabled=true;
//блокирует возможность зашифровать уже зашифрованный файл
if((ex[0] == 'c'&&ex[1] == 'r'&&ex[2] == 'p'&&ex[3] == 't') || (ex[0] == 'C'&&ex[1] == 'R'&&ex[2] == 'P'&&ex[3] == 'T')) { //если выбран зашифрованный файл
//if(ex=="CRPT") {
b_lock->Enabled = false; //кнопка зашифровать недоступна
b_unlock->Enabled = true; //доступна кнопка расшифровать
}
else{ //если выбран другой файл
b_unlock->Enabled = false; //кнопка расшифровать недоступна
b_lock->Enabled = true; //кнопка зашифровать доступна
}
}
}
//---------------------------------------------------------------------------

void __fastcall TMForm::b_lockClick(TObject *Sender)
{
if (password->Text=="")
ShowMessage("Поле ключа не может быть пустым!");
else{
AnsiString filenew=filen+".crpt";
DeleteFile(filenew);
fCoDec(filen,filenew, true);
l_pass->Enabled=false;
fpass->Clear();
fpass->Enabled=false;
password->Clear();
password->Enabled=false;
b_lock->Enabled=false;
y->Visible=false;
n->Visible=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TMForm::b_unlockClick(TObject *Sender)
{
if (password->Text=="")
	ShowMessage("Поле ключа не может быть пустым!");
else{
AnsiString filenew=filen;
int index = filenew.Pos(".crpt");
if( index != 0 ) {
   filenew.Delete(index,5);	   //удаляем расширение шифрованного файла
}
DeleteFile(filenew);
fCoDec(filen,filenew, false);
l_pass->Enabled=false;
fpass->Clear();
fpass->Enabled=false;
password->Clear();
password->Enabled=false;
b_unlock->Enabled=false;
y->Visible=false;
n->Visible=false;
}
}
//---------------------------------------------------------------------------
 void TMForm::fCoDec(AnsiString Pt1, AnsiString Pt2, bool enco)
{
	if(cmppass()){
	const cmax = 524288000;//  максимальный размер файла - 500 мб
	AnsiString pass = password->Text;
    HCRYPTPROV  hProv ;              //  провайдер
	HCRYPTHASH  hash ;               //  хэш
    HCRYPTKEY   key ;                //  ключ
	UCHAR *bufC;                     //  буфер для обработки
	DWORD len;                       //  длина данных в файле
//    получаем контекст криптопровайдера
    CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
//    создаем хеш-объект
    CryptCreateHash(hProv, CALG_SHA, 0, 0, &hash);
//    хешируем пароль
	CryptHashData(hash, pass.c_str(), pass.Length(), 0);
//    создаем ключ на основании пароля для потокового шифра RC2
	CryptDeriveKey(hProv, CALG_RC2, hash, 0, &key);
//    уничтожаем хеш-объект
    CryptDestroyHash(hash);
//    открываем файлы
	 ifstream  fin(Pt1.c_str(),ios::in|ios::binary) ;
	 ofstream fout(Pt2.c_str(),ios::out|ios::binary) ;
//    выделяем место для буфера
    bufC = new UCHAR[cmax] ;  //  выделяем память
    fin.read(bufC,cmax) ;
	len=fin.gcount() ;
	if (enco){    //    шифруем данные
	//clock_t start = clock();
	   CryptEncrypt(key, 0, true, 0, bufC, &len, cmax);
	   ShowMessage("Файл "+Pt1+" успешно зашифрован! Зашифрованный файл имеет расширение .crpt");
	  // ShowMessage((clock() - start) / CLOCKS_PER_SEC);
	   }
	else{       //   расшифровываем данные
	   CryptDecrypt(key, 0, true, 0, bufC, &len );
	   ShowMessage("Файл "+Pt2+" успешно дешифрован!");
	}
	fout.write(bufC,len);
//    освобождаем контекст криптопровайдера
    CryptReleaseContext(hProv, 0);
    delete[] bufC;
    fin.close();
	fout.close();
	}
	}
//---------------------------------------------------------------------------
	int TMForm::cmppass(){
	if (fpass->Text==password->Text)
	return 1;
	else{
		ShowMessage("Введенные ключи не совпадают!");
		password->SetFocus();
		return 0;
	}
	}
void __fastcall TMForm::passwordChange(TObject *Sender)
{
if(fpass->Text!=password->Text){
	if(n->Visible==false){
		y->Visible=false;
		n->Visible=true;
	}
}else{
	if(y->Visible==false){
		n->Visible=false;
		y->Visible=true;
	}
}
}
//---------------------------------------------------------------------------


