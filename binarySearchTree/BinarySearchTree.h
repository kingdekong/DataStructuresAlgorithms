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
	BSTNode<T>* mRoot; //根结点
public:
	//查看BSTTree是否有某个值
	BSTNode<T>* search(T key);
	//插入BSTNode
	void insertNode(T key);
	//删除BSTNode
	void deleteNode(T key);

	//查找结点ｘ的后继结点．即，查找＂二叉树中数据值大于该结点＂的＂最小结点＂
	BSTNode<T>* successor(BSTNode<T>* node);

	//查找结点ｘ的前驱结点．即，查找＂二叉树中数据值小于该结点＂的＂最大结点＂
	BSTNode<T>* predecessor(BSTNode<T>* node);

	//查找最小结点：返回最小结点的键值
	T minimum();

	//查找最大结点：返回最大结点的键值
	T maximum();

	//打印BSTNode
	void printNode();

private:
	//查看BSTTree是否有某个值
	BSTNode<T>* search(BSTNode<T>*& root, T key) const;
	//插入BSTNode
	void insertNode(BSTNode<T>*& root, BSTNode<T>* insNode);

	//删除BSTNode, 布尔值pos：1 代表后继版本，0代表前驱版本
	BSTNode<T>* deleteNode(BSTNode<T>*& root, BSTNode<T>* delNode, bool pos);
	//删除BSTNode 后继版本
	BSTNode<T>* deleteNodeSuccessor(BSTNode<T>*& root, BSTNode<T>* delNode);
	//删除BSTNode 前驱版本
	BSTNode<T>* deleteNodePredecessor(BSTNode<T>*& root, BSTNode<T>* delNode);

	//查找最小结点：返回最小结点的键值
	BSTNode<T>* minimum(BSTNode<T>* tree);

	//查找最大结点：返回最大结点的键值
	BSTNode<T>* maximum(BSTNode<T>* tree);

	//打印BSTNode
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
	//第一种情况：
	if (node->rightChild != nullptr)
	{
		return minimum(node->rightChild);
	}

	BSTNode<T>* tmpParentNode = node->parent;
	//不进循环node是左子节点，进循环node是右子节点
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

	//node是左子节点，向上寻找，直到node是右子节点
	while ((nullptr != tmpParentNode) && (node == tmpParentNode->leftChild))
	{
		node = tmpParentNode;
		tmpParentNode = tmpParentNode->parent;
	}
	// node是右子节点
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
	//根节点不为空,这里是判断insNode应该插入的位置
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
	// 建立双向连接关系：insNode的父节点指向其父，其父的子节点指向insNode
	insNode->parent = insertNodePositon;
	//根节点为空
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
	//找到要删除的Node的替代节点：根节点或者后继节点
	BSTNode<T>* replaceNode = nullptr;
	BSTNode<T>* replaceNodeChildNode = nullptr;
	if (nullptr == delNode->leftChild || nullptr == delNode->rightChild)
	{
		replaceNode = delNode; //删除的是叶子结点或者是只有一个子节点的结点
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
	else if (replaceNode == replaceNode->parent->leftChild)//后继
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
		replaceNode = delNode;//情况1或2，删除的是叶子节点或者是只有一个子节点的结点
	}
	else
	{
		replaceNode = predecessor(delNode);//情况3
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