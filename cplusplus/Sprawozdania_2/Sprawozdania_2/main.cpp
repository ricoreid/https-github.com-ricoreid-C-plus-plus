/*
Create a binary tree that implements the functions of search, insert and delete.
The user should be able to define the number of nodes to create the tree and use any of
the above function to add, delete and search from the tree. When the tree is initialize,
the program should print the created tree and any changes made to the tree thereafter
in a file with the user's name.

*/

#include <iostream>
#include <ctime>
#include "Node.h"
#include <cstring>
#include "Generator.h"

using namespace std;

int main() {

	/* cout <<"Create a binary tree that implements the functions of search, insert and delete.
	The user should be able to define the number of nodes to create the tree and use any of_
		the above function to add, delete and search from the tree.When the tree is initialize
		the program should print the created tree and any changes made to the tree thereafter
		in a file with the user's name. " << endl; */

	//Generator myGenerator;

	srand((unsigned)time(NULL));

	std::cout << "Enter value for root node: ";
	int rtNodeValue = 0;
	std::cin >> rtNodeValue;

	int numNodes = 0;
	int newNode = 0;
	Node myNode(rtNodeValue);


// Type of data entry for each node.
	int option = 2;
	std::cout << endl << "Enter \'1\' manually enter the data. \n"
		"Enter \'2\' automatically generate the data. \n";

	std::cin >> option;

	if (option == 2)
	{
		numNodes = 100; // rand() % 50 + 1;
		for (int i = 0; i < numNodes; i++)
		{
			myNode.insert(rand()%1000+1);
		}
	}
	else if (option == 1)
	{
		std::cout << "Please specify the number of nodes that the tree will consist of: ";
		std::cin >> numNodes;

		std::cout << "Please enter the data for each node:" << endl;
		for (int i = 0; i < numNodes; i++)
		{
			// cout << "\'i\' is: " << i << " numNodes is: " << numNodes << endl;
			std::cout << "Node " << i + 1 << ": ";
			std::cin >> newNode;
			myNode.insert(newNode);
		}
	}
	else
	{
		std::cout << "No such option." << endl;
	}


// Option for manipulating the binary tree
	int opcja = 0;

	std::cout << endl << "Enter \'0\' to exit \n"
		"Enter \'1\' to insert a node \n"
		"Enter \'2\' to delete a node \n"
		"Enter \'3\' to search the tree \n"
		"Enter \'4\' to print the tree  \n"
		<< endl << endl;

	std::cout << "Please choose an option: ";
	std::cin >> opcja;
	int searchOption = 0;
	int printOption = 0;
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	//int val4 = 0;

	while (opcja != 0)
	{
		
		switch (opcja)
		{
		case 0:		// exits the loop
			break;

		case 1:		// insert data into the tree
			std::cout << "Please enter the value: ";
			std::cin >> val1;
			myNode.insert(val1);
			break;

		case 2:		// delete from the tree	
			std::cout << "Please enter the value: ";
			std::cin >> val2;
			myNode.del(val2);
			break;

		case 3:		// search the tree
		{
			std::cout << "Please enter your search value: ";
			std::cin >> val3;
			clock_t tstart = clock();
			if (myNode.searchInOrder(val3))
			{
				std::cout << "Node exists" << endl;
				std::cout << "Time taken: " << (double)(clock() - tstart) / CLOCKS_PER_SEC << "ms" << endl;
			}
			else
			{
				std::cout << "Node does not exist" << endl;
				std::cout << "Time taken: " << (double)(clock() - tstart) / CLOCKS_PER_SEC << "ms" << endl;
			}
			break;
		}

		case 4:		// print the tree
			myNode.printInOrder();
			break;
			
			
		default:
			std::cout << "Input not recognised, please try again." << endl;
		} // end switch block


		std::cout << endl << "Please choose an option: ";
		std::cin >> opcja;
	} // end while loop





	system("PAUSE");
	return 0;

}

