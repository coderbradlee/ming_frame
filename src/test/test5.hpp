#pragma once
#include "../log.hpp"
#include "../include.hpp"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/Connector.h>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <muduo/base/LogStream.h>
#include <execinfo.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "tree.hpp"
namespace test5_namespace
{
	int find_min_in_rotated_array(const int* arr,int size)
	{
		int low=0;
		int high=size-1;
		int mid=(low+high)/2;
		while(low<high)
		{

			if(arr[high]<arr[mid])//min in right half
			{
				low=mid+1;
			}
			else if(arr[high]>arr[mid])
			{
				high=mid;
			}
			// else
			// {

			// 	return arr[mid];
			// }
			mid=(low+high)/2;
			std::cout<<low<<":"<<mid<<":"<<high<<std::endl;
		}
		return arr[mid]; 
	}
	void test_find_min_in_rotated_array()
	{
		int arr[]={4,5,6,7,8,2,3};
		std::cout<<find_min_in_rotated_array(arr,7)<<std::endl;
		int arr1[]={44,55,66,7,8,9,10};
		std::cout<<find_min_in_rotated_array(arr1,7)<<std::endl;
	}
    void min_subarray(int* arr,int size)
    {
    	int* sum=new int[size];
    	sum[0]=0;
    	int index=1;
    	for(int i=1;i<size;++i)
    	{
    		sum[i]=sum[i-1]+arr[i];
    		if(sum[i]==0)
    			index=i;
    	}
    	std::sort(sum,sum+size);
    	int min=std::abs(sum[1]-sum[0]);
    	
    	for(int i=1;i<size;++i)
    	{
    		if(std::abs(sum[i]-sum[i-1])<min)
    		{
    			min=std::abs(sum[i]-sum[i-1]);
    			index=i;
    		}
    	}
    	std::cout<<min<<std::endl;
    }
    void find_min_subarray(int* arr,int size)
    {
    	std::vector<std::pair<int,int>> sum(size,std::pair<int,int>(0,0));
    	sum[0]=std::make_pair(0,0);
    	int index=1;
    	for(int i=1;i<size;++i)
    	{
    		sum[i]=std::make_pair(sum[i-1].first+arr[i],i);
    		// sum[i]=sum[i-1]+arr[i];
    		// if(sum[i]==0)
    		// 	index=i;
    	}
    	std::sort(sum.begin(),sum.end(),[](std::pair<int,int> x,std::pair<int,int> y){return x.first<y.first;});
    	int min=std::abs(sum[1].first-sum[0].first);
    	
    	for(int i=1;i<size;++i)
    	{
    		if(std::abs(sum[i].first-sum[i-1].first)<min)
    		{
    			min=std::abs(sum[i].first-sum[i-1].first);
    			index=i;
    		}
    	}

    	std::cout<<sum[index+1].second<<":"<<sum[index].second<<std::endl;
    }
	void test_min_subarray()
	{
		int arr[]={1,-2,3,10,-4,7,2,-5};
		///////////0 1 -1 2 12 8 15 17 12
		//min_subarray(arr,8);
		find_min_subarray(arr,8);
	}
	void max_subarray(int* arr,int size)
	{
		int ret=arr[0];
		int sum=arr[0];
		for(int i=0;i<size;++i)
		{
			if(sum>0)
			{
				sum+=arr[i];
			}
			else
			{
				sum=arr[i];
			}
			ret=std::max(ret,sum);
		}
		std::cout<<ret<<std::endl;
	}
	void find_max_subarray(int* arr,int size)
	{
		int ret=arr[0];
		int sum=arr[0];
		int ret_low_index=0;
		int ret_high_index=0;
		int sum_low_index=0;
		int sum_high_index=0;
		for(int i=0;i<size;++i)
		{
			if(sum>0)
			{
				sum+=arr[i];
				sum_high_index=i;
			}
			else
			{
				sum=arr[i];
				sum_low_index=sum_high_index=i;
			}
			if(ret<sum)
			{
				ret=sum;
				ret_low_index=sum_low_index;
				ret_high_index=sum_high_index;
			}
		}
		std::cout<<ret_low_index<<":"<<ret_high_index<<std::endl;
		std::cout<<ret<<std::endl;
	}
	void test_max_subarray()
	{
		int arr[]={1,-2,3,10,-4,7,2,-5};
		///////////0 1 -1 2 12 8 15 17 12
		//max_subarray(arr,8);
		find_max_subarray(arr,8);
	}
	void max_subsequence(int* arr,int size)
	{
		int len=1;
		int max=0;
		int to=0;
		for(int i=0;i<size-1;++i)
		{
			if((arr[i]+1)==arr[i+1])
			{
				++len;
				if(len>max)
				{
					max=len;
					to=i+1;
				}
				//std::cout<<len<<":"<<max<<std::endl;
			}
			else
			{
				//i+=len;
				len=1;
			}
		}
		std::cout<<to+1-max<<":"<<to<<std::endl;
	}
	void test_max_subsequence()
	{
		int arr[]={1,2,39,2,3,4,5,10,22};
		max_subsequence(arr,9);
		int arr2[]={1,2,39,2,3,4,5,6,10};
		max_subsequence(arr2,9);
		int arr3[]={1,2,3,4,5,6,2,39,10};
		max_subsequence(arr3,9);
	}
	void holland(int* arr,int size)
	{
			//begin cur end
		int begin=0;
		int cur=0;
		int end=size-1;
		while(cur<end)
		{
			if(arr[cur]==0)
			{
				if(arr[begin]!=0)
				{
					std::swap(arr[begin],arr[cur]);
				}
				++begin;
				++cur;
			}
			else if(arr[cur]==1)
			{
				++cur;
			}
			else if(arr[cur]==2)
			{
				std::swap(arr[cur],arr[end]);
				--end;
			}
		}
	}
	void test_holland()
	{
		int arr[]={1,2,0,2,1,2,1,0,1};
		holland(arr,9);
		for(auto i:arr)
		{
			std::cout<<i<<" ";
		}
		std::cout<<std::endl;
	}
	typedef struct Bucket
	{
		bool valid;
		int min;
		int max;
		Bucket():valid(false){}
		void add(int n)
		{
			if(!valid)
			{
				min=max=n;
				valid=true;
			}
			else
			{
				if(max<n)
					max=n;
				else if(min>n)
					min=n;
			}
		}
	}bucket;
	int cal_gap(int* arr,int size)
	{
		std::vector<bucket> v(size);
		int max=arr[0];
		int min=arr[0];
		for(int i=1;i<size;++i)
		{
			if(arr[i]>max)
				max=arr[i];
			else if(arr[i]<min)
				min=arr[i];
		}
		int size_of_bucket=(max-min)/size;
		for(int i=0;i<size;++i)
		//arr[i]-min除以桶的大小可得位于哪个桶，桶的大小为max-min/size
		{
			int location=(arr[i]-min)/size_of_bucket;
			if(location>=size)
				location=size-1;
			// bucket b;
			// b.add(arr[i]);
			//v[location]=b;
			v[location].add(arr[i]);
		}
		int j=0;
		int ret=0;
		for(int i=1;i<size;++i)
		{
			if(v[i].valid)
			{
				if(v[i].min-v[j].max>ret)
				{
					ret=v[i].min-v[j].max;
				}	
				j=i;
			}
		}
		for(auto& i:v)
		{
			if(i.valid)
			std::cout<<"["<<i.min<<","<<i.max<<"]"<<std::endl;
		}
		return ret;
	}
	int cal_gap2(int* arr,int size)
	{
		bucket* pbucket=new bucket[size];
		int max=arr[0];
		int min=arr[0];
		for(int i=1;i<size;++i)
		{
			if(max<arr[i])
				max=arr[i];
			else if(min>arr[i])
				min=arr[i];
		}
		int delta=max-min;
		int numbucket;
		for(int i=0;i<size;++i)
		{
			numbucket=(arr[i]-min)*size/delta;
			if(numbucket>=size)
			{
				numbucket=size-1;
			}
			pbucket[numbucket].add(arr[i]);
		}
		int ngap=delta/size;
		int gap;
		int z=0;
		for(int j=1;j<size;++j)
		{
			if(pbucket[j].valid)
			{
				gap=pbucket[j].min-pbucket[z].max;
				if(ngap<gap)
				{
					ngap=gap;
				}
				z=j;
			}
		}
		for(int i=0;i<size;++i)
		{
			if(pbucket[i].valid)
			std::cout<<"["<<pbucket[i].min<<","<<pbucket[i].max<<"]"<<std::endl;
		}
		return ngap;
	}
	void test_cal_gap()
	{
		int arr[]={1,7,14,9,4,13};
		std::cout<<cal_gap(arr,6)<<std::endl;
		int arr2[]={10,7,14,80,4,13,30};
		std::cout<<cal_gap(arr2,7)<<std::endl;
		std::cout<<"----------------"<<std::endl;
		
		std::cout<<cal_gap2(arr,6)<<std::endl;
		
		std::cout<<cal_gap2(arr2,7)<<std::endl;
	}
	void cantor1(std::vector<int> arr,std::vector<int>& ori,int size)
	{
		for(int i=0;i<size;++i)
		{
			for(int j=i+1;j<size;++j)
			{
				if(arr[j]<arr[i])
					++ori[i];
			}
		}
	}
	void cantor2(std::vector<int> arr,std::vector<int>& ori,int size)
	{
		std::vector<int> v(size);
		for(int i=0;i<size;++i)
			v[i]=i+1;
		for(int i=0;i<size;++i)
		{
			ori[i]=v[arr[i]];
			v.erase(v.begin()+arr[i]);
		}
	}
	
	void test_cantor()
	{
		std::vector<int> array{4,6,2,5,3,1};
		std::vector<int> arr{3,4,1,2,1,0};
		std::vector<int> ori(6,0);
		cantor1(array,ori,6);
		
		for(auto i:ori)
		{
			std::cout<<i<<std::endl;
		}
		std::cout<<"-----------------"<<std::endl;
		//ori.clear();
		cantor2(arr,ori,6);
		for(auto i:ori)
		{
			std::cout<<i<<std::endl;
		}
	}
	typedef struct Node
	{
		int data;
		int parent;
		int left;
		int right;
		Node():data(-1),parent(-1),left(-1),right(-1){}
	}node;
	void cal_frequence(const char* str,int* frequence)
	{
		int len=strlen(str);
		for(int i=0;i<len;++i)
		{
			++frequence[str[i]];
		}
	}
	void print_frequence(int *frequence,int N)
	{
		int j=0;
		for(int i=0;i<N;++i)
		{
			if(i=='\t')
			{
				//std::cout<<i<<std::endl;
				frequence[i]=0;
			}
			if(frequence[i]!=0)
			{
				printf("%c:%d ",i,frequence[i]);
				++j;
			}	
			
			if(j!=0&&j%10==0)
			{
				printf("\n");
				j=0;
			}	
		}
		std::cout<<std::endl;
	}
	void cal_exist_char(int* frequence,int N,std::vector<int>& exist_key)
	{
		int j=0;
		for(int i=0;i<N;++i)
		{
			if(frequence[i]!=0)
			{
				frequence[j]=frequence[i];
				++j;
				exist_key.push_back(i);
			}
		}
	}
	void select2min(node* huffmanNode,int N,int& one,int& two)
	{
		//make two is bigger one of one and two
		one=-1;
		two=-1;
		int min1=-1;
		int min2=min1;
		for(int i=0;i<N;++i)
		{
			if((huffmanNode[i].parent)==-1)
			{
				if((one<0)||(huffmanNode[i].data<min1))
				{
					min2=min1;
					two=one;
					min1=huffmanNode[i].data;
					one=i;
				}
				else if((two<0)||(huffmanNode[i].data<min2))
				{
					min2=huffmanNode[i].data;
					two=i;
				}
				//printf("/////////////%d:%d\n",one,two);
			}
		}
	}
	void huffman_code(int* frequence,int N,std::vector<std::vector<char>>& huffman)
	{
		int size=2*N-1;
		node* huffmanNode=new node[size];
		for(int i=0;i<N;++i)
		{
			huffmanNode[i].data=frequence[i];
		}
		int one,two;
		for(int i=N;i<size;++i)
		{
			//choose two minner between 0-i 
			select2min(huffmanNode,i,one,two);
			//printf("/////////////%d\n",i);
			huffmanNode[i].data=huffmanNode[one].data+huffmanNode[two].data;
			huffmanNode[i].left=one;
			huffmanNode[i].right=two;
			huffmanNode[one].parent=i;
			huffmanNode[two].parent=i;
		}
		for(int i=0;i<N;++i)//前N个为叶子节点，需要求编码
		{
			std::vector<char> code;
			int cur=i;
			while(huffmanNode[cur].parent!=-1)
			{
				if(cur==(huffmanNode[huffmanNode[cur].parent].left))
				{
					code.push_back('0');
				}
				else
				{
					code.push_back('1');
				}
				if(cur!=huffmanNode[cur].parent)
					cur=huffmanNode[cur].parent;
				else
				{
					break;
				}
			}
			std::reverse(code.begin(),code.end());
			huffman[i]=code;
		}
	}
	void print_huffman(std::vector<int> exist_key,std::vector<std::vector<char>>& huffman)
	{
		for(int i=0;i<exist_key.size();++i)
		{
			printf("%c:", exist_key[i]);
			for(auto j:huffman[i])
			{
				printf("%c",j);
			}
			printf("\n");
		}
	}
	void test_huffman()
	{
		const int N=256;
		const char str[]="when I was young I'd listen to the radio\
						waiting for my favorite songs\
						when they played I'd sing along, \
						it make me smile.\
						those were such happy times and not so long ago\
						how I wondered where they'd gone.\
						but they're back again just like a long lost friend\
						all the songs I love so well.\
						every shalala every wo'wo\
						still shines.\
						every shing-a-ling-a-ling\
						that they're starting\
						to sing so fine";

		int frequence[N]={0};
		cal_frequence(str,frequence);
		print_frequence(frequence,N);
		std::vector<int> exist_key;
		//存在的字符保存的exist_key中，个数还是保存在frequence里
		cal_exist_char(frequence,N,exist_key);
		//this should be the same with print_frequence
		for(int i=0;i<exist_key.size();++i)
		{
			printf("%c:%d ",exist_key[i],frequence[i]);
			if(i!=0&&i%10==0)
			{
				printf("\n");
			}	
		}
		printf("\n------------------\n");
		std::vector<std::vector<char>> v(exist_key.size());
		huffman_code(frequence,exist_key.size(),v);
		
		print_huffman(exist_key,v);
	}
	void inpre2post(const char* inorder,const char* preorder,int size,char* postorder,int& index)
	{
		if(size<=0)
			return;
		if(size==1)
		{
			postorder[index]=preorder[0];
			++index;
			return;
		}
		char root=preorder[0];
		int inorderIndex=0;
		for(int i=0;i<size;++i)
		{
			if(root==inorder[i])
				inorderIndex=i;
		}
		int right=size-inorderIndex-1;
		inpre2post(inorder,preorder+1,inorderIndex,postorder,index);
		inpre2post(inorder+inorderIndex+1,preorder+size-right,right,postorder,index);
		postorder[index]=root;
		++index;
	}
	void inpre2post(const char* inorder,const char* preorder,int size,char* postorder)
	{
		int index=0;
		inpre2post(inorder,preorder,size,postorder,index);
	}
	void test_inpre2post()
	{
		char preorder[]="GDAFEMHZ";
		char inorder[]="ADEFGHMZ";
		char postorder[8]={0};
		inpre2post(inorder,preorder,8,postorder);
		for(auto i:postorder)
		{
			printf("%c", i);
		}
		printf("\n");
	}
	bool is_post_order(const int* arr,int size)
	{
		int i=size-1;
		if(i<=0)
			return true;
		int root=arr[i];
		int right=size-2;
		while(right>=0)
		{
			if(arr[right]>root)
				--right;
			else
				break;
		}
		int left=0;
		while(left<size-1)
		{
			if(arr[left]<root)
				++left;
			else
				break;
		}
		if(left!=(right+1))
			return false;
		
		bool ileft=is_post_order(arr,left);
		bool iright=is_post_order(arr+left,size-left-1);
		return ileft&&iright;
	}
	void test_is_post_order()
	{
		int arr1[]={1,2,3,4,5};
		int arr2[]={3,5,1,4,2};
		int arr3[]={1,2,5,4,3};
		int arr4[]={5,4,3,2,1};
		std::cout<<is_post_order(arr1,5)<<std::endl;
		std::cout<<is_post_order(arr2,5)<<std::endl;
		std::cout<<is_post_order(arr3,5)<<std::endl;
		std::cout<<is_post_order(arr4,5)<<std::endl;
	}
	void print(treeNode* root)
	{
		printf("%d ", root->data);
	}
	void changeValue(treeNode* tn)
	{
		tn->data=rand()%100;
	}
	void test_tree()
	{
		int arr[]={1,5,2,3,7,4};
		binaryTree bt;
		for(auto& i:arr)
		{
			bt.insert(i);
		}
		bt.inOrder(print);
		printf("\n");
		bt.preOrder(print);
		printf("\n");
		bt.inOrder(changeValue);
		bt.inOrder(print);
		printf("\n");
		bt.preOrder(print);
		printf("\n");
		treeNode* tn;
		int num=bt.largestBST(tn);
		printf("%d %d\n", tn->data,num);
		bt.reverseTree();
		bt.inOrder(print);
		printf("\n");
		bt.preOrder(print);
		printf("\n");
	}
	int allParentheses(int size)
	{
		if(size==0)
			return 1;
		else if(size==1)
			return 1;
		int ret=0;
		for(int i=0;i<size;++i)
		{	
			ret=ret+allParentheses(i)*allParentheses(size-1-i);
		}
		return ret;

	}
	void unionResult(std::vector<std::string>& prefix,std::vector<std::string>& suffix,std::vector<std::string>& out)
	{
		for(auto i:prefix)
			for(auto j:suffix)
			{
				out.push_back(i+"("+j+")");
			}
	}
	void allParentheses(std::vector<std::string>& out,int size)
	{
		if(size==0)
			out.push_back("");
		else if(size==1)
			out.push_back("()");;
		int ret=0;
		for(int i=0;i<size;++i)
		{	
			std::vector<std::string> prefix,suffix;
			allParentheses(prefix,i);
			allParentheses(suffix,size-1-i);
			unionResult(prefix,suffix,out);
		}
	}
	void test_allparentheses()
	{
		const int N=5;
		std::cout<<allParentheses(N)<<std::endl;
		std::cout<<allParentheses(15)<<std::endl;
		std::vector<std::string> out;
		allParentheses(out,5);
		for(int i=0;i<allParentheses(N);++i)
		{
			std::cout<<i<<": "<<out[i]<<std::endl;
		}
	}
	class unionFindSet
	{
	public:
		unionFindSet():m_N(0){}
		unionFindSet(int n):m_N(n),m_parent(n,0)
		{
			for(int i=0;i<m_N;++i)
				m_parent[i]=i;

		}
		~unionFindSet(){}
		
		int find(int i)
		{
			if((i<0)||(i>=m_N))
				return -1;
			int t=i;
			while(i!=m_parent[i])
			{
				i=m_parent[i];
			}
			
			while(t!=m_parent[t])
			{
				int temp=m_parent[t];
				m_parent[t]=i;
				t=temp;
			}
			return i;
		}
		void _union(int i,int j)
		{
			int left=find(i);
			int right=find(j);
			if(left==-1||right==-1)
				return;
			if(left!=right)
			{
				m_parent[left]=right;
			}
		}
		void print()
		{
			for(auto i=0;i<10;++i)
			{
				find(i);
			}
			for(auto i:m_parent)
			{
				//if(i!=0)
				{
					std::cout<<i<<std::endl;
				}
			}
		}
	private:
		int m_N;
		std::vector<int> m_parent;
	};
	void test_unionFindSet()
	{
		unionFindSet ufs(10);
		ufs._union(2,6);
		ufs._union(5,6);
		ufs._union(1,8);
		ufs._union(2,9);
		ufs._union(5,3);
		ufs._union(4,8);
		ufs._union(4,0);
		ufs.print();

	}
	void articulationPoint(
		const std::vector<std::vector<int>>& graph,
		int i,
		int parent,
		int root,
		std::vector<int>& dfn,
		std::vector<int>& low,
		int& n,
		std::vector<bool>& ret)
	{
		dfn[i]=low[i]=n;
		++n;
		int child=0;
		for(int j=0;j<graph.size();++j)
		{
			if(graph[i][j]!=0)
			{
				if(dfn[j]==-1)
				{
					++child;
					articulationPoint(graph,j,i,root,dfn,low,n,ret);
					low[i]=std::min(low[i],low[j]);
					if((i!=root)&&(low[j]>dfn[i]))
						ret[i]=true;
					else if((i==root)&&(child==2))
					{
						ret[i]=true;
						child=0;
					}
				}
				else if(parent!=j)
				{
					low[i]=std::min(low[i],dfn[j]);
				}
			}
		}
	}
	void articulationPoint(const std::vector<std::vector<int>>& graph,std::vector<bool>& ret)
	{
		int N=graph.size();
		//std::cout<<N<<std::endl;
		std::vector<int> dfn(N,-1);
		std::vector<int> low(N,0);
		int root=0;
		int n=0;
		articulationPoint(graph,root,-1,root,dfn,low,n,ret);
	}
	void test_articulationPoint()
	{
		const int N=13;
		std::vector<std::vector<int>> v(N,std::vector<int>(N,0));
		//A B C D E F G H I J K  L  M 
		//0 1 2 3 4 5 6 7 8 9 10 11 12
		v[0][1]=1;v[0][2]=1;v[0][5]=1;v[0][11]=1;
		v[1][0]=1;v[1][2]=1;v[1][3]=1;v[1][4]=1;
		v[1][6]=1;v[1][7]=1;v[1][12]=1;
		v[2][0]=1;v[2][1]=1;
		v[3][1]=1;v[3][4]=1;
		v[4][1]=1;v[4][3]=1;
		v[5][0]=1;
		v[6][1]=1;v[6][7]=1;v[6][8]=1;v[6][10]=1;
		v[7][1]=1;v[7][9]=1;v[7][10]=1;
		v[8][9]=1;
		v[9][11]=1;v[9][12]=1;
		v[10][6]=1;v[10][7]=1;
		v[11][0]=1;v[11][12]=1;
		v[12][1]=1;v[12][9]=1;v[12][11]=1;
		std::vector<bool> ret(N,false);
		articulationPoint(v,ret);
		for(int i=0;i<N;++i)
		{
			if(ret[i])
			{
				printf("%c ",i+'A');
			}
		}
		printf("\n");
	}
	int findNewNode(const std::vector<bool>& choiced,const std::vector<int>& dist)
	{
		int min=INFINITY;
		int minIndex=0;
		for(int i=1;i<dist.size();++i)
		{
			//printf("dist[i]:%d,i:%d\n",dist[i],i );
			if((dist[i]<min)&&(!choiced[i]))
			{
				min=dist[i];
				minIndex=i;
			}	
		}
		return minIndex;
	}
	void dijkstra(
		const std::vector<std::vector<int>>& graph,
		int start,
		std::vector<bool>& choiced,
		std::vector<int>& dist,
		std::vector<int>& pre)
	{
		int size=graph.size();
		{
			//init
			choiced[0]=true;
			for(int i=1;i<size;++i)
			{
				if(graph[0][i]<INFINITY)
				{
					dist[i]=graph[0][i];
				}
			}
		}
		for(int num=0;num<size-1;++num)
		{
			int newNode=findNewNode(choiced,dist);
			choiced[newNode]=true;
			for(int i=0;i<size;++i)
			{	
				int temp=dist[newNode]+graph[newNode][i];
				// printf("%d\n",temp);
				if(temp>0)
				{
					//dist[i]=std::min(dist[i],temp);
                    if(dist[i]>temp)
                    {
                        dist[i]=temp;
                        pre[i]=newNode;
                    }
					printf("pre[%d]=%d,newNode:%d\n",i,pre[i],newNode);
				}		
			}
		}
		for(auto i:pre)
		{
			std::cout<<i<<" ";
		}
        std::cout<<std::endl;
		
	}
	void minPath(int start,int end,const std::vector<int>& pre)
	{
		for(auto i:pre)
		{
			std::cout<<i<<" ";
		}
        std::cout<<std::endl;
		int i=end;
		std::vector<int> path;
		path.push_back(end);
        //--i;
		while((pre[i]!=start)&&(pre[i]!=i))
		{
			i=pre[i];
			path.push_back(i);
		}
		path.push_back(start);
		for(auto it=path.rbegin();it!=path.rend();++it)
			printf("%d ",*it );
		printf("\n");
	}
	void test_dijkstra()
	{
		const int N=7;
		std::vector<std::vector<int>> v(N,std::vector<int>(N,INFINITY));
		v[0][0]=0;v[0][1]=20;v[0][2]=50;v[0][3]=30;
		v[1][1]=0;v[1][2]=25;v[1][5]=70;
		v[2][2]=0;v[2][3]=40;v[2][4]=25;v[2][5]=50;
		v[3][3]=0;v[3][4]=55;
		v[4][4]=0;v[4][5]=10;v[4][6]=70;
		v[5][5]=0;v[5][6]=50;
		v[6][6]=0;
		std::vector<bool> choiced(N,false);
		std::vector<int> dist(N,INFINITY);
		dist[0]=0;//到自己的距离
		//计算0点到其他节点的距离
		std::vector<int> pre(N,-1);
        for(int i=0;i<N;++i)
        {
            pre[i]=i;
        }
		dijkstra(v,0,choiced,dist,pre);
		for(int i=0;i<choiced.size();++i)
		{
			if(choiced[i])
			printf("%d ",i );
		}
		printf("\n");
		for(auto i:dist)
			printf("%d ",i );
		printf("\n");
		for(auto i:pre)
			printf("%d ",i );
		printf("\n");
		//print 0-7 min path
		minPath(0,6,pre);
		minPath(0,2,pre);
	}
	void floyd(const std::vector<std::vector<int>>& graph,
		std::vector<std::vector<int>>& sp,std::vector<std::vector<int>>& next)
	{
		int size=graph.size();
		sp=graph;
		for(int i=0;i<size;++i)
			for(int j=0;j<size;++j)
			{
				next[i][j]=j;
			}
		for(int k=0;k<size;++k)
		{
			for(int i=0;i<size;++i)
				for(int j=0;j<size;++j)
				{
					if(graph[i][j]>graph[i][k]+graph[k][j])
					{
						sp[i][j]=graph[i][k]+graph[k][j];
						next[i][j]=next[i][k];
					}
				}
		}
	}
	void floydMinPath(int start,int end,const std::vector<std::vector<int>>& next)
	{
		std::vector<int> v;
		v.push_back(start);
		int k=next[start][end];
		while(k!=end)
		{
			v.push_back(k);
			k=next[k][end];
		}
		v.push_back(end);
		for(auto i:v)
			printf("%d ", i);
		printf("\n");
	}
	void test_floyd()
	{
		const int N=7;
		std::vector<std::vector<int>> v(N,std::vector<int>(N,INFINITY));
		v[0][0]=0;v[0][1]=20;v[0][2]=50;v[0][3]=30;
		v[1][1]=0;v[1][2]=25;v[1][5]=70;
		v[2][2]=0;v[2][3]=40;v[2][4]=25;v[2][5]=50;
		v[3][3]=0;v[3][4]=55;
		v[4][4]=0;v[4][5]=10;v[4][6]=70;
		v[5][5]=0;v[5][6]=50;
		v[6][6]=0;
		std::vector<std::vector<int>> shortestPath(N,std::vector<int>(N,INFINITY));
		std::vector<std::vector<int>> next(N,-1);
		floyd(v,shortestPath,next);
		
		floydMinPath(0,6,next);
		floydMinPath(0,2,next);
	}
	void test_out()
	{
		test_floyd();
		// test_dijkstra();
		// test_articulationPoint();
		// test_unionFindSet();
		//test_tree();
		//test_is_post_order();
		//test_inpre2post();
		//test_huffman();
		// test_cantor();
		// test_cal_gap();
		//test_holland();
		//test_max_subsequence();
		//test_max_subarray();
		//test_min_subarray();
		//test_find_min_in_rotated_array();
	}
}
