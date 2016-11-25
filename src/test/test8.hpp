#pragma once
#include <boost/unordered_map.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <execinfo.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <random>
#include "tree.hpp"
namespace test8_namespace
{
void inpost2pre(std::string in,std::string post)
{
	if(in.length()<1||post.length()<1)
	{
		return;
	}
	std::cout<<post[post.length()-1]<<std::endl;
	if(in.length()==1||post.length()==1)
	{	
		return;
	}
	
	int i=in.find(post[post.size()-1]);//i=4
	std::cout<<i<<std::endl;
	if(i!=std::string::npos)
	{
		int len=in.size()-i-1;
		inpost2pre(in.substr(0,i),post.substr(0,i));
		inpost2pre(in.substr(i+1,len),post.substr(post.size()-1-len,len));
	}
}
void test_inpost2pre()
{
	std::string post="AEFDHZMG";
	std::string in="ADEFGHMZ";
	inpost2pre(in,post);
}
void print(treeNode* p)
{
	std::cout<<p->data<<" ";
}
void change(treeNode* p)
{
	std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_y(0,100);  
	auto dice_y= std::bind(dis_y,gen);
	p->data=dice_y();
}
void test_largestBST()
{
	binaryTree b;
	b.insert(4);
	b.insert(2);
	b.insert(1);
	b.insert(3);
	b.insert(6);
	b.insert(5);
	b.insert(7);
	b.inOrder(change);
	b.inOrder(print);
	std::cout<<std::endl<<"----------------------"<<std::endl;
	b.preOrder(print);
	std::cout<<std::endl<<"----------------------"<<std::endl;
	treeNode* ret;
	int count=b.largestBST(ret);
	std::cout<<count<<":"<<ret->data<<std::endl;
}
int catalan(int n)
{
	std::vector<int> dp(n+1,0);
	dp[0]=1;
	dp[1]=1;
	for(int i=2;i<=n;++i)
	{
		// int len=0;
		// if(i%2==0)
		// {
		// 	len=i/2;
		// }
		// else
		// 	len=i/2+1;
		for(int j=0;j<i;++j)
		{
			dp[i]+=dp[j]*dp[i-1-j];
		}
	}
	// for(auto& i:dp)
	// {
	// 	std::cout<<i<<" ";
	// }
	// std::cout<<std::endl;
	return dp[n];
}
void catalan(int n,std::vector<std::string>& ret)
{
	if(n==0)
	{
		ret.push_back("");
		return;
	}
	if(n==1)
	{
		ret.push_back("()");
		return;
	}

	for(int i=0;i<n;++i)
	{
		std::vector<std::string> temp1;
		std::vector<std::string> temp2;
		catalan(i,temp1);
		catalan(n-i-1,temp2);
		
		for(int j=0;j<temp1.size();++j)
		{
			for(int k=0;k<temp2.size();++k)
			{
				ret.push_back(temp1[j]+"("+temp2[k]+")");
			}
		}
	}
}
void test_catalan()
{
	int n=catalan(5);
	std::cout<<n<<std::endl;
	std::vector<std::string> result;
	catalan(5,result);
	for(int i=0;i<result.size();++i)
	{
		//printf("%d: %s\n",i,result[i]);
		std::cout<<i<<": "<<result[i]<<std::endl;
	}
}
int longestKsubstring(const std::string& str,int len)
{
	int size=str.size();
	std::set<char> separateChar;
	int ml=0;
	int i=0;
	int j=0;
	while(j<size)
	{
		if(separateChar.find(str[j])!=separateChar.end())
		{
			ml=std::max(ml,j-i+1);
			++j;//存在
		}
		else
		{ 
			if(separateChar.size()<len)
			{
				separateChar.insert(str[j]);
				ml=std::max(ml,j-i+1);
				++j;
			}
			else
			{
				//去除一个，增加一个
				int index=i;
				for(int k=i;k<j;++k)
				{
					if(str[k]==str[i])
					{
						index=k;
					}
				}
				separateChar.erase(str[i]);
				i=index+1;
				separateChar.insert(str[j]);
				ml=std::max(ml,j-i+1);
				++j;
			}
			//separateChar.insert(str[j]);
		}
		
		// ml=std::max(ml,j-i+1);
		// ++j;
	}
	for(auto& se:separateChar)
	{
		std::cout<<se<<" ";
	}
	std::cout<<std::endl;
	return ml;
}
void test_longestKsubstring()
{
	 //std::string str="edbaecacaceac";
	std::string str="eceba";
	int len=longestKsubstring(str,3);
	std::cout<<len<<std::endl;
}
class unionFindSet
{
public:
	unionFindSet(int n):m_size(n),m_parents(n,0)
	{
		for(int i=0;i<n;++i)
		{
			m_parents[i]=i;
		}
	}
	int finds(int i)
	{
		if(i<0||i>=m_size)
		{
			return -1;
		}
		int root=i;
		while(root!=m_parents[root])
		{
			root=m_parents[root];
		}
		while(i!=root)
		{
			int temp=m_parents[i];
			m_parents[i]=root;
			i=temp;
		}
		return root;
	}
	void unions(int i,int j)
	{
		if(i<0||i>=m_size||j<0||j>=m_size)
		{
			return;
		}
		int findi=finds(i);
		int findj=finds(j);
		if(findi!=findj)
		{
			m_parents[findi]=findj;
		}
	}
	void print()
	{
		for(auto& i:m_parents)
		{
			std::cout<<i<<" ";
		}
		std::cout<<std::endl;
	}
private:
	int m_size;
	std::vector<int> m_parents;
};

void test_unionFindSet()
{
	const int N=10;
	unionFindSet u(N);
	u.unions(2,6);
	u.unions(5,6);
	u.unions(1,8);
	u.unions(2,9);
	u.unions(5,3);
	u.unions(4,8);
	u.unions(4,0);
	for(int i=0;i<N;++i)
	{
		u.finds(i);
	}
	u.print();
}
void print(const std::vector<int>& v)
{
	for(auto& i:v)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl<<"---------------------"<<std::endl;
}
void dijkstra(const std::vector<std::vector<int>>& v,std::vector<bool>& choiced,std::vector<int>& dist,std::vector<int>& pre)
{
	int size=v.size();
	//dist[0]=0;//到自己的距离
	//计算0点到其他节点的距离
	for(int i=0;i<size;++i)
	{
		dist[i]=v[0][i];
	}
	int choicedSize=0;
	int minIndex=0;
	int minValue=dist[0];
	while(choicedSize<size)
	{
		minValue=INT_MAX;
		minIndex=size;
		for(int i=0;i<size;++i)
		{
			if(!choiced[i])
			{
				if(dist[i]<minValue)
				{
					minValue=dist[i];
					minIndex=i;
				}
			}
		}
		
		if((minIndex<size)&&(!choiced[minIndex]))
		{
			for(int i=0;i<size;++i)
			{
				//dist[i]=std::min(dist[i],dist[minIndex]+v[minIndex][i]);
				//std::cout<<minIndex<<":"<<i<<":"<<dist[i]<<std::endl;
				if(dist[i]>(dist[minIndex]+v[minIndex][i]))
				{
					dist[i]=dist[minIndex]+v[minIndex][i];
					pre[i]=minIndex;
				}
			}
			choiced[minIndex]=true;
		}	
		++choicedSize;
		//std::cout<<minIndex<<":"<<i<<":"<<dist[i]<<std::endl;
		//print(dist);
	}
}
void findRoute(int from,int to,const std::vector<int>& pre)
{
	for(auto& t:pre)
	{
		std::cout<<t<<" ";
	}
	std::cout<<std::endl;
	int i=to;
	std::stack<int> s;
	s.push(to);
	while(i!=pre[i])
	{
		s.push(pre[i]);
		i=pre[i];
	}
	s.push(from);
	while(!s.empty())
	{
		std::cout<<s.top()<<" ";
		s.pop();
	}
	std::cout<<std::endl;
}
void test_dijkstra()
{
	const int N=7;
	std::vector<std::vector<int>> v(N,std::vector<int>(N,INT_MAX/2));
	v[0][0]=0;v[0][1]=20;v[0][2]=50;v[0][3]=30;
	v[1][1]=0;v[1][2]=25;v[1][5]=70;
	v[2][2]=0;v[2][3]=40;v[2][4]=25;v[2][5]=50;
	v[3][3]=0;v[3][4]=55;
	v[4][4]=0;v[4][5]=10;v[4][6]=70;
	v[5][5]=0;v[5][6]=50;
	v[6][6]=0;
	std::vector<bool> choiced(N,false);
	std::vector<int> dist(N,INT_MAX/2);
	std::vector<int> pre(N,0);
	for(int i=0;i<N;++i)
	{
		pre[i]=i;
	}
	dijkstra(v,choiced,dist,pre);
	print(dist);
	int from=0;
	int to=5;
	findRoute(from,to,pre);
}
void test_out()
{
	test_dijkstra();
	// test_unionFindSet();
	// test_longestKsubstring();
	// test_catalan();
	// test_largestBST();
	// test_inpost2pre();
}
}