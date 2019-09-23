#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <intrin.h>


#define uchar	unsigned char
#define uint	unsigned int
#define ulong	unsigned long


using namespace std;


/* Deklarujemy globalne zmienne */
int W; // Pojemność plecaka
int n; // Ilość przedmiotów
int Weight[31], Cost[31]; // Tablice wagi i wartości każdego przedmiotu
typedef enum { FROM_FILE = 0, MANUAL_INPUT = !FROM_FILE }; // Potrzebujemy dla odczytu


														   /* Funkcja, która wczytuje dane dla wykonania zadania i sprawdza, czy użytkownik wprowadził nieujemną liczbę, a nie np. słowo.
														   FROM_FILE i MANUAL_INPUT to po prostu 0 albo 1 - one są zdefiniowane wcześniej. W pliku dane.txt w pierwszym wierszu jest wskazany rozmiar
														   plecaka, a w pozostałych wierszach — wagi oraz wartości przedmiotów. Ilość przedmiotów n ustala się z ilości wierszy z wagami i wartościami */
void enter_Data(uint inputmethod)
{
	ifstream inFile("dane.txt");
	// 1. Wprowadzamy pojemność plecaka
	if (inputmethod == MANUAL_INPUT) // Jeśli jest wybrane MANUAL_INPUT, to wprowadzamy dane ręcznie
	{
		for (;;)
		{
			cout << "Enter Capacity of Backpack (W): ";
			if (!(cin >> W))
			{ // Trzeba wprowadzić liczbę, a nie np. słowo
				cin.clear();
				cin.ignore(10, '\n');
				cout << "Error! Please use digits!" << endl << endl;
				continue; // Zaczynamy pętlę od początku
			}
			else
			{
				if (W < 1)
				{ // Trzeba wprowadzić nieujemną liczbę całkowitą nie równą zeru
					cout << "Error! Please enter the number more than 0!" << endl << endl;
					continue; // Zaczynamy pętlę od początku
				}
				break; // Jeśli wszystko OK - wychodzimy z pętli 
			}
		}


		// 2. Wprowadzamy ilość przedmiotów
		for (;;)
		{
			cout << "Enter Number of items (n): ";
			if (!(cin >> n))
			{ // Trzeba wprowadzić liczbę, a nie np. słowo
				cin.clear();
				cin.ignore(10, '\n');
				cout << "Error! Please use digits!" << endl << endl;
				continue; // Zaczynamy pętlę od początku
			}
			else
			{
				if ((n < 1) || (n > 31))
				{ // Trzeba wprowadzić nieujemną liczbę całkowitą nie równą zeru oraz nie większą od 31
					cout << "Error! Please enter the number not more than 31!" << endl << endl;
					continue; // Zaczynamy pętlę od początku
				}
				break; // Jeśli wszystko OK - wychodzimy z pętli 
			}
		}


		// 3. Wprowadzamy wagę i wartość każdego przedmiotu
		cout << "Enter Weight and Cost of each item: " << endl;
		for (int i = 0; i < n; i++)
		{
			for (;;)
			{
				cout << i + 1 << ". Weight = ";
				if (!(cin >> Weight[i]))
				{ // Trzeba wprowadzić liczbę, a nie np. słowo
					cin.clear();
					cin.ignore(10, '\n');
					cout << "Error! Please use digits!" << endl << endl;
					continue; // Zaczynamy pętlę od początku
				}
				else
				{
					if (Weight[i] < 1)
					{ // Trzeba wprowadzić nieujemną liczbę całkowitą
						cout << "Error! Please enter the number more than 1!" << endl << endl;
						continue; // Zaczynamy pętlę od początku
					}
					break; // Jeśli wszystko OK - wychodzimy z pętli 
				}
			}
			for (;;)
			{
				cout << "   Cost = ";
				if (!(cin >> Cost[i]))
				{ // Trzeba wprowadzić liczbę, a nie np. słowo
					cin.clear();
					cin.ignore(10, '\n');
					cout << "Error! Please use digits!" << endl;
					continue; // Zaczynamy pętlę od początku
				}
				else
				{
					if (Cost[i] < 1)
					{ // Trzeba wprowadzić nieujemną liczbę całkowitą
						cout << "Error! Please enter the number more than 1!" << endl;
						continue; // Zaczynamy pętlę od początku
					}
					break; // Jeśli wszystko OK - wychodzimy z pętli 
				}
			}
			cout << endl;
		}
	}
	else if (inputmethod == FROM_FILE) // Jeśli jest wybrane FROM_FILE, to wczytujemy dane z pliku tekstowego
	{
		inFile >> W; // Pierwsza liczba w pliku - pojemność plecaka
		int i = 0; // Indeks początkowy tablic Weight[] i Cost[] dla wczytania z pliku
		while (inFile >> Weight[i])	inFile >> Cost[i++]; // Dopóki plik nie skończył się, wczytujemy po kolei Weight i Cost każdego przedmiotu, a potem inkrementujemy i
		inFile.close();	// Zamykamy plik
		n = i; // i - ilość przedmiotów
			   // Wyświetlamy wczytane dane
		cout << "Capacity of Backpack (W): " << W << endl;
		cout << "Number of items (n): " << n << endl;
		cout << "Weight and Cost of each item: " << endl;
		for (int j = 0; j < n; j++)
		{
			cout << j + 1 << ". Weight = " << Weight[j];
			cout << "; cost = " << Cost[j] << endl;
		}
	}
}


/* Funkcja, która wypełnia plecak. Działa ona na programowaniu dynamicznym (go realizuje tablica DP[][], gdzie wiersze to numery przedmiotów
od 0 do podanej wartości n; kolumny to wagi od 0 do pojemności plecaka W). Funkcja ta posiada 4 argumenty: weight[] - tablica wag;
cost[] - tablica wartości; capacity - pojemność plecaka; qty - ilość przedmiotów. Najpierw funkcja znachodzi maksymalną wartość przedmiotów,
które należy położyć do plecaka, a potem przebiera wszystkie najlepsze wartości i sprawdza, które z nich zmieścią się w plecaku. */
int fillBackpack(int *weight, int *cost, int capacity, int qty)
{
	int BestCost = 0, BestWeight = 0;
	/* Tworzymy główną tablicę dwuwymiarową */
	int **DP = new int*[qty + 1]; // Tworzymy tablicę wskaźników (wiersze macierzy)
	for (int i = 0; i < qty + 1; i++) { DP[i] = new int[capacity + 1]; } // Inicjalizacja wskaźników dla tablicy DP[][] (kołumny)


																		 /* Tworzymy tablicę, która liczy przedmioty dodane do plecaka */
	int **Set = new int*[qty + 1];
	for (int i = 0; i < qty + 1; i++) { Set[i] = new int[capacity + 1]; }


	/* Zerujemy wszystkie elementy tablic DP[][] i Set[][] */
	for (int i = 0; i < qty + 1; i++) {
		for (int j = 0; j < capacity + 1; j++) {
			DP[i][j] = Set[i][j] = 0;
		}
	}


	for (int i = 1; i <= qty; i++) { // Przebieramy wiersze (przedmioty)
		for (int j = 1; j <= capacity; j++) { // ... i wewnątrz - kolumny
			if (weight[i - 1] <= j) {
				BestCost = DP[i - 1][j - weight[i - 1]] + cost[i - 1];
				if (BestCost >= DP[i - 1][j]) {
					DP[i][j] = BestCost;
					Set[i][j] = 1;
				}
				else {
					DP[i][j] = DP[i - 1][j];
					Set[i][j] = 0;
				}
			}


			else {
				DP[i][j] = DP[i - 1][j];
				Set[i][j] = 0;
			}
		}
	}
	// W wyniku programowania dynamicznego otrzymaliśmy najlepszą wartość:
	BestCost = DP[qty][capacity];


	/* Teraz powinniśmy dowiedzieć się, które przedmioty zostały dodane do plecaka: w miejscach, gdzie znajdowaliśmy najlepszą wartość,
	pozostały '1'. Zaczynać powinniśmy z końca, bo w DP[][] właśnie ostatni element ma najlepszą wartość */
	cout << "Used Items: ";
	int j = capacity;
	for (int i = qty; i > 0; i--) {
		if (Set[i][j] == 1) {
			cout << i << " ";
			BestWeight += weight[i - 1]; // Dodajemy przedmiot do plecaka
			j -= weight[i - 1];
		}
	}
	cout << endl;
	cout << "Best Weight: " << BestWeight << endl; // Wyświetlenie
												   /* Dealokacja tablic dynamicznych */
	for (int i = 0; i < qty + 1; i++) { delete[] Set[i]; }
	delete[] Set;
	for (int i = 0; i < qty + 1; i++) { delete[] DP[i]; }
	delete[] DP;
	return BestCost;
}


/* Funkcja, która wybiera najlepszy zestaw przedmiotów */
void findBestPrice()
{
	cout << "Best Cost: " << fillBackpack(Weight, Cost, W, n) << endl;
}


int main()
{
	srand((unsigned)time(NULL));
	enter_Data(MANUAL_INPUT);
	//enter_Data(FROM_FILE);
	cout << endl << "Dziekuje! Rozwiazanie:" << endl << endl;
	findBestPrice();
	cout << endl;
	system("pause");
	return 0;
}

