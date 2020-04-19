#include <iostream>
#include <iomanip>		
#include <string>
#include <stdlib.h>


#define uint unsigned int


using namespace std;
void fill_Arrays();
uint dekompozycja(uint, uint, uint, uint, uint*, char*);


/* Global variables */
uint _n_, _m_, _p_, _k_;
uint X[100]; // Tablica wejść
char Y[100]; // Tablica wyjść


			 /* Funkcja, która liczy 2^x */
uint pow2(uint x)
{
	uint Result = 1;


	while ((x--) != 0)
	{
		Result *= 2;
	}


	return Result;
}


/* Funkcja, która generuje dowolną liczbę z podanego okresu (min - początek okresu; max - koniec okresu) */
uint rnd(uint min, uint max)
{
	return min + (double)rand() / (RAND_MAX + 1) * (max - min);
}


/* Funkcja, która przeksztalca liczbę binarną w dziesiętną */
uint binToDec(char *bin_arr, uint length)
{
	uint Res = 0;


	for (int i = 0; i < length; i++)
	{
		if ((bin_arr[i] - '0') == 1) Res += pow2(i);
	}


	return Res;
}


/* Funkcja, która przekształca char w unsigned int */
uint charToInt(char c)
{
	return (c - '0');
}


/* Funkcja, która przedstawia liczbę unsigned int w postaci binarnej (value - liczba, którą trzeba przedstawić w postaci binarnej;
size - ilość pozycji liczby binarnej; space - spacji pomiędzy pozycjami liczby binarnej) */
string uintToBin(uint value, uint size, uint space)
{
	string S;
	char *B = new char[100];


	_itoa_s(value, B, 100, 2); // Przekształcamy value w tablicę symboli B[], przekształcenie binarne, więc '2'; 100 - rozmiar tablicy
	S.assign(B); // Przenosimy tablicę symboli w string
	S.insert(0, size - S.length(), '0'); // Dodajemy '0' z lewej strony (np., gde size = 5, to otrzymujemy 00101, a nie 101)
	if (space)
	{
		for (int i = 0; i < S.length() - 1; i++)
		{
			S.insert(++i, 1, ' '); // Wstawiamy spację po każdej pozycji (żeby wypisywać nie 00101, a '0 0 1 0 1' 
		}
	}


	delete[] B; // Zwolnenie pamięci
	return S;
}


/* Funkcja, która wczytuje dane dla wykonania zadania. W wyniku otrzymujemy Size - rozmiar zbioru dla permutacji */
void enter_Data()
{
	uint Var;
	uint Flag = 0;


	/* Dane wejściowe: */
	// 1. Liczba wejść
	for (;;)
	{ // Nieskończona pętla
		cout << "Enter liczba wejsc (n): ";
		if (!(cin >> _n_))
		{ // Należy wprowadzić liczbę, a użytkownik wprowadził literę albo slowo
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Error! Please use digits!" << endl << endl;
			continue; // Zaczynamy pętle od początku - wprowadzamy jeszcze raz
		}
		else
		{
			if ((_n_ < 1) || (_n_ > 9))
			{ // Nie można wprowadzać wartość, mniejszą od 1 i większą od 9
				cout << "Error! Please enter the number not more than 9!" << endl << endl;
				continue; // Zaczynamy pętle od początku
			}
			break; // Jeżeli wszystko OK - wychodziemy z nieskończonej pętli 
		}
	}


	// 2. Liczba stanów określonych
	for (;;)
	{ // Nieskończona pętla
		cout << "Enter stanow okreslonych (p): ";
		if (!(cin >> _p_))
		{ // Należy wprowadzić liczbę, a użytkownik wprowadził literę albo slowo
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Error! Please use digits!" << endl << endl;
			continue; // Zaczynamy pętle od początku - wprowadzamy jeszcze raz
		}
		else
		{
			Var = pow2(_n_);	// 2^n
			if ((_p_ < 1) || (_p_ > Var))
			{ // Nie można wprowadzać wartość, mniejszą od 1 i większą od 2^n
				cout << "Error! Please enter the number not more than: 1 <= p <= 2^n" << endl << endl;
				continue;
			}
			break; // Jeżeli wszystko OK - wychodziemy z nieskończonej pętli 
		}
	}


	// Wypełniamy oraz wypisujemy macierzy wejść i wyjść:
	fill_Arrays();
	cout << endl;


	// 3. Liczba wejść adresowych MUX
	for (;;)
	{
		cout << "Enter liczba wejsc adresowych MUX (k): ";
		if (!(cin >> _k_))
		{ // Należy wprowadzić liczbę, a użytkownik wprowadził literę albo slowo
			cin.clear(); cin.ignore(10, '\n');
			cout << "Error! Please use digits!" << endl << endl;
			continue; // Zaczynamy pętle od początku - wprowadzamy jeszcze raz
		}
		else
		{
			if (_k_ < 1)
			{ // Nie można wprowadzać wartość, mniejszą od 1 
				cout << "Error! Please enter the number not less than 1" << endl << endl;
				continue;
			}
			for (int i = 1; i <= _k_; i++)
			{ // 2^k nie może być większe od p
				if (pow2(i) > _p_)
				{
					Flag = 1;
					break;
				}
			}
			if (Flag)
			{
				Flag = 0;
				cout << "Error! Please enter the number k not more than: 2^k <= p" << endl << endl;
				continue;
			}
			break; // Jeżeli wszystko OK - wychodziemy z nieskończonej pętli 
		}
	}
}


void reverse_CharArr(char *arr)
{
	string S;


	S.assign(arr);	// Przekształcamy tablicę symboli Y w string
	reverse(S.begin(), S.end()); // Zmieniamy kolejność symboli w string
	strcpy_s(arr, S.length() + 1, S.c_str()); // Kopiujemy string w tablicę symboli Y
}


/* Funkcja, która wypełnia tablicy i wyświetla ich */
void fill_Arrays()
{
	uint Var, Out, k = _p_ - 1;
	uint Flag = 0;
	string S;


	memset(Y, NULL, 100); // Oczyszczamy pamięć, gdzie przechowuje się tablica Y
	cout << endl;


	// Otrzymujemy tablicę X
	// 1 - Generujemy pierwszy element tablicy X
	X[0] = rnd(1, pow2(_n_)); // Dowolna liczba z przedziału od 1 do 2^n
							  // 2 - Dalej wypełniamy tablicę X
	for (int i = 1; i < _p_; i++)
	{
		Var = rnd(1, pow2(_n_)); // Dowolna liczba z przedziału od 1 do 2^n
		for (int k = 0; k < i; k++)
		{ // Sprawdzamy, czy kolejny element tablicy nie jest równy żadnemu wcześniejszemu
			if (Var == X[k])
			{
				Flag = 1;
				break;
			}
		}
		if (Flag)
		{ // Jeśli program znachodzi taki sam element wcześniej, to zeruje zmienną Flag
			Flag = 0;
			i--;
			continue;
		}
		X[i] = Var; // Koniec sprawdzenia, wypełniamy
	}
	// Tablica wejść X jest gotowa


	// Otrzymujemy tablicę Y
	Out = rnd(3, pow2(_p_) - 1); // Generujemy Y - dowolna liczba z przedziału od 3 do (2^p - 1) (żeby było co najmniej dwie jedynki, ale nie było tylko jedynek)	
	S = uintToBin(Out, _p_, 0);
	strcpy_s(Y, S.length() + 1, S.c_str()); // Przekształcamy string w tablicę symboli Y[]
	reverse_CharArr(Y); // Rewersujemy kolejność symboli
						// Tablica wyjść Y jest gotowa
						// Dekorowanie
	cout << "     ";
	for (int i = 1; i <= _n_; i++) cout << "x" << i;
	cout << endl;


	// Wyświetlamy tablicy X oraz Y w postaci binarnej
	char *B = new char[100];
	for (int i = 0; i < _p_; i++)
	{
		S = uintToBin(X[i], _n_, 1); // Przekształcamy X[i] w postać binarną; '1' - wpisujemy spacje pomiędzy pozycjami
		if (i == 0) cout << "X = ";
		else cout << "    ";
		cout << "| " << S << " |";	// Wyświetlamy X[i] w postaci binarnej (np., jeśli Х[i]=12, to otrzymujemy 0 0 1 1 0 0)
		if (Y[i] == NULL) Y[i] = '0';
		if (i == 0) cout << "  Y = ";
		else cout << "      ";
		cout << "| " << Y[i] << " |" << endl;
	}
	delete[] B; // Zwolnienie pamięci
}


uint findSolution(uint *X1, char *Y1, uint j, string S)
{
	uint Res = 0; // Wynik = 0, Jeżeli znaleziono warianty
	uint Tmp, Flag1, Flag2;
	Flag1 = Flag2 = 0;


	// Tworzymy tablice wskaźników
	char **W = new char *[10];
	char *H = new char[100];
	char *NotH = new char[100];
	uint *Var = new uint[100];
	uint *NotVar = new uint[100];


	for (int i = 0; i < 10; i++) { W[i] = new char[100]; } // Inicjalizacja wskaźników
	for (int i = 0; i < j; i++)
	{  // Wypełniamy tablicę wejść zerami i jedynkami
		S = uintToBin(X1[i], _n_ - _k_, 0);
		strcpy_s(H, S.length() + 1, S.c_str()); // Kopiujemy string w tablicę H


		for (int j = 0; j < _n_ - _k_; j++)
		{
			W[i][j] = H[j];
		}
	}
	if (Y1[0] != '$')
	{
		for (int col = 0; col < _n_ - _k_; col++)
		{
			for (int row = 0; row < j; row++)
			{
				H[row] = W[row][col];
				NotH[row] = H[row] ^ 1;
			}
			Var[col] = binToDec(H, j);
			NotVar[col] = binToDec(NotH, j);
			Tmp = binToDec(Y1, j);
			if (Var[col] == Tmp)
			{
				Flag1 = 1;
				if (!Flag2) cout << "-> Y = ";
				cout << "x" << (col + 1 + _k_) << "; ";
				Res = 1;
			}
			if (NotVar[col] == Tmp)
			{
				Flag2 = 1;
				if (!Flag1)	cout << "-> Y = ";
				cout << "x!" << (col + 1 + _k_) << "; ";
				Res = 1;
			}
		}
	}


	// Zniszczenie dynamicznych tablic
	delete[] NotVar;
	delete[] Var;
	delete[] NotH;
	delete[] H;
	for (int i = 0; i < 10; i++) { delete[] W[i]; }
	delete[] W;


	return Res;
}


void synteza_MUX()
{
	uint L = 0;
	dekompozycja(L, _n_, 0x00, _p_, X, Y);
}




uint dekompozycja(uint level, uint numofinputs, uint name, uint numofstates, uint *arr_inputs, char *arr_outputs)	// name - imię MUXi, P - ilość stanów 
{
	string S;
	uint Tmp, Fl_FoundAmbiguity = 0;
	cout << endl << "--------------------------------" << endl << endl;


	char *B = new char[100];
	// 1. Level L
	cout << "L = " << level << endl;
	cout << "A = ";
	for (int i = level*_k_; i < (level + 1)*_k_; i++)	cout << "x" << i + 1;
	cout << endl;


	uint *X1 = new uint[100];
	for (int k = 0; k < pow2(_k_); k++)
	{
		int j = 0;
		char *Y1 = new char[100];
		cout << "           ";
		for (int i = (level + 1)*_k_; i < _n_; i++) cout << "x" << i + 1;
		cout << endl;


		for (int i = 0; i < numofstates; i++)
		{
			if (arr_inputs[i] >> (numofinputs - _k_) == k)
			{   // Jeśli znaleziono kombinację z okresu 0...2^k 
				X1[j] = arr_inputs[i] & (pow2(numofinputs - _k_) - 1);
				Y1[j++] = arr_outputs[i];
				cout << setw(2) << i + 1 << " -> ";
				if (j - 1 == 0) cout << "X = | ";
				else cout << "    | ";
				cout << uintToBin(X1[j - 1], numofinputs - _k_, 1) << " |  ";
				if (j - 1 == 0) cout << "Y = | ";
				else cout << "    | ";
				cout << Y1[j - 1] << " |" << endl;


			}
			else {	// Jeśli nie znaleziono kombinację z okresu 0...2^k 
				Y1[i] = '$'; // Znak '$' oznacza, że Y1 jest pusty
			}
		}


		_itoa_s(k, B, 100, 2);	// Przekształcamy Out w tablicę symboli Y[], przekształcenie binarne, więc '2'; 100 - rozmiar tablicy
		S.assign(B); // Przenosimy tablicę symboli w string
		S.insert(0, _k_ - S.length(), '0');	// Dodajemy '0' z lewej strony
		cout << "MUX" << name << "(" << setw(_k_) << S << ") ";


		// Sprawdzamy wartości Y1, i jeśli są one różne, to potrzebujemy kolejnej dekompozycji
		// 1 - Sprawdzamy '0' i '1'
		Tmp = charToInt(Y1[0]);
		for (int a = 1; a < j; a++)
		{
			if (charToInt(Y1[a]) != Tmp)
			{
				Fl_FoundAmbiguity = 1;
				break;
			}
			Tmp = charToInt(Y1[a]);
		}
		// 2 - Jeżeli jest różnica, to potrzebujemy kolejnej dekompozycji:
		if (Fl_FoundAmbiguity)
		{
			Fl_FoundAmbiguity = 0;
			// Szukamy kombinacje, które odpowiadają otrzymanej Y1, na wejściach X
			if (!findSolution(X1, Y1, j, S))
			{
				reverse_CharArr(B);
				name = binToDec(B, _k_);
				cout << "= MUX" << name << endl;
				// Tworzymy nowe macierzy wejść i wyjść
				uint *uX = new uint[100];
				char *uY = new char[100];
				for (int i = 0; i < j; i++)
				{
					uX[i] = X1[i];
					uY[i] = Y1[i];
				}
				if (numofinputs - _k_ > _k_)
				{
					numofinputs -= _k_;
					dekompozycja(++level, numofinputs, name, j, uX, uY);


					// Odnawiamy wartości level i numofinputs
					level--;
					numofinputs += _k_;
					// Drukujemy, jakim był poziom (kontynujemy...)
					cout << endl << "--------------------------------" << endl << endl;
					cout << "L = " << level << endl;
					cout << "A = ";
					for (int i = level*_k_; i < (level + 1)*_k_; i++)	cout << "x" << i + 1;
					cout << endl;
				}
				else
				{
					cout << "Dekompozycja jest niemozliwa!" << endl;
					cout << "Liczba pozostałych wyjść jest mniejsza niż liczba wejść adresowych 'k'!" << endl;
				}
				delete[] uY;
				delete[] uX;
			}
		}
		else
		{ // Wartości w macierzy wejść nie różnią się
			if (Y1[0] == '$') cout << "... no matches" << endl;
			else cout << "= " << Y1[0];
		}
		delete[] Y1;
		cout << endl;
	}
	delete[] X1;
	delete[] B;
	return 0;
}


int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL)); // Każdy raz liczby losowe będą różne


	enter_Data();
	cout << endl << "Thank you! Rozwiazanie:" << endl << endl;
	cout << "Dekompozycja UK na MUX" << endl;
	synteza_MUX();


	cout << endl;
	system("pause");
	return 0;
}

