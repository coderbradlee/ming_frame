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
		tn=m_root;
		return 0;
	}
	~binaryTree()
	{
		if(m_root)
		{	
			_destroy(m_root);
			m_root=nullptr;
		}
	}
private:
	void _insert(treeNode*& root,int value)
	{
		//std::cout<<value<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		if(root==nullptr)
		{
			root=new treeNode(value);
			return;
		}
		else if(value>root->data)
		{
			_insert(root->right,value);
		}
		else 
		{
			_insert(root->left,value);
		}
	}
	void _inOrder(treeNode* root,callback print)
	{
		//std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
		if(root==nullptr)
			return;
		_inOrder(root->left,print);
		print(root);
		_inOrder(root->right,print);
		
	}
	void _preOrder(treeNode* root,callback print)
	{
		if(root==nullptr)
			return;
		print(root);
		_preOrder(root->left,print);
		_preOrder(root->right,print);
		
	}
	void _destroy(treeNode* node)
	{
		if(node)
		{
			_destroy(node->left);
			_destroy(node->right);
			delete node;
		}

	}
private:
	treeNode* m_root;
};