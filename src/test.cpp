#include "Huffman.hpp"
using namespace std;

int main() {
	setlocale(LC_ALL, "Turkish");

	Huffman *huffman = new Huffman("Deneme.txt");
	while(true)
	{
		system("cls");
		int secim;
		cout << "1- Dosyayý Sýkýþtýr " <<endl;
		cout << "2- Sýkýþtýrýlmýþ Dosyayý Ekrana Yaz" << endl;
		cout << "3- Cýkýþ" << endl;
		cin >> secim;
		
			if (secim == 1)
			{
				huffman->Kodla();
				cout << *huffman;
				cout << "Tablo Olusturuldu. Lütfen bekleyiniz!" << endl;
				huffman->DatYaz();
				cout << "Sýkýþtýrma islemi Tamamlandi." << endl;
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