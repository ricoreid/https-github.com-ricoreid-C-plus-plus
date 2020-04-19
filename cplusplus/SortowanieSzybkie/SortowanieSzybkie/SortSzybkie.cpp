#include <iostream>
#include <ctime>
#include <cstdlib>

void zamiana(int &a, int &b) {

	int temp = a;
	a = b;
	b = temp;
}

void sortowacTablice(int* tab, int lewy, int prawy) {

	int i = lewy;
	int j = prawy;
	int pivot = prawy / 2;
	
	while (i <= j) {
		while (tab[i] < pivot)
			i++;

		while (tab[j] > pivot)
			j--;

		if (i <= j) {
			zamiana(tab[i], tab[j]);
			i++;
			j--;
		}
	}

	if (lewy < j)
		sortowacTablice(tab, lewy, j);

	if (i < prawy)
		sortowacTablice(tab, i, prawy);
	
}

void drukujTablice(int* tab, int rozmiar) {

	for (int i = 0; i < rozmiar; i++) {
		std::cout << tab[i] << " ";
	} // koniec petli for
	std::cout << std::endl;
}

int main() {

	srand(time(NULL));
	const int ROZMIAR = 5;
	int tab[ROZMIAR];

	for (int i = 0; i < ROZMIAR; i++) {
		tab[i] = rand() % 100 + 1;
	} // koniec petli for

	drukujTablice(tab, ROZMIAR);
	sortowacTablice(tab, 0, ROZMIAR - 1);
	drukujTablice(tab, ROZMIAR);

	system("pause");

	return 0;
} // koniec funkcja main