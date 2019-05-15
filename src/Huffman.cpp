#include "Huffman.hpp"
#include<string>
#include<cstring>
#include<bitset>
Huffman::Huffman(string dosyaYolu) {
	harfler = 256;
	girdi = "";
	DosyaOku(dosyaYolu);
	kok = NULL;
}
void Huffman::DosyaOku(string dosyaYolu)
{
	string satir;
	ifstream dosya(dosyaYolu);
	if (dosya.is_open())
	{
		while (getline(dosya, satir))
		{
			girdi += satir;
			girdi += '\n';
		}
		dosya.close();
	}
	else return;
}
void Huffman::Kodla() {

	//char *karakterler = new char[girdi.size() - 1];
	char karakterler[girdi.size() - 1];
	strcpy(karakterler, girdi.c_str());

	//Frekanslarý say
	//	int *frek = new int[harfler];
	int frek[harfler];
	// frekanslarý sýfýrla
	for (int i = 0; i<harfler; i++)frek[i] = 0;

	for (int i = 0; i < girdi.size() - 1; i++)
		frek[karakterler[i]]++;

	// Huffman aðacýný oluþtur
	kok = AgacOlustur(frek);

	// 01 kodlar oluþturuluyor
	KodOlustur(kok, "");

}
void Huffman::BinaryCevir()						 //okuduðu karakterleri tablo ile kaþýlaþtýrýp bit karþýlýðýný string olarak hafýzada tutar.
{

	fstream dosya;
	char karakter; string bit;
	for (int i = 0; i < girdi.length(); i++)
	{
		dosya.open("tablo.txt", ios::in);
		if (dosya.is_open())
		{
			while (dosya >> karakter >> bit)
			{
				if (karakter == '@') 
				{
					if (girdi[i] == ' ')
					{
						binaryDat += bit;
						break;
					}
				}
				else if (karakter == '>')
				{
					if (girdi[i] == '\n')
					{
						binaryDat += bit;
						break;
					}
				}
				else if (girdi[i] == karakter)
				{
					binaryDat += bit;
					break;
				}
			}
		}
		dosya.close();
	}

}
void Huffman::DatYaz()	//binaryCevir fonksiyonunda deðiþkene atadýðý binary kodunu dat dosyasýna binary olarak yazan fonskiyon.
{
	BinaryCevir();
	string siradaki;
	int uzunluk = binaryDat.length();

	//eklenecek 0 sayisi bulunuyor
	int kalan = 8 - binaryDat.length() % 8;
	//0 lar ekleniyor
	for (int i = 0; i < kalan; i++)
	{
		binaryDat += '0';
	}
	//her 8 bit bulunup dosyaya yazilacak
	int tursayi = binaryDat.length() / 8;
	for (int i = 0; i < tursayi; i++)
	{
		//siradaki 8 bit string alýnýyor.
		siradaki = binaryDat.substr(i * 8, 8);
		//bitset e cevriliyor.
		bitset<8> bayt(siradaki);
		
		//bitsette tutulaný degiskene atiyor. ardindan dosyaya yazilabilir.
		unsigned char deneme = bayt.to_ulong();
	
		fstream file;
		file.open("Bit.dat", fstream::binary | fstream::app);

		if (file.is_open() == true)
		{
			file << deneme;
		}

		file.close();
	}


}

void Huffman::DatOkuyucu() //dat dosyasýndan okuyup okuduðu verileri bitset e ceviren ve ardýndan bitOkuyucu fonksiyonu ile ekrana yazdýran fonksiyon
{
	string dat_bit = "";
	char krk;
	ifstream file;

	file.open("Bit.dat", fstream::binary | fstream::out);	
	if (!file)
		cout << "File Not Found." << endl;
	else
	{
		file.seekg(0);	
		while (file >> krk)
		{
			bitset<8> son(krk);
			dat_bit += son.to_string();

		}

	}
	file.close();


	cout << bitOkuyucu(dat_bit);

}
string Huffman::bitOkuyucu(string baytlar) //parametre olarak girilen bitleri tutan deðiþkenin içerisindeki bitleri tablo ile karþýlaþtýrýp karaktere ceviren ve metine ekleyen fonksiyon. 
{
	string metin = "";
	string gecici = "";
	fstream file;
	char krk; string bitler;
	for (int i = 0; i < baytlar.length(); i++)
	{
		gecici += baytlar[i];
		file.open("tablo.txt", ios::in);
		if (file.is_open())
		{
			while (file >> krk >> bitler)
			{
				if (krk == '@')
				{
					if (gecici == bitler)
					{
						metin += " ";
						gecici = "";
						break;
					}
				}
				else if (krk == '>')
				{
					if (gecici == bitler)
					{
						metin += '\n';
						gecici = "";
						break;
					}
				}
				else if (gecici == bitler)
				{
					metin += krk;
					gecici = "";
					break;
				}
			}
		}
		file.close();
	}
	return metin;


}


Dugum* Huffman::AgacOlustur(int frek[]) {
	// dosyada var olan karakterler için düðüm oluþtur.
	//Dugum** dugumler = new Dugum*[harfler];
	Dugum *dugumler[harfler];
	for (int i = 0; i<harfler; i++) {
		if (frek[i]>0)
		{
			dugumler[i] = new Dugum((char)i, frek[i]);
		}
		else {
			dugumler[i] = NULL;
		}
	}
	while (true)
	{
		int ilkIndeks = MinDugumIndeks(dugumler);
		Dugum *min1 = dugumler[ilkIndeks];
		dugumler[ilkIndeks] = NULL;
		int ikinciIndeks = MinDugumIndeks(dugumler);
		if (ikinciIndeks == -1) {
			return min1;
		}
		Dugum *min2 = dugumler[ikinciIndeks];
		dugumler[ikinciIndeks] = NULL;
		dugumler[ilkIndeks] = new Dugum(0, min1->frekans + min2->frekans, min1, min2);
	}

}
int Huffman::MinDugumIndeks(Dugum* dugumler[]) {
	Dugum* min;
	int minIndeks = -1;

	// ilk null olmayan düðümü min al
	for (int i = 0; i<harfler; i++)
	{
		if (dugumler[i] != NULL)
		{
			min = dugumler[i];
			minIndeks = i;
			break;
		}
	}

	for (int i = 0; i<harfler; i++)
	{
		if (dugumler[i] == NULL) continue;

		if (*min > *(dugumler[i]))
		{
			min = dugumler[i];
			minIndeks = i;
		}
	}
	return minIndeks;
}
void Huffman::KodOlustur(Dugum* alt_dugum, string kod) {
	if (!alt_dugum->YaprakMi())
	{
		KodOlustur(alt_dugum->sol, kod + "0");
		KodOlustur(alt_dugum->sag, kod + "1");
	}
	else {
		alt_dugum->kod = kod;
	}
}
ostream& operator<<(ostream& ekran, Huffman& krk) {
	ekran << "Huffman Agacindaki Karakterler ve Kodlari:" << endl;
	krk.Inorder(krk.kok);
	return ekran;
}



void Huffman::Inorder(Dugum* alt_dugum) //inorder olarak ekrana yazdýrýrken ayný zamanda tablo.txt oluþturup inorder olarak tabloya yazdýran fonksiyon.
{
	if (alt_dugum != NULL)
	{
		Inorder(alt_dugum->sol);
		if (alt_dugum->YaprakMi())
		{

			fstream file;
			file.open("tablo.txt", fstream::in | std::fstream::out | std::fstream::app);

			if (alt_dugum->karakter == ' ')
			{
				cout << "@" << ": " << alt_dugum->kod << endl;
				if (file.is_open() == true)
				{
					file << '@' << " " << alt_dugum->kod << endl;
				}
			}
			else if (alt_dugum->karakter == '\n')
			{
				cout << ">" << ": " << alt_dugum->kod << endl;
				if (file.is_open() == true)
				{
					file << '>' << " " << alt_dugum->kod << endl;
				}
			}
			else
			{
				cout << alt_dugum->karakter << ": " << alt_dugum->kod << endl;
				if (file.is_open() == true)
				{
					file << alt_dugum->karakter << " " << alt_dugum->kod << endl;
				}
			}
			file.close();
		}

		Inorder(alt_dugum->sag);


	}
}
void Huffman::SilDugum(Dugum* alt_dugum) {
	if (alt_dugum == NULL) return;
	SilDugum(alt_dugum->sol);
	SilDugum(alt_dugum->sag);
	delete alt_dugum;
	alt_dugum = NULL;
}

Huffman::~Huffman() {
	// Çöp oluþmamasý için aðaç temizleniyor.
	SilDugum(kok);
}

