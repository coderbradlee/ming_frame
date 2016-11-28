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
void print(int count,const std::vector<int>& arr,const std::vector<std::pair<int,char>>& op,int size)
{
	auto it=op.begin();
	for(int i=0;i<arr.size();++i)
	{
		if(i==arr.size()-1)
		{
			std::cout<<arr[i];
			break;
		}
		std::cout<<arr[i];
		if((it!=op.end())&&(it->first==i))
		{
			std::cout<<it->second;
			++it;
		}
	}
	std::cout<<std::endl;
}
bool calcHundred(const std::vector<int>& arr,int size,int cur,int curSum,int last,std::vector<std::pair<int,char>>& op,int sum,int& count)
{
	if(cur==(size-1))
	{
		// std::cout<<last<<":"<<arr[size-1]<<std::endl;
		last=10*last+arr[size-1];
		// std::cout<<curSum<<":"<<last<<std::endl;
		// std::cout<<op.size()<<std::endl;
		if(op.size()>=1)
		{
			if(((op[op.size()-1].second=='+')&&((curSum+last)==sum))||((op[op.size()-1].second=='-')&&((curSum-last)==sum)))
			{
				++count;
				print(count,arr,op,size);
				return true;
			}
		}
		
		return false;
	}
	last=10*last+arr[cur];
	calcHundred(arr,size,cur+1,curSum,last,op,sum,count);

	bool isAdd=false;
	if(op.size()>=1)
	{
		isAdd=op[op.size()-1].second=='+';
	}
	else
	{
		isAdd=true;
	}
	op.push_back(std::make_pair(cur,'+'));
	calcHundred(arr,size,cur+1,isAdd?curSum+last:curSum-last,0,op,sum,count);
	op.back().second='-';
	calcHundred(arr,size,cur+1,isAdd?curSum+last:curSum-last,0,op,sum,count);
	op.pop_back();
	return count!=0;
}
void test_caLcHundred()
{
	std::vector<int> arr{1,2,3,4,5,6,7,8,9};
	std::vector<std::pair<int,char>> op;
	int count=0;
	calcHundred(arr,9,0,0,0,op,100,count);
}
void floyd(const std::vector<std::vector<int>>& v,std::vector<std::vector<int>>& shortestPath,std::vector<std::vector<int>>& next)
{
	shortestPath=v;
	int size=v.size();
	for(int i=0;i<size;++i)
	{
		for(int j=0;j<size;++j)
		{
			next[i][j]=j;
		}
	}
	for(int k=0;k<size;++k)
	{
		for(int i=0;i<size;++i)
		{
			for(int j=0;j<size;++j)
			{
				int t=shortestPath[i][k]+shortestPath[k][j];
				if((t>0)&&(t<shortestPath[i][j]))
				{
					shortestPath[i][j]=t;
					next[i][j]=next[i][k];
				}
			}
		}
	}
}
void floydMinPath(int from,int to,const std::vector<std::vector<int>>& next)
{
	std::cout<<from<<"->";
	int k=next[from][to];
	while(k!=to)
	{
		std::cout<<k<<"->";
		k=next[k][to];
	}
	std::cout<<to<<std::endl;
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
	std::vector<std::vector<int>> shortestPath(N,std::vector<int>(N,INT_MAX));
	std::vector<std::vector<int>> next(N,std::vector<int>(N,-1));
	floyd(v,shortestPath,next);
	for(auto i:shortestPath)
	{
		for(auto j:i)
		{
			std::cout<<j<<" ";
		}
		std::cout<<std::endl;
	}
	floydMinPath(0,6,next);
	floydMinPath(0,2,next);

}
void bellmanFord(const std::vector<std::vector<int>>& arr,std::vector<int>& shortestPath,std::vector<std::vector<int>>& next,int from)
{
	int size=arr.size();
	int minValue=0;
	shortestPath[from]=0;
	for(int k=0;k<size;++k)
	{
		for(int i=0;i<size;++i)
		{
			for(int j=0;j<size;++j)
			{
				if(arr[i][j]<INT_MAX)
				{
					shortestPath[j]=std::min(shortestPath[j],shortestPath[i]+arr[i][j]);
				}
			}
		}
	}
	
}
void test_bellmanFord()
{
	const int N=7;
	std::vector<std::vector<int>> v(N,std::vector<int>(N,INT_MAX));
	v[0][0]=0;v[0][1]=20;v[0][2]=50;v[0][3]=30;
	v[1][1]=0;v[1][2]=25;v[1][5]=70;
	v[2][2]=0;v[2][3]=40;v[2][4]=25;v[2][5]=50;
	v[3][3]=0;v[3][4]=55;
	v[4][4]=0;v[4][5]=10;v[4][6]=70;
	v[5][5]=0;v[5][6]=50;
	v[6][6]=0;
	std::vector<int> shortestPath(N,INT_MAX);
	std::vector<std::vector<int>> next(N,std::vector<int>(N,-1));
	bellmanFord(v,shortestPath,next,0);
	
	for(auto j:shortestPath)
	{
		std::cout<<j<<" ";
	}
	std::cout<<std::endl;
}
typedef struct Edge
{
	int m_from;
	int m_to;
	int m_value;
	Edge(int from,int to,int data):m_from(from),m_to(to),m_value(data)
	{}
	
}edge;
bool operator==(const edge& x,const edge& y)
{
	//std::cout<<__LINE__<<std::endl;
	return (x.m_from==y.m_from)&&(x.m_to==y.m_to)&&(x.m_value==y.m_value);
}
bool isAdded(const std::vector<edge>& ret,int from,int to,int value)
{
	edge temp=edge(from,to,value);
	for(auto& x:ret)
	{
		if(x==temp)
		{
			return true;
		}
	}
	return false;
}
edge minEdges(const std::vector<std::vector<int>>& arr,std::vector<int>& points,std::vector<edge>& ret)
{
	//以points里面的点为起点，寻找不在ret中的最小边
	int minValue=INT_MAX;
	int minFrom=INT_MAX;
	int minTo=INT_MAX;
	for(int i=0;i<points.size();++i)
	{
		for(int j=0;j<arr[0].size();++j)
		{
			int t=arr[points[i]][j];
			if((t>0)&&(t<minValue))
			{
				if(!isAdded(ret,points[i],j,t))
				{
					minValue=t;
					minFrom=points[i];
					minTo=j;
					std::cout<<minTo<<":"<<minValue<<std::endl;
				}
			}
		}
	}

	return edge(minFrom,minTo,minValue);
}
void addEdge(std::vector<edge>& ret,edge minEdge,std::vector<int>& points)
{
	//for(int i=0;i<)
	ret.push_back(minEdge);
	 points.push_back(minEdge.m_to);
	//points[minEdge.m_to]=true;
}
void prim(const std::vector<std::vector<int>>& arr,std::vector<edge>& ret)
{
	int N=arr.size();
	std::vector<int> points;
	//std::vector<bool> points(N,false);
	points.push_back(0);
	// for(int i=0;i<N;++i)
	// 	points[i]=i;
//	deleteEdge(ret,minEdge);
	for(int i=0;i<N-1;++i)//repeat n-1
	{
		edge minEdge=minEdges(arr,points,ret);
		if((minEdge.m_value!=INT_MAX)&&(minEdge.m_value!=0))
			addEdge(ret,minEdge,points);
	}
}
void test_prim()
{
	const int N=7;
	std::vector<std::vector<int>> v(N,std::vector<int>(N,INT_MAX));
	v[0][0]=0;v[0][1]=20;v[0][2]=50;v[0][3]=30;
	v[1][1]=0;v[1][2]=25;v[1][5]=70;
	v[2][2]=0;v[2][3]=40;v[2][4]=25;v[2][5]=50;
	v[3][3]=0;v[3][4]=55;
	v[4][4]=0;v[4][5]=10;v[4][6]=70;
	v[5][5]=0;v[5][6]=50;
	v[6][6]=0;
	std::vector<edge> ret;
	prim(v,ret);
	std::cout<<"---------------"<<std::endl;
	for(auto& i:ret)
		std::cout<<"("<<i.m_from<<","<<i.m_to<<"):"<<i.m_value<<std::endl;
}
void test_out()
{
	test_prim();
	// test_bellmanFord();
	// test_floyd();
	// test_caLcHundred();
	// test_dijkstra();
	// test_unionFindSet();
	// test_longestKsubstring();
	// test_catalan();
	// test_largestBST();
	// test_inpost2pre();
}
}