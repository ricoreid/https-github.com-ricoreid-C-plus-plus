#include <iostream>
#include <ctime>
#include <cstdlib>

void zamiana(int &a, int &b) {

	int temp = a;
	a = b;
	b = temp;
}
void drukujTablice(int* tab, int rozmiar) {

	for (int i = 0; i < rozmiar; i++) {
		std::cout << tab[i] << " ";
	} // koniec petli for
	std::cout << std::endl;
}
void sortowacTablice(int* tab, int rozmiar) {
	
	clock_t poczatek = clock();
	int pierwsza = 0;
	int druga = 0;

	for (int i = 1; i < rozmiar; i++) {
		pierwsza = i;
		druga = i - 1;

		while (druga >= 0 && tab[pierwsza] < tab[druga]) {
			zamiana(tab[pierwsza], tab[druga]);
			druga = druga - 1;
			
			pierwsza = druga + 1;
		} // konca petli while
	} // konca petli for
	clock_t koniec = clock();
	double wynik = ((double)koniec - poczatek) / CLOCKS_PER_SEC;
	std::cout << "skonczyl na: " << wynik << " ms" << std::endl;
} // konca funkcja sortowacTablice

int main() {

	srand(time(NULL));
	const int ROZMIAR = 1000;
	int tab[ROZMIAR];

	for (int i = 0; i < ROZMIAR; i++) {
		tab[i] = rand() % 1000 + 1;
	} // koniec petli for

	drukujTablice(tab, ROZMIAR);
	sortowacTablice(tab, ROZMIAR);
	drukujTablice(tab, ROZMIAR);

	system("pause");

	return 0;
} // koniec funkcja main