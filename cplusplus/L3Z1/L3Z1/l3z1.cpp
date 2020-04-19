#include <iostream>
#include <ctime>
#include <cstdlib>

void zamienia(int &a, int &b)
{
	
	int temp = a;
	a = b;
	b = temp;

}

void sortowanie(int tab[], int rozmiar)
{
	
	for (int i = 0; i < rozmiar; i++)
	{
		int min = tab[i];
		for (int j = i + 1; j < rozmiar; j++)
		{
			if (tab[j] < min)
			{
				min = tab[j];
				zamienia(tab[i], tab[j]);
			}
		}
	}

}
void drukujTablice(int tab[], int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		std::cout << tab[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	srand(time(NULL));
	const int ROZMIAR = 20;
	int tab[ROZMIAR];

	for (int i = 0; i < ROZMIAR; i++)
	{
		tab[i] = rand() % 100 + 1;
	}

	std::cout << "Tablica nie sortowana" << std::endl;
	drukujTablice(tab, ROZMIAR);
	sortowanie(tab, ROZMIAR);
	std::cout << "Tablica sortowana" << std::endl;
	drukujTablice(tab, ROZMIAR);

	system("pause");

	return 0;
}