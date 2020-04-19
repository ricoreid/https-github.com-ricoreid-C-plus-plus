/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   L2Z3.cpp
* Author: rico
*
* Created on 05 February 2019, 20:50
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <random>
#include <ctime>
#include <climits>

#include <stdlib.h>

//using namespace std;

void wyszukiwanieBinarne(int tab[], int rozmiar, int wartosc)
{
	int lewy = 0;
	int prawy = rozmiar - 1;
	int srodek = (lewy + prawy) / 2;

	bool znaleziono = false;

	while (lewy <= prawy && !znaleziono)
	{
		if (wartosc == tab[srodek])
		{
			znaleziono = true;
		}
		else if (wartosc > tab[srodek])
		{
			lewy = srodek + 1;
			srodek = (lewy + prawy) / 2;
		}
		else
		{
			prawy = srodek - 1;
			srodek = (lewy + prawy) / 2;
		}
	}

	if (znaleziono == false)
		std::cout << "Wartosc nie znaleziono" << std::endl;
	else
		std::cout << "Wartosc " << wartosc << " znaleziono na indeks " << srodek << std::endl;

	//    std::cin.clear();
	//    std::cin.ignore();

}


int main()
{
	int const ROZMIAR = 10;
	int tab[] = { 2, 4, 9, 23, 29, 31, 36, 50, 58, 77 };
	//int war;
	int x;

	/*
	cout << "Prosze Podac Wartosci Tablice." << endl;
	for(int i = 0; i < ROZMIAR; i++)
	{
	cout << "wartosc " << i + 1 << ": ";
	cin >> war;
	tab[i] = war;
	cout << endl;
	}
	*/




	std::cout << "Prosze podac wartosc do szukiwania: ";

	std::cin >> x;
	//    std::cin.clear();
	//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//    std::cin.get();





	std::cout << "Wartosc do szukania: " << x << std::endl;

	wyszukiwanieBinarne(tab, 10, x);

	system("pause");

	return 0;
}

