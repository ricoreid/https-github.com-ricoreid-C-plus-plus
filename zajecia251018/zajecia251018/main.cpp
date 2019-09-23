#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>

using namespace std;

void zmiana(int a, int b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
}

void szybkiSortuj(int tab[], int lewy, int prawy)
{
	int i = lewy;
	int j = lewy;
	int g = prawy;

	for (j; j < g; j++)
	{
		if (tab[j] <= tab[g])
		{
			
			zmiana(tab[i], tab[j]);
			i++;
		}
		
	}
	zmiana(tab[i], tab[g]);

	szybkiSortuj(tab, lewy, i - 1);
	szybkiSortuj(tab, i + 1, prawy);
}

void drukuj(int tab[], int)
{


}

int main()
{

	srand(time(NULL));

	int const N = 20;

	int tab[N];

	for (int i = 0; i < N; i++)
	{
		tab[i] = (rand() % 20) + 1;
	}

	szybkiSortuj(tab, 0, N-1);

	drukuj(tab, N);

	system("pause");
}