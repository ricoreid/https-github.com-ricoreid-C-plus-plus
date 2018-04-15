#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void zmienicWartosci(int*, int*);
void robicPemutacji(int*, int, int, fstream&);

int main() {

	fstream off;
	string plikNazwa;
	cout << "Prosze podac imie: ";
	getline(cin, plikNazwa);

	off.open(plikNazwa + ".txt", ios::out);
	if (!off)
		cout << "cos nie tak" << endl;

	int rozmiarTablicy = 0;
	cout << "Prosze podac rozmiar tablica: ";
	cin >> rozmiarTablicy;
	cout << endl;

	int *tab = new int[rozmiarTablicy];
	for (int i = 0; i < rozmiarTablicy; i++) {

		cout << "Podac wartosc " << i + 1 << ": ";
		cin >> tab[i];
		cout << endl;
	}

	robicPemutacji(tab, 0, rozmiarTablicy - 1, off);

	delete tab;

	off.close();

	system("PAUSE");
	return 0;
}

void zmienicWartosci(int *indeks1, int *indeks2) {

	int temp = *indeks1;
	*indeks1 = *indeks2;
	*indeks2 = temp;
}

//Wykonać permutacje i zapisz na pliku
void robicPemutacji(int *tab, int indeks, int rozmiarTab, fstream &off) {

	int j;
	if (indeks == rozmiarTab) {

		for (int i = 0; i < rozmiarTab + 1; i++) {
			cout << setw(2) << tab[i];
			off << setw(2) << tab[i];
		}
		cout << endl;
		off << endl;
	}
	else {

		for (j = indeks; j <= rozmiarTab; j++) {

			zmienicWartosci((tab + indeks), (tab + j));
			robicPemutacji(tab, indeks + 1, rozmiarTab, off);
			zmienicWartosci((tab + indeks), (tab + j));
		}
	}

}
