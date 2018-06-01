/*
Create a binary tree that implements the functions of search, insert and delete.
The user should be able to define the number of nodes to create the tree and use any of
the above function to add, delete and search from the tree. When the tree is initialize,
the program should print the created tree and any changes made to the tree thereafter
in a file with the user's name.

*/

#include <iostream>
#include <cstdlib>
#include "Node.h"
#include <cstring>

using namespace std;

int main(){

	/* cout <<"Create a binary tree that implements the functions of search, insert and delete.
	The user should be able to define the number of nodes to create the tree and use any of_
		the above function to add, delete and search from the tree.When the tree is initialize
		the program should print the created tree and any changes made to the tree thereafter
		in a file with the user's name. " << endl; */
	
	int numNodes = 0;
	int newNode = 0;
	Node myNode(10);

	cout << "Please specify the number of nodes that the tree will consist of: ";
	cin >> numNodes;
	cout << "you entered: " << numNodes << endl;
	cout << "Please enter the data for each node:" << endl;
	for (int i = 0; i < numNodes; i++)
	{
		cout << "\'i\' is: " << i << " numNodes is: " << numNodes << endl;
		cout << "Node " << i+1 << ": ";
		cin >> newNode;
		myNode.insert(newNode);
	}

	int opcja = 0;

	cout << endl << "Enter \'0\' to exit \n"
		"Enter \'1\' to insert a node \n"
		"Enter \'2\' to delete a node \n"
		"Enter \'3\' to print the tree \n"
		"Enter \'4\' to search the tree \n"
		<< endl << endl;

	cout << "Please choose an option: ";
	cin >> opcja;

	while (opcja != 0)
	{
		switch (opcja)
		{
		case 0 :
			break;

		case 1 :
			cout << "Please enter the value: ";
			cin >> numNodes;
			myNode.insert(numNodes);
			break;

		case 2 :
			cout << "Please enter the value: ";
			cin >> numNodes;
			myNode.del(numNodes);
			break;

		case 4:
			cout << "Please enter the value: ";
			cin >> numNodes;
			if (myNode.search(numNodes))
				cout << "Node exists" << endl;
			else
				cout << "Node does not exist" << endl;
			break;

		case 3 :
			myNode.printInOrder();
			break;

		default :
			cout << "Input not recognised, please try again." << endl;
		} // end switch block

		cout << endl << "Please choose an option: ";
		cin >> opcja;
	} // end while loop
	




	system("PAUSE");
	return 0;

}

