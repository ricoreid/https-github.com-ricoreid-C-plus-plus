#include<iostream>
#include<cstdlib>
#include<cstring>
#include<list>

using namespace std;

void addFront(list<int>& lista, int wal)
{
	lista.push_back(wal);
}
void printLista(list<int> lista)
{
	for (list<int>::iterator i = lista.begin(); i != lista.end(); ++i)
	{
		cout << *i << endl;

	}
}
void clearLista(list<int>& lista)
{
	lista.clear();
	printLista(lista);
	cout << "list cleared" << endl;
}
int main()
{
	list<int> tableList;
	int n = sizeof(tableList);
	int val = 0;

	tableList.push_front(34);

	// drukuj lista
	printLista(tableList);
	
	// dodac elementu do lista
	cout << "Enter a value: ";
	cin >> val;
	addFront(tableList, val);
	
	// drukuj lista
	printLista(tableList);



	system("pause");
	
}