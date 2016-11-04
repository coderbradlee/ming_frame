#pragma once
typedef struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode():data(0),left(nullptr),right(nullptr){}
	TreeNode(int value):data(value),left(nullptr),right(nullptr){}
	~TreeNode(){delete left;left=nullptr;delete right;right=nullptr;}
}treeNode;
class binaryTree
{
public:
	typedef std::function<void(treeNode*)> callback;
	binaryTree():m_root(nullptr){}
	void insert(int value)
	{
		_insert(m_root,value);
	}
	void inOrder(callback print)
	{
		_inOrder(m_root,print);
	}
	void preOrder(callback print)
	{
		_preOrder(m_root,print);
	}
	int largestBST(treeNode*& tn)
	{
		
	}
private:
	void _insert(treeNode* root,int value)
	{
		if(root==nullptr)
		{
			root=new treeNode(value);
		}
		else if(value>root->data)
		{
			insert(root->right,value);
		}
		else 
		{
			insert(root->left,value);
		}
	}
	void _inOrder(treeNode* root,callback print)
	{
		if(root==nullptr)
			return;
		if(root->left)
		{
			_inOrder(root->left,print);
		}
		print(root);
		if(root->right)
		{
			_inOrder(root->right,print);
		}
	}
	void _preOrder(treeNode* root,callback print)
	{
		if(root==nullptr)
			return;
		if(root->left)
		{
			_preOrder(root->left,print);
		}
		print(root);
		if(root->right)
		{
			_preOrder(root->right,print);
		}
	}
	
private:
	treeNode* m_root;
};