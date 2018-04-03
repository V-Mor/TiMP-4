#include<vector>
#include<iostream>
#include"Tree.h"
int main()
{
	Tree<int> der(5);
	der.addNode(15, 0);
	der.addNode(15, 1);
	der.addNode(15, 1);
	der.addNode(10, 1);
	der.addNode(15, 3);
	der.addNode(15, 4);
	der.addNode(10, 2);
	der.addNode(15, 5);
	cout << der.getIncNumber(15, 0);
	return 0;
}