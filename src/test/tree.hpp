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
	void inOrder(callback print)const
	{
		_inOrder(m_root,print);
	}
	void preOrder(callback print)const
	{
		_preOrder(m_root,print);
	}
	int largestBST(treeNode*& tn)
	{
		int count=0;
		int maxcount=0;
		int leftmax,rightmin;
		//_largestBST(m_root,count,maxcount,leftmax,rightmin,tn)
		return maxcount;
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
	bool _largestBST(const treeNode* m_root,int& count,int& maxcount,int& min,int& max,treeNode*& tn)
	{
		if(!m_root)
		{
			return true;
		}

		int leftcount=0;
		int rightcount=0;
		int leftmax=-1,leftmin=-1;
		int rightmin=-1,rightmax=-1;
		count=0;
		if(!_largestBST(m_root->left,leftcount,maxcount,leftmin,leftmax,tn))
		{
			return false;
		}
		if(!_largestBST(m_root->right,rightcount,maxcount,rightmin,rightmax,tn))
		{
			return false;
		}
		
		if((leftmax<m_root->data)&&(rightmin>m_root->data))
		{
			max=std::max(leftmax,m_root->data);
			min=std::min(rightmin,m_root->data);
			count=leftcount+rightcount+1;
			if(count>maxcount)
			{
				maxcount=count;
		//		tn=m_root;
			}
			return true;
		}
		
		return false;
	}
	void _insert(treeNode*& root,int value)
	{
		//std::cout<<value<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		if(root==nullptr)
		{
			root=new treeNode(value);
			return;
		}
		else if(value>(root->data))
		{
			_insert(root->right,value);
		}
		else 
		{
			_insert(root->left,value);
		}
	}
	
	void _inOrder(treeNode* root,callback print)const
	{
		//std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
		// if(root==nullptr)
		// 	return;
		// _inOrder(root->left,print);
		// print(root);
		// _inOrder(root->right,print);
		if(root)
		{
			_inOrder(root->left, print);
			print(root);
			_inOrder(root->right, print);
		}
	}
	void _preOrder(treeNode* root,callback print)const
	{
		// if(root==nullptr)
		// 	return;
		// print(root);
		// _preOrder(root->left,print);
		// _preOrder(root->right,print);
		if(root)
		{
			print(root);
			_preOrder(root->left, print);
			_preOrder(root->right, print);
			
		}
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