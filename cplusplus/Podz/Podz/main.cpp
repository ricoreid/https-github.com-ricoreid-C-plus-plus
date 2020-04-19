/** Rule [1]:	for example,
if arraySize = 4,
generate all the numbers between 1111 and 1234
using only the digits 1, 2, 3 and 4:
1111
1112
1113	-> to remove: rule [3]
1114	-> to remove: rule [3]


1121
1122
1123
1124	-> to remove: rule [3]


1131	-> to remove: rule [3]
1132	-> to remove: rule [3]
1133	-> to remove: rule [3]
1134	-> to remove: rule [3]


1211
1212
1213
1214	-> to remove: rule [3]


1221
1222
1223
1224	-> to remove: rule [3]


1231
1232
1233
1234


*/

#include <iostream>
#include <math.h>

using namespace std;


// Instance variables
int A[100];
int arraySize;


void populateArray()
{
	for (int i = 0; i < arraySize; i++) {
		A[i] = 1;
	}
}


void dataInput()
{
	for (;;) {
		cout << "Enter the arraySize of the array: ";
		if (!(cin >> arraySize)) {
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Error! Please use digits!" << endl << endl;
			continue;
		}
		else break;
	}
	populateArray();
}

// This function generates next number according to rule [1]

void generateNumber()
{
	static int Index[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static int Entrance = 1;


	if (Entrance++ == 1) return;


	A[arraySize - 1]++;
	if (A[arraySize - 1] > arraySize) {
		populateArray();
		for (int i = 2; i <= arraySize; i++) {
			if (Index[i] < arraySize - i) {
				Index[i]++;
				for (int j = 0; j < i; j++)	Index[j] = 0;
				break;
			}
		}
		for (int i = 2; i <= arraySize; i++) {
			A[arraySize - i] += Index[i];
		}
	}
}


// This function removes odd rows according to rule [3]
// returns: 0 - true row
// 1 - false row

bool removeOddEntry()
{
	int Max = A[0];
	int Cnt = 0;


	for (int i = 0; i < arraySize; i++) {
		for (int j = 0; j < i; j++) {
			if (A[j] > Max) {
				Max = A[j];
				Cnt++;
			}
		}
		if (abs(A[i] - Max) > 1) {
			if (A[i] > Cnt) return 1;
		}
	}
	return 0;
}


void Podzialy(int w)
{
	static int N = 1;
	if (w < arraySize) {
		for (int i = w; i < arraySize; i++) {
			Podzialy(w + 1);
		}
	}
	else {
		generateNumber();
		if (removeOddEntry()) return;
		cout << N++ << "=> ";
		for (int j = 0; j < arraySize; j++) {
			cout << A[j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	dataInput();
	Podzialy(0);

	cout << endl;
	system("pause");
	return 0;
}

