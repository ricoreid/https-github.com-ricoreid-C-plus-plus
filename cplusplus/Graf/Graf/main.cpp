#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <time.h>
#include <Windows.h>


using namespace std;


int n, N, G, Size, E;
double a, b, c, d;


float random()
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	/* 

	static_cast <float> performs the conversion of the result from the rand() function into a variable of the type float. Therefore, with this action we are dividing any number from 0 to 32767 with 32767 and we'll receive the result from 0 to 1
	
	*/
	return r;
}


enum
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Мagenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


void setColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


int enterNumber(string text, int maxvalue)
{
	int Value;


	for (;;)
	{
		cout << text << " ";
		if (!(cin >> Value)) // checks for input entry
		{
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Error! Please use digits!" << endl << endl;
			continue;
		}
		else if (maxvalue == 0) break;
		else if (Value > maxvalue)
		{
			cout << "Error! Please enter the number not more than " << maxvalue << "!" << endl << endl;
			continue;
		}
		else break;
	}
	return Value;
}


void getData()
{
	N = enterNumber("Enter N:", 256);	
	G = enterNumber("Enter G(%):", 100); 


	for (n = 0; ; n++) 
	{
		Size = (int)pow(2., n); 
		if (Size >= N) break; 
	}
	float Tmp = ((float)G / 100) * N*(N - 1) / 2;	
	E = (int)Tmp;
}


int putOnes(int** mac, float a, float b, float c, float d, int x, int y, int count)
{
	if (count == 0) // If necessary - we are writing down into the array the number one
	{
		if (mac[x][y] == 1) return 0;
		else if (x == y) return 0;	// On main diagonal cannot be the number ones
		else
		{
			mac[x][y] = 1;
			return 1;
		}
	}
	else
	{
		int x1, y1; // New variables for copying the values
		float r;
		int p = (int)pow(2., count - 1);  
		r = random();		
							/* The codes below check whether we hit on the given probability */
		if (r < a) { x1 = x; y1 = y; }
		else if (r >= a && r < a + b) { x1 = x + p; y1 = y; }
		else if (r >= a + b && r < a + b + c) { x1 = x; y1 = y + p; }
		else if (r >= a + b + c) { x1 = x + p; y1 = y + p; }


		return putOnes(mac, a, b, c, d, x1, y1, count - 1); // Recursion with new x1 variables and y1. We are making the meter smaller count, because we have a recursion
	}


}


int main()
{
	srand(time(NULL));
	getData();
	cout << endl << "n = " << n;
	cout << endl << "Size of the matrix = 2^n = " << Size;
	cout << endl << "E (the amount of ones) = " << E << endl << endl;
	cout << "| | | | | | | | | | | |" << endl;
	cout << "| |     | | | |     | |" << endl;
	cout << "| |  a  | | | |  b  | |" << endl;
	cout << "| |     | | | |     | |" << endl;
	cout << "| | | | | | | | | | | |" << endl;
	cout << "| | | | | | | | | | | |" << endl;
	cout << "| |     | | | |     | |" << endl;
	cout << "| |  c  | | | |  d  | |" << endl;
	cout << "| |     | | | |     | |" << endl;
	cout << "| | | | | | | | | | | |" << endl;
	cout << "Enter probability for the quarters: " << endl;
	while (1)
	{
		cout << "a (in %): ";
		cin >> a;
		cout << "b (in %): ";
		cin >> b;
		cout << "c (in %): ";
		cin >> c;
		cout << "d (in %): ";
		cin >> d;
		cout << endl;
		if ((a + b + c + d) == 100) break;	// if the sum is equal to 100 - we exit the loop.
		else cout << "Error! The sum of probabilities must be 100%. Try once more: " << endl;
	}
	a /= 100; b /= 100; c /= 100; d /= 100;
	int **mac1 = new int *[Size];	
	for (int i = 0; i < Size; i++) 
	{
		mac1[i] = new int[Size];	


		for (int j = 0; j < Size; j++)
		{
			mac1[i][j] = 0;		
		}
	}
	int start = 0, until = E; // Variables for the control of the quantity of number ones
	while (start < until) // We are carrying the function out pace (), until we won't achieve the needed quantity of single rooms
	{
		start += putOnes(mac1, a, b, c, d, 0, 0, n);
	}
	for (int i = 0; i < Size; i++) // prints the matrix
	{
		for (int j = 0; j < Size; j++)
		{
			if (mac1[i][j] == 1) setColor(Yellow, Black); // Changes the colour of all the 1s
			cout << mac1[i][j] << " ";
			setColor(White, Black);	// returns white
		}
		cout << endl;
	}
	// frees memory space used
	for (int i = 0; i < Size; i++) delete[] mac1[i];
	delete[] mac1;
	cout << endl;
	system("pause");
	return 0;
}

