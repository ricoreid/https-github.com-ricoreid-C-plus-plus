#include <iostream>
#include <cstdlib>

#ifndef NODE_H
#define NODE_H

class Node
{

	public:
		Node(int);
		~Node();
		bool searchInOrder(int);
		void insert(int);
		void del(int);
		void printInOrder();

	private:
		int data = 0;
		Node *left = NULL;
		Node *right = NULL;
};

#endif

