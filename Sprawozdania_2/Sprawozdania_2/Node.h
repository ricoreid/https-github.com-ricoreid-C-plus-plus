#include <iostream>
#include <cstdlib>

#ifndef NODE_H
#define NODE_H

class Node
{

	public:
		Node(int);
		~Node();
		bool search(int);
		void insert(int);
		void del(int);
		void printInOrder();

	private:
		Node *left = NULL;
		Node *right = NULL;
		int data = 0;
};

#endif

