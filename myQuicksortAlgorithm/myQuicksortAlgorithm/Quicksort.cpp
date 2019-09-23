#include <iostream>
#include <ctime>
#include <cstdlib>

void zamiana(int &a, int &b) {

	int temp = a;
	a = b;
	b = temp;
}
int podzial(int* tab, int rozmiar) {

	return 0;
}

void drukujTablice(int* tab, int rozmiar) {

	for (int i = 0; i < rozmiar; i++) {
		std::cout << tab[i] << " ";
	} // koniec petli for
	std::cout << std::endl;
}
void sortowacTablice(int* tab, int rozmiar) {

	// assign pivot to the last digit in the array.
	int i = 0;
	for (int j = 0; j < rozmiar - 1; j++) {
		if (tab[j] > tab[rozmiar - 1]) {
			continue;
		}
		else {
			zamiana(tab[j], tab[i]);
		}
		i++;
	}

	// divide the array and place the pivot in the correct position.

	zamiana(tab[i], tab[rozmiar - 1]);

	//sortowacTablice(tab, i);

	
} // konca funkcja sortowacTablice

int main() {

	srand(time(NULL));
	const int ROZMIAR = 10;
	int tab[ROZMIAR];

	for (int i = 0; i < ROZMIAR; i++) {
		tab[i] = rand() % 100 + 1;
	} // koniec petli for

	drukujTablice(tab, ROZMIAR);
	sortowacTablice(tab, ROZMIAR);
	drukujTablice(tab, ROZMIAR);

	system("pause");

	return 0;
} // koniec funkcja main