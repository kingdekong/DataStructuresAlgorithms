#include<iostream>
#include<vector>
#include <string>
#include "BinarySearchTree.h"
using namespace std;
void test_searchNode(BSTTree<int>* tree, int key)
{
	BSTNode<int>* result = tree->search(key);
	if (nullptr != result)
	{
		cout << "find result value is " << result->value << endl;
	}
	else
	{
		cout << "not found " << endl;
	}
	cout << endl;
}
void test_insertNode(BSTTree<int>* tree, vector<int>& vec)
{
	cout << "insert begin : " << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		tree->insertNode(vec.at(i));
	}
	cout << endl << "insert end " << endl;
	cout << endl;
}

void test_deleteNode(BSTTree<int>* tree, int key)
{
	tree->deleteNode(key);
	cout << endl;
}

void test_printTree(BSTTree<int>* tree)
{
	cout << "print BSTTree:" << endl;
	tree->printNode();
	cout << endl;
}

void printOriginalData(vector<int>& vec)
{
	cout << "vec data begin : " << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " " << vec.at(i) << " ";
	}
	cout << endl << "vec data end  " << endl;
	cout << endl;
}


void test_mininum(BSTTree<int>* tree)
{
	cout << " BSTTree mininum value: " << tree->minimum() << endl;
	cout << endl;
}


void test_maxinum(BSTTree<int>* tree)
{
	cout << " BSTTree maxinum value: " << tree->maximum() << endl;
	cout << endl;
}

void test_successor(BSTTree<int>* tree, int key)
{
	BSTNode<int>* result = tree->search(key);
	if (nullptr != result)
	{
		BSTNode<int>* successorNode = tree->successor(result);
		if (nullptr != successorNode)
		{
			cout << "find: " << key << " successor value is " << successorNode->value << endl;
		}
		else
		{
			cout << "find: " << key << " successor value is NULL " << endl;
		}
	}
	else
	{
		cout << "not found " << endl;
	}
	cout << endl;
}


void test_predecessor(BSTTree<int>* tree, int key)
{
	BSTNode<int>* result = tree->search(key);
	if (nullptr != result)
	{
		BSTNode<int>* predecessorNode = tree->predecessor(result);
		if (nullptr != predecessorNode) {
			cout << "find: " << key << " predecessor value is " << predecessorNode->value << endl;
		}
		else {
			cout << "find: " << key << " predecessor value is NULL " << endl;
		}

	}
	else
	{
		cout << "not found " << endl;
	}
	cout << endl;
}

int main() {
	//vector<int> dataVec{ 7,3,11,1,5,9,13,0,2,4,6,8,10,12,14 };
	vector<int> dataVec{ 7,3,11,1,5,9,13,2,4,6,8,10,12,14 };
	printOriginalData(dataVec);

	BSTTree<int>* bstTree = new BSTTree<int>();
	test_insertNode(bstTree, dataVec);
	test_printTree(bstTree);

	test_searchNode(bstTree, 11);

	test_mininum(bstTree);
	test_maxinum(bstTree);


	test_successor(bstTree, 0);
	test_predecessor(bstTree, 0);

	test_successor(bstTree, 14);
	test_predecessor(bstTree, 14);

	test_deleteNode(bstTree, 1);
	test_printTree(bstTree);


	system("pause");
	return 0;
}
