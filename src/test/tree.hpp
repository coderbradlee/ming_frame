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
		int nodemax=0,nodemin=0;
		_largestBST(m_root,count,maxcount,nodemin,nodemax,tn);
		return maxcount;
	}
	void reverseTree()
	{
		_reverseTree(m_root);
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
	void _reverseTree(treeNode* root)
	{
		if(!root)
			return;
		std::swap(root->left,root->right);
		_reverseTree(root->left);
		_reverseTree(root->right);

	}
	bool _largestBST(treeNode* root,int& count,int& maxcount,int& nodemin,int& nodemax,treeNode*& tn)
	{
		// count = 0;
		// if(!root)
		// 	return true;
		// int nMin1 = INT_MAX, nMin2 = INT_MAX;
		// int nMax1 = INT_MIN, nMax2 = INT_MIN;
		// int c1, c2;
		// if(!_largestBST(root->left, c1, maxcount, nMin1, nMax1, tn))
		// 	return false;
		// if(!_largestBST(root->right, c2, maxcount, nMin2, nMax2, tn))
		// 	return false;
		// if((root->data < nMax1) || (root->data > nMin2))
		// 	return false;
		// count = c1 + c2 + 1;
		// nodemin = std::min(nMin1, root->data);
		// nodemax = std::max(nMax2, root->data);
		// if(count > maxcount)
		// {
		// 	maxcount = count;
		// 	tn = root;
		// }
		// return true;

		if(!root)
		{
			return true;
		}
		printf("%d %d %d %d %d\n", count,maxcount,nodemin,nodemax,root->data);
		int leftcount=0;
		int rightcount=0;
		int leftmax=INT_MIN,leftmin=INT_MAX;
		int rightmin=INT_MAX,rightmax=INT_MIN;
		count=0;
		if(!_largestBST(root->left,leftcount,maxcount,leftmin,leftmax,tn))
		{
			return false;
		}
		if(!_largestBST(root->right,rightcount,maxcount,rightmin,rightmax,tn))
		{
			return false;
		}
		if((leftmax<(root->data))&&(rightmin>(root->data)))
		{
			nodemax=std::max(rightmax,root->data);
			nodemin=std::min(leftmin,root->data);
			count=leftcount+rightcount+1;
			if(count>maxcount)
			{
				maxcount=count;
				tn=root;
			}
			return true;
			//ret=true;
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