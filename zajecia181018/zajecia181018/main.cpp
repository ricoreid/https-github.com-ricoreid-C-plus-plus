#include <ctime>
#include <iostream>
#include <cstring>

using namespace std;


void wstaw(int* tab, int n) 
{ //funkcja zapelniajaca tablice tab o rozmiarze n
	for (int i = 0; i<n; i++) tab[i] = rand() % 10;
}
void drukuj(int* tab, int n, char *txt) 
{
	printf(txt);
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
} //funkcja do wyswietlenia danych z tablicy
void zamian(int* tab, int a, int b)
{
	int temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}
void sortuj1(int* tab, int n)
{
	int kroki = 0;
		//buble sort | prosta zamiane
	for (int i = 0; i < n; i++)
	{
		
		for (int j = n - 1; j >= i; j--)
		{
			if(tab[j] < tab[j - 1])
				zamian(tab, j, j - 1);

			kroki++;
		} // konca druga petli for

	} // konca piersza petli for
	cout << endl << "ilosc kroki: " << kroki << endl;

	drukuj(tab, n, "sortowanie przez Bubble: ");
	cout << endl;
}
void sortujPrzezWybieranie(int* tab, int n)
{
	int min = 0;
	int kroki2 = 0;
	for (int i = 0; i < n; i++)
	{
		min = tab[i];
		for (int j = i; j < n; j++)
		{
			if (tab[i] < tab[j])
				zamian(tab, i, j);

			kroki2++;
		}
	}

	cout << endl << "ilosc kroki: " << kroki2
		<< endl;
	drukuj(tab, n, "Sortowanie przez Wybrania: ");
	cout << endl;
}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	const int N = 1000; //rozmiar tablicy

	int tab[N];

	wstaw(tab, N);
	drukuj(tab, N, "Dowolnym ciagu: ");
	clock_t poczatek = clock();
	sortuj1(tab, N);
	clock_t koniec = clock();
	double wynik = ((double)koniec - (double)poczatek) / CLOCKS_PER_SEC;
	cout << "czas na sortowanie: " << wynik << " ms" << endl;

	clock_t poczatek2 = clock();
	sortujPrzezWybieranie(tab, N);
	clock_t koniec2 = clock();
	double wynik2 = ((double)koniec2 - (double)poczatek2) / CLOCKS_PER_SEC;
	cout << "czas na sortowanie: " << wynik2 << " ms" << endl;

	system("pause");
		return 0;
}