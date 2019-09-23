#include<iostream>
#include<random>
#include<ctime>

using namespace std;

class Node
{
private:
	int data = 0;
	Node *left;
	Node *right;

public:
	void wstawicNode(int v)
	{
		if (data == 0)
			data = v;
		else if (data < v)
			leftInsert(v);
		else
			rightInsert(v);
	}

	void drukuj()
	{
		if (left != NULL)
			left->drukuj();

		cout << data << " ";

		if (right != NULL)
			right->drukuj();
	}

	void leftInsert(int* v)
	{
		if (left->data == 0)
			left->data = v;
		else if (left->data < v)
			leftInsert(v);
		else
			rightInsert(v);
	}

	void rightInsert(int* v)
	{
		if (right.data == 0)
			right.data = v;
		else if (right->data > v)
			rightInsert(v);
		else
			leftInsert(v);
	}
};

int main()
{
	srand(time(NULL));
	Node myNode;
	
	int n = 0;
	myNode.wstawicNode(10);

	for (int i = 0; i < 10; i++)
	{
		n = 1 + (rand() % 10);
		myNode.wstawicNode( n );
	}

	system("pause");
}