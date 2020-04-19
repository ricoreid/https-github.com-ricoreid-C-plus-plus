#include <iostream>	
#include <stdlib.h>
#include <list>		
#include <map>		
#include <vector>	
#include <string>
#include <time.h>


using namespace std;


/* Private defines */
#define uchar	unsigned char
#define uint	unsigned int
#define ulong	unsigned long
/* Macroses */
#define ch(x)		'0' + x	
#define abs(x)		(x < 0 ? -x : x)
#define max(a, b)	(a > b ? a : b)	


/* Tworzymy klasę */
class Node
{
public:
	char Sym;	// Symbol
	int  Num;	// Liczba
	Node *Up, *Dn;	// Wskaźniki na górną i dolną gałąź (górne i dolne dziecko)


					/* Tworzymy konstruktor, żeby można było odrazu zdefiniować Sym и Num (np. Node NNN('q', 16) -> NNN.Sym = 'q'; NNN.Num = 16) */
	Node(char s, int n) { Sym = s; Num = n; }


	/* Tworzymy konstruktor, który robi linki pustymi */
	Node() { Up = Dn = NULL; }


	/* Tworzymy konstruktor, który potrzebujemy dla wygenerowania drzewa */
	Node(Node *up, Node *dn)
	{
		Sym = 0; // Nie ma symbolu
		Up = up; // Zapisuje w *Up link na górnego dziecka
		Dn = dn; // Zapisuje w *Dn link na dolnego dziecka
		Num = up->Num + dn->Num;
	}


	// Obciążenie operatora '<' (żeby było możliwe sortowanie za parametrem Num)
	bool operator < (Node n) const
	{
		return Num < n.Num;
	}
};


/* Struktury */
/* Tworzymy strukturę dla sortowania wskaźników */
struct comparePtr
{
	// Obciążenie operatora '()'  
	bool operator () (const Node *up, const Node *dn) const
	{
		return up->Num < dn->Num; // Jeśli górny Num jest mniejszy, to true, jeśli dolny - false 
	}
};
void printTree(Node *root, int n);
void buildCodeTable(Node *root);
/* Globalne zmienne */
vector<bool> _Code;	// W tej tablicę będziemy przechowywać kody binarne
map<char, vector<bool> > _Table; // Tablica asocjacyjna (symbol - odpowiadający kod)


								 /* Tworzymy funkcję, która koduje tekst za pomocą algorytmu Huffmana */
void encoding()
{
	/* 1. Wprowadzamy tekst, przebieramy wiersze i liczymi częstotliwości */
	map<char, int> A; // Tworzymy tablicę asocjacyjną A (każdemu symbolu odpowiada liczba)
	string S; // Tekst, który należy zakodować
	cout << "Please enter the text for the encoding by Huffman algorithm:" << endl << "> ";
	getline(cin, S); // Wprowadzamy tekst


					 /* 2. Wyświetlamy rozmiar tekstu wejściowego */
	cout << endl << "The size of input text is: " << (S.length() * 8) << " bit (" << S.length() << " byte)" << endl << endl;
	for (uint i = 0; i < S.length(); i++) { // Wypelniamy tablicę asocjacyjną А
		char Ch = S[i];
		A[Ch]++;
	}


	/* 3. Wyświetlany ilośc róznych symboli w tekscie oraz ich częstotliwość */
	cout << "1. The input text contains the following number of characters:" << endl;
	map<char, int>::iterator ii;
	for (ii = A.begin(); ii != A.end(); ii++) {
		cout << "'" << ii->first << "' - " << ii->second << endl;
	}
	cout << endl;


	/* Tworzymy list z początkowymi węzłami (zapisane w map A) i sortujemy od mniejszej do większej częstotliwości: */
	list<Node*> L; // Tworzymy listę wskaźników na Node
	map<char, int>::iterator ij;
	for (ij = A.begin(); ij != A.end(); ij++) {	// Przebieramy map A i tworzymy węzły 
		Node *ptr = new Node; // Tworzymy nowy węzeł w pamięci dynamicznej
		ptr->Sym = ij->first; // Sym - symbol (pierwszy element z tablicy asocjatywnej map A)
		ptr->Num = ij->second; // Num - ilość występowań symbolu (drugi element z tablicy asocjatywnej map A)
		L.push_back(ptr); // "Łożymy" stworzony węzeł ptr w listę L    
	}
	/* W wyniku w L otrzymujemy wskaźniki na obiekty Node */
	/* Sortujemy - wykorzystamy soecjalną strukturę comparePtr: */
	L.sort(comparePtr());


	/* 4. Wyświetlamy wysortowaną listę symboli */
	cout << "2. The sorted list of the characters:" << endl;
	list<Node*>::iterator ik;
	for (ik = L.begin(); ik != L.end(); ik++) {
		cout << (*ik)->Num << ":'" << (*ik)->Sym << "' ";
	}
	cout << endl << endl;


	/* 5. Generujemy drzewo: usuwamy pierwsze 2 elementy i tworzymy nowy według ich sumy. Robimy to dopóki nie osiągniemy korzenia */
	while (L.size() != 1) {	// Uruchomoiamy pętlę dopóki liśta ma więcej niż jeden element (usuwamy po jednemu elementu)
		L.sort(comparePtr());	// Sortujemy od mniejszego Num do większego
		Node *SonUp = L.front();	// Pomocnicza zmienna - pierwszy element listy
		L.pop_front();				// Usuwamy pierwszy element, na go miejsce łożymy drugi
		Node *SonDn = L.front();	// Pomocnicza zmienna - nowy pierwszy element listy 
		L.pop_front();				// Usuwamy go z listy
									/* W wyniku usunięliśmy dwa pierwszych elementa, ale zapamiętaliśmy ich w zmiennych SonUp i SonDn */


									/* Tworzymy rodzica usuniętych elementów */
		Node *Parent = new Node(SonUp, SonDn);
		/* Parametry rodzica:
		- *Up - wskaźnik na SonUp
		- *Dn - wskaźnik na SonDn
		- Num - suma SonUp.Num + SonDn.Num
		- Sym jest równy 0
		*/
		L.push_back(Parent);	// Łożymy rodzica do listy
	}


	// Ostatni element - korzenie drzewa 
	Node *Root = L.front();


	/* 6. Wyświetlamy drzewo */
	cout << "3. The Huffman Tree:" << endl;
	printTree(Root, 0);
	cout << endl;


	/* 7. Generujemy kody dla symboli */
	buildCodeTable(Root);


	/* 8. Wyświetlamy kody */
	cout << "4. The resulting symbol code table using the Huffman algorithm:" << endl;
	map<char, vector<bool> >::iterator il;
	for (il = _Table.begin(); il != _Table.end(); il++) {
		cout << "'" << il->first << "' = ";
		for (uint i = 0; i < il->second.size(); i++) {
			cout << il->second[i];
		}
		cout << endl;
	}
	cout << endl;


	/* 9. Wyświetlamy kod binarny (zakodowany tekst wejściowy) */
	cout << "5. The output binary code of the text, encoded using the Huffman algorithm:" << endl;
	int Length = 0;	// Długość kodu
	for (int i = 0; i < S.length(); i++) { // Prezbieramy tekst wejściowy
		char Ch = S[i];	// Bierzemy symbol
		vector<bool> Out = _Table[Ch];	// Tablica Out ma w sobi kod binarny Ch
		for (int j = 0; j < Out.size(); j++) { // Wyświetlamy '0' i '1' tablicy Out
			cout << Out[j];
			Length++; // Liczymy długość kodu wyjściowego
		}
	}
	cout << endl << endl;
	/* 10. Wyświetlamy długość kodu wyjściowego */
	cout << "Length of output code: " << Length << " bit" << endl;
	cout << endl;
}


/* Tworzymy funkcję, która wyświetla drzewo Huffmana. Potrzebujemy tą funkcję w funkcji encoding(). Posiada 2 argumenty:
*root - wskaźnik na węzeł; n - licznik rekursji. W wyniku otrzymujemy wyświetlone drzewo */
void printTree(Node *root, int n)
{
	if (root != NULL) {
		printTree(root->Up, n + 1);
		for (int i = 0; i < n; i++) {
			cout << "     ";
		}
		if (root->Sym) {
			cout << root->Num << ":'" << root->Sym << "' " << endl;
		}
		else {
			cout << root->Num << endl;
		}
		printTree(root->Dn, n + 1);
	}
}


/* Tworzymy funkcję, która generuje kody dla symboli. Algorytm generowania tego kodu: zaczynamy od korzenia.
Kiedy idziemy do góry, zapisujemy do kodu '1', kiedy do dołu - '0'. *root - wskaźnik na węzeł. Jeśli w węzłu stoi symbol -
kończymy ruch i zapamiętujemy symbol. Wracamy do poprzedniego węzłu i idziemy w inną strony dopóki nie znajdziemy symbol */
void buildCodeTable(Node *root)
{
	/* Idziemy od węzla w dół */
	if (root->Dn != NULL) {  // Jeśli jest dolne dziecko, to
		_Code.push_back(0); // 1 - w tablicę globalną _Code wpisujemy '0'
		buildCodeTable(root->Dn); // 2 - rekursja z nowym węzłem, który przeszliśmy
	}
	/* Idziemy od węzla w górę */
	if (root->Up != NULL) {	// Jeśli jest górne dziecko, to
		_Code.push_back(1);	// 1 - w tablicę globalną _Code wpisujemy '1'
		buildCodeTable(root->Up); // 2 - rekursja z nowym węzłem, który przeszliśmy
	}
	if ((root->Up == NULL) && (root->Dn == NULL)) { // Jeśli węzeł kończy się symbolem, to
		_Table[root->Sym] = _Code; // . . . zapisujemy w tablicę globalną otrzymany kod z tablicy _Code
	}
	if (_Code.size()) { _Code.pop_back(); }		// Usuwamy ostatni bit z listy _Code (np., było 10110, otrzymujemy 1011)
												/* W wyniku tablica _Code staje pustą, a tablica map _Table będzie wypełniona */
}


int main()
{
	srand((unsigned)time(NULL));
	cout << "Huffman coding using 'greedy algorithms': " << endl;
	encoding();
	cout << endl;
	system("pause");
	return 0;
}

