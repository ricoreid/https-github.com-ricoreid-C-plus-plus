#include "Node.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Node::Node(int d)
{
	data = d;
}
Node::~Node() {


}
bool Node::search(int val) {

	if (val == data)
	{
		return true;

	}
	else if (val < data)
	{
		if (left == NULL)
			return false;
		else
			return left->search(val);
	}
	else
	{
		if (right == NULL)
			return false;
		else
			return right->search(val);
	}

}
void Node::insert(int val) {


	if (val <= data)
	{

		if (left == NULL)
			left = new Node(val);
		else
			left->insert(val);
	}
	else
	{
		if (right == NULL)
			right = new Node(val);
		else
			right->insert(val);
	}

}
void Node::del(int val) {

	if (val <= data)
	{
		if (val == left->data)
			left = NULL;
		else
			left->del(val);
	}
	else
	{
		if (val == right->data)
			right = NULL;
		else
			right->del(val);
	}
}
void Node::printInOrder()
{
	if (left != NULL)
		left->printInOrder();

	cout << data << " ";

	if (right != NULL)
		right->printInOrder();
}
