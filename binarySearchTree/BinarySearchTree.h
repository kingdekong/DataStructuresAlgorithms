#ifndef _BINARY_SERACH_TREE_HPP_
#define _BINARY_SERACH_TREE_HPP_

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template<typename T>
class BSTNode
{
public:
	BSTNode(T val, BSTNode* p, BSTNode* left, BSTNode* right) :
		value(val), parent(p), leftChild(left), rightChild(right) {}
public:
	T value;
	BSTNode* parent;
	BSTNode* leftChild;
	BSTNode* rightChild;
};

template<typename T>
class BSTTree {
private:
	BSTNode<T>* mRoot; //�����
public:
	//�鿴BSTTree�Ƿ���ĳ��ֵ
	BSTNode<T>* search(T key);
	//����BSTNode
	void insertNode(T key);
	//ɾ��BSTNode
	void deleteNode(T key);

	//���ҽ����ĺ�̽�㣮�������ң�������������ֵ���ڸý�㣢�ģ���С��㣢
	BSTNode<T>* successor(BSTNode<T>* node);

	//���ҽ�����ǰ����㣮�������ң�������������ֵС�ڸý�㣢�ģ�����㣢
	BSTNode<T>* predecessor(BSTNode<T>* node);

	//������С��㣺������С���ļ�ֵ
	T minimum();

	//��������㣺���������ļ�ֵ
	T maximum();

	//��ӡBSTNode
	void printNode();

private:
	//�鿴BSTTree�Ƿ���ĳ��ֵ
	BSTNode<T>* search(BSTNode<T>*& root, T key) const;
	//����BSTNode
	void insertNode(BSTNode<T>*& root, BSTNode<T>* insNode);

	//ɾ��BSTNode, ����ֵpos��1 �����̰汾��0����ǰ���汾
	BSTNode<T>* deleteNode(BSTNode<T>*& root, BSTNode<T>* delNode, bool pos);
	//ɾ��BSTNode ��̰汾
	BSTNode<T>* deleteNodeSuccessor(BSTNode<T>*& root, BSTNode<T>* delNode);
	//ɾ��BSTNode ǰ���汾
	BSTNode<T>* deleteNodePredecessor(BSTNode<T>*& root, BSTNode<T>* delNode);

	//������С��㣺������С���ļ�ֵ
	BSTNode<T>* minimum(BSTNode<T>* tree);

	//��������㣺���������ļ�ֵ
	BSTNode<T>* maximum(BSTNode<T>* tree);

	//��ӡBSTNode
	void printNode(BSTNode<T>* tree, T key, int direction);
};

//public: beigin

template<typename T>
BSTNode<T>* BSTTree<T>::search(T key)
{
	return search(mRoot, key);
}

template<typename T>
void BSTTree<T>::insertNode(T key)
{
	BSTNode<T>* insNode = new BSTNode<T>(key, nullptr, nullptr, nullptr);
	if (nullptr == insNode)
	{
		return;
	}
	insertNode(mRoot, insNode);
}

template<typename T>
void BSTTree<T>::deleteNode(T key)
{
	BSTNode<T>* deletResultNode = search(key);
	BSTNode<T>* removeNode = nullptr;
	if (nullptr != deletResultNode)
	{
		removeNode = deleteNode(mRoot, deletResultNode, 0);
		cout << " remove Node value is " << removeNode->value;
	}
	delete removeNode;
}
template<typename T>
BSTNode<T>* BSTTree<T>::successor(BSTNode<T>* node)
{
	//��һ�������
	if (node->rightChild != nullptr)
	{
		return minimum(node->rightChild);
	}

	BSTNode<T>* tmpParentNode = node->parent;
	//����ѭ��node�����ӽڵ㣬��ѭ��node�����ӽڵ�
	while ((tmpParentNode != nullptr) && (node == tmpParentNode->rightChild))
	{
		node = tmpParentNode;
		tmpParentNode = tmpParentNode->parent;
	}

	if (tmpParentNode != nullptr) {
		return tmpParentNode;
	}
	else
	{
		return (BSTNode<T>*)nullptr;
	}
}
template<typename T>
BSTNode<T>* BSTTree<T>::predecessor(BSTNode<T>* node)
{
	if (nullptr != node->leftChild)
	{
		return maximum(node->leftChild);
	}
	BSTNode<T>* tmpParentNode = node->parent;

	//node�����ӽڵ㣬����Ѱ�ң�ֱ��node�����ӽڵ�
	while ((nullptr != tmpParentNode) && (node == tmpParentNode->leftChild))
	{
		node = tmpParentNode;
		tmpParentNode = tmpParentNode->parent;
	}
	// node�����ӽڵ�
	if (nullptr != tmpParentNode)
	{
		return tmpParentNode;
	}
	else
	{
		return (BSTNode<T>*)nullptr;
	}
}
template<typename T>
T BSTTree<T>::minimum()
{
	BSTNode<T>* resultNode = minimum(mRoot);
	if (nullptr == resultNode)
	{
		return (T)nullptr;
	}
	else
	{
		return resultNode->value;
	}
}
template<typename T>
T BSTTree<T>::maximum()
{
	BSTNode<T>* resultNode = maximum(mRoot);
	if (nullptr == resultNode)
	{
		return (T)nullptr;
	}
	else
	{
		return resultNode->value;
	}
}
template<typename T>
void BSTTree<T>::printNode()
{
	printNode(mRoot, mRoot->value, 0);
}

//public: end


//private: beigin

template<typename T>
BSTNode<T>* BSTTree<T>::search(BSTNode<T>*& root, T key) const
{
	if (nullptr == root || key == root->value)
	{
		return root;
	}
	if (key < root->value)
	{
		return search(root->leftChild, key);
	}
	else
	{
		return search(root->rightChild, key);
	}
}

template<typename T>
void BSTTree<T>::insertNode(BSTNode<T>*& root, BSTNode<T>* insNode)
{
	BSTNode<T>* tmpParentNode = root;
	BSTNode<T>* insertNodePositon = nullptr;
	//���ڵ㲻Ϊ��,�������ж�insNodeӦ�ò����λ��
	while (tmpParentNode != nullptr)
	{
		insertNodePositon = tmpParentNode;

		if (insNode->value < tmpParentNode->value)
		{
			tmpParentNode = tmpParentNode->leftChild;
		}
		else
		{
			tmpParentNode = tmpParentNode->rightChild;
		}
	}
	// ����˫�����ӹ�ϵ��insNode�ĸ��ڵ�ָ���丸���丸���ӽڵ�ָ��insNode
	insNode->parent = insertNodePositon;
	//���ڵ�Ϊ��
	if (nullptr == insertNodePositon)
	{
		root = insNode;
	}
	else if (insNode->value < insertNodePositon->value)
	{
		insertNodePositon->leftChild = insNode;
	}
	else
	{
		insertNodePositon->rightChild = insNode;
	}
}

template<typename T>
BSTNode<T>* BSTTree<T>::deleteNode(BSTNode<T>*& root, BSTNode<T>* delNode, bool pos)
{
	if (pos)
	{
		return deleteNodeSuccessor(root, delNode);
	}
	else
	{
		return deleteNodePredecessor(root, delNode);
	}
}

template<typename T>
BSTNode<T>* BSTTree<T>::deleteNodeSuccessor(BSTNode<T>*& root, BSTNode<T>* delNode)
{
	//�ҵ�Ҫɾ����Node������ڵ㣺���ڵ���ߺ�̽ڵ�
	BSTNode<T>* replaceNode = nullptr;
	BSTNode<T>* replaceNodeChildNode = nullptr;
	if (nullptr == delNode->leftChild || nullptr == delNode->rightChild)
	{
		replaceNode = delNode; //ɾ������Ҷ�ӽ�������ֻ��һ���ӽڵ�Ľ��
	}
	else
	{
		replaceNode = successor(delNode);
	}

	if (nullptr != replaceNode->leftChild)
	{
		replaceNodeChildNode = replaceNode->leftChild;
	}
	else
	{
		replaceNodeChildNode = replaceNode->rightChild;
	}

	if (nullptr != replaceNodeChildNode)
	{
		replaceNodeChildNode->parent = replaceNode->parent;
	}

	if (nullptr == replaceNode->parent)
	{
		root = replaceNodeChildNode;
	}
	else if (replaceNode == replaceNode->parent->leftChild)//���
	{
		replaceNode->parent->leftChild = replaceNodeChildNode;
	}
	else
	{
		replaceNode->parent->rightChild = replaceNodeChildNode;
		cout << " here  here " << endl;
	}

	if (delNode != replaceNode)
	{
		delNode->value = replaceNode->value;
		cout << " here delNode " << delNode->value << endl;
	}
	cout << " here replaceNode " << replaceNode->value << endl;
	return replaceNode;
}

template<typename T>
BSTNode<T>* BSTTree<T>::deleteNodePredecessor(BSTNode<T>*& root, BSTNode<T>* delNode)
{
	BSTNode<T>* replaceNode = nullptr;
	BSTNode<T>* replaceNodeChildNode = nullptr;
	if (nullptr == delNode->leftChild || nullptr == delNode->rightChild)
	{
		replaceNode = delNode;//���1��2��ɾ������Ҷ�ӽڵ������ֻ��һ���ӽڵ�Ľ��
	}
	else
	{
		replaceNode = predecessor(delNode);//���3
	}

	if (nullptr != replaceNode->leftChild)
	{
		replaceNodeChildNode = replaceNode->leftChild;
	}
	else
	{
		replaceNodeChildNode = replaceNode->rightChild;
	}

	if (nullptr != replaceNodeChildNode)
	{
		replaceNodeChildNode->parent = replaceNode->parent;
	}

	if (nullptr == replaceNode->parent)
	{
		replaceNode = replaceNodeChildNode;
	}
	else if (replaceNode == replaceNode->parent->leftChild)
	{
		replaceNode->parent->leftChild = replaceNodeChildNode;
	}
	else
	{
		replaceNode->parent->rightChild = replaceNodeChildNode;
	}

	if (delNode != replaceNode)
	{
		if (nullptr != replaceNode) {
			delNode->value = replaceNode->value;
		}
	}

	return replaceNode;
}

template<typename T>
BSTNode<T>* BSTTree<T>::minimum(BSTNode<T>* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}
	while (tree->leftChild != nullptr)
	{
		tree = tree->leftChild;
	}
	return tree;
}

template<typename T>
BSTNode<T>* BSTTree<T>::maximum(BSTNode<T>* tree)
{
	if (nullptr == tree)
	{
		return nullptr;
	}
	while (nullptr != tree->rightChild) {
		tree = tree->rightChild;
	}
	return tree;
}

template<typename T>
void BSTTree<T>::printNode(BSTNode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0) {
			cout << setw(2) << tree->value << " is root" << endl;
		}
		else {
			cout << setw(2) << tree->value << " is " << setw(2) <<
				key << "'s " << setw(12) <<
				(direction == 1 ? "right child" : "left child") << endl;
		}
		printNode(tree->leftChild, tree->value, -1);
		printNode(tree->rightChild, tree->value, 1);
	}
}

//private: end

#endif // _BINARY_SERACH_TREE_HPP_