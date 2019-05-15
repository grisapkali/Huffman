#include "Huffman.hpp"
using namespace std;

int main() {
	setlocale(LC_ALL, "Turkish");

	Huffman *huffman = new Huffman("Deneme.txt");
	while(true)
	{
		system("cls");
		int secim;
		cout << "1- Dosyay� S�k��t�r " <<endl;
		cout << "2- S�k��t�r�lm�� Dosyay� Ekrana Yaz" << endl;
		cout << "3- C�k��" << endl;
		cin >> secim;
		
			if (secim == 1)
			{
				huffman->Kodla();
				cout << *huffman;
				cout << "Tablo Olusturuldu. L�tfen bekleyiniz!" << endl;
				huffman->DatYaz();
				cout << "S�k��t�rma islemi Tamamlandi." << endl;
				system("pause");
			}

			else if (secim == 2)
			{
				system("cls");
				huffman->DatOkuyucu();
				system("pause");
			}
			else if (secim == 3)
			{
				break;
			}
			else
			{
				cout << "Lutfen 1 yada 2 yi seciniz.";
				system("pause");
			}
	}

	delete huffman;
	return 0;
}