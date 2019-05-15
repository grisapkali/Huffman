#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include<string>
#include "Dugum.hpp"
#include<locale.h> 

class Huffman {
private:
	int harfler;  			// harflerin ASCII karþýlýklarý
	string girdi;			// dosyadan okunan girdi
	Dugum *kok;
	string binaryDat = "";


	Dugum* AgacOlustur(int frek[]);
	void KodOlustur(Dugum*, string);
	int MinDugumIndeks(Dugum* dugumler[]);
	void DosyaOku(string);
	void Inorder(Dugum*);
	void SilDugum(Dugum*);

	string bitOkuyucu(string);
	void BinaryCevir();
public:
	Huffman(string);
	void Kodla();
	void DatYaz();
	void DatOkuyucu();
	friend ostream& operator<<(ostream&, Huffman&);
	~Huffman();
};


#endif