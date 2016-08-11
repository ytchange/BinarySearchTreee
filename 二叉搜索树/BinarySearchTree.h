#pragma once

#include <iostream>
using namespace std;

template<class K,class V>
struct BinarySearchTreeNode
{
	K _key;
	V _value;
	BinarySearchTreeNode<K,V> *_left;
	BinarySearchTreeNode<K,V> *_right;
	BinarySearchTreeNode(const K&key, const V&value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};
template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	~BinarySearchTree()
	{
		_destoryNode(_root);
	}
	//插入数据非递归写法
	bool Insert(const K&key, const V&value)
	{
		if (_root == NULL)
		{
			Node *newNode = new Node(key, value);
			_root = newNode;
			return true;
		}
		Node *cur = _root;
		Node *parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; //当值相同时返回错误
			}
		}
		if (parent->_key > key)
		{
			Node *tmp = new Node(key, value);
			parent->_left = tmp;
		}
		else
		{
			Node *tmp = new Node(key, value);
			parent->_right = tmp;
		}
		return true;
	}
	//插入递归写法
	bool InsertR(const K&key, const V&value)
	{
		return _InsertR(_root, key, value);
	}
	//按照key值查找非递归
	Node* Find(const K&key)
	{
		Node *root = _root;
		while (root)
		{
			if (root->_key < key)
			{
				root = root->_right;
			}
			else if (root->_key>key)
			{
				root = root->_left;
			}
			else
			{
				return root;
			}
		}
		return NULL;
	}
	Node* FindR(const K&key)
	{
		Node *ret = _Find(_root, key);
		return ret;
	}
	//删除非递归
	bool Remove(const K&key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				break;
			}
		}
		if (cur == NULL)
		{
			return false;
		}
		//删除，1.左孩子或者右孩子为空
		//2.左右孩子都不为空
		if (cur->_left == NULL) //左为空
		{
			if (parent == NULL)  //当删除根节点时，那么它的左子树为空，所以要更改根节点
			{
				_root = cur->_right;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
			
			delete cur;
		}
		else if (cur->_right == NULL)//右为空
		{
			if (parent == NULL)  //当删除根节点时，那么它的右子树为空，所以要更改根节点
			{
				_root = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
			delete cur;
		}
		else //左右都不为空
		{
			Node *parent = cur;
			Node *subLeft = cur->_right;
			while (subLeft->_left)  //在cur之后找中序遍历的下一个节点
			{
				parent = subLeft;
				subLeft = subLeft->_left;
			}
			cur->_key = subLeft->_key;
			cur->_value = subLeft->_value;

			if (parent->_right == subLeft) //subleft的位置不同，则修改的情况也不同
			{
				parent->_right = subLeft->_right;
			}
			else
			{
				parent->_left = subLeft->_right;
			}
			delete subLeft;
		}
		return true;
	}
	//删除递归
	bool RemoveR(const K &key)
	{
		return _RemoveR(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	
protected:
	void _InOrder(Node *root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _InsertR(Node *&root, const K &key, const V&value)
	{//巧妙借助引用，当root为空，则创建节点赋给root
		if (root == NULL)
		{
			Node *tmp = new Node(key, value);
			root = tmp;
			return true;
		}
		if (root->_key < key)
		{
			return _InsertR(root->_right, key, value);
		}
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}
	//查找递归
	Node *_Find(Node *root,const K &key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_key < key)
		{
			return _Find(root->_right, key);
		}
		else if (root->_key>key)
		{
			return _Find(root->_left, key);
		}
		else
		{
			return root;
		}
	}
	//删除递归写法
	bool _RemoveR(Node* &root, const K&key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else if (root->_key>key)
		{
			return _RemoveR(root->_left, key);
		}
		else
		{
			Node *del = root;
			if (root->_left == NULL) //左或者右为空
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else //左右都不为空
			{
				Node *parent = root;
				Node *subLeft = root->_right;
				while (subLeft->_left)
				{
					parent = subLeft;
					subLeft = subLeft->_left;
				}
				root->_key = subLeft->_key;
				root->_value = subLeft->_value;

				del = subLeft;
				if (parent->_left == subLeft)
				{
					parent->_left = subLeft->_right;
				}
				else
				{
					parent->_right = subLeft->_right;
				}
			}
			delete del;
			return true;
		}
	}
	void _destoryNode(Node *_root)
	{
		if (_root == NULL)
		{
			delete _root;
			_root = NULL;
			return;
		}
		_destoryNode(_root->_left);
		_destoryNode(_root->_right);
	}
private:
	Node *_root;
};

void insertTest()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BinarySearchTree<int, int> bst;
	for (int i = 0; i <len ; i++)
	{
		//bst.Insert(arr[i], i);
		bst.InsertR(arr[i], i);
	}
	bst.InOrder();
	cout << endl;
	
	bool ret = bst.Remove(9);
	if (ret == true)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" <<  endl;;
	}
	bst.InOrder();
}
void removeTest()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BinarySearchTree<int, int> bst;
	for (int i = 0; i <len; i++)
	{
		//bst.Insert(arr[i], i);
		bst.InsertR(arr[i], i);
	}
	bst.InOrder();
	cout << endl;

	bst.Remove(3);
	bst.InOrder();
	cout << endl;
	bst.Remove(5);
	bst.InOrder();
	cout << endl;
	bst.Remove(9);
	bst.InOrder();
	cout << endl;
	bst.Remove(6);
	bst.InOrder();
	cout << endl;
	bst.Remove(7);
	bst.InOrder();
	cout << endl;
	bst.Remove(8);
	bst.InOrder();
	cout << endl;
}
void removeTestR()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BinarySearchTree<int, int> bst;
	for (int i = 0; i < len; i++)
	{
		//bst.Insert(arr[i], i);
		bst.InsertR(arr[i], i);
	}
	bst.InOrder();
	cout << endl;
	
	bst.RemoveR(5);
	bst.InOrder();
	cout << endl;
	bst.RemoveR(9);
	bst.InOrder();
	cout << endl;
	bst.RemoveR(6);
	bst.InOrder();
	cout << endl;
	bst.RemoveR(7);
	bst.InOrder();
	cout << endl;
	bst.RemoveR(8);
	bst.InOrder();
	cout << endl;
}