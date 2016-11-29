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
	// bool operator<(const edge& x,const edge& y)
	// {
	// 	return x.m_value<y.m_value;
	// }
	
}edge;
bool operator<( const edge& l, const edge& r )
{ 
	return l.m_value<r.m_value;
}
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
void kruskal(const std::vector<std::vector<int>>& arr,std::vector<edge>& mst)
{
	std::set<edge> temp;
	for(int i=0;i<arr.size();++i)
	{
		for(int j=0;j<arr[0].size();++j)
		{
			if(arr[i][j]<INT_MAX)
			{
				temp.insert(edge(i,j,arr[i][j]));
			}
		}
	}
	unionFindSet ufs(arr.size());
	while(!temp.empty())
	{
		auto it=temp.begin();
		int ri=ufs.finds((*it).m_from);
		int rj=ufs.finds((*it).m_to);
		if(ri!=rj)
		{
			ufs.unions(ri,rj);
			mst.push_back(*it);
		}
		temp.erase(it);
	}
	// ufs.print();
}
void test_kruskal()
{
	const int N=6;
	std::vector<std::vector<int>> v(N,std::vector<int>(N,INT_MAX));
	v[0][0]=0;v[0][1]=10;v[0][3]=30;v[0][4]=45;
	v[1][1]=0;v[1][2]=50;v[1][5]=25;
	v[2][2]=0;v[2][4]=35;v[2][5]=15;
	v[3][3]=0;v[3][5]=20;
	v[4][4]=0;v[4][5]=55;
	v[5][5]=0;
	std::vector<edge> mst;
	kruskal(v,mst);
	for(auto& i:mst)
	{
		std::cout<<"("<<i.m_from+1<<","<<i.m_to+1<<"):"<<i.m_value<<std::endl;
	}
}
bool outStackSequence(const std::string& in,const std::string& out)
{
	int inLen=in.length();
	int outLen=out.length();
	std::stack<char> s;
	s.push(in[0]);
	int i=1;
	int j=0;
	while(j<outLen)
	{
		if(in[i]==out[j])
		{
			++i;
			++j;
		}
		else
		{
			if(!s.empty())
			{
				char c=s.top();
				if((c!=out[j])&&(i<inLen))
				{
					s.push(in[i++]);
				}
				else
				{
					if(s.top()!=out[j])
						return false;
					s.pop();
					++j;
				}
			}
			else if(in[i]!=out[j])
			{
				s.push(in[i++]);
			}
		}
	}
	return true;
}
void test_outStackSequence()
{
	// std::string in="ABCDEFG";
	// std::string out="BAEDFGC";
	std::string in="ABCD";
	std::string out="BDAC";
	bool b=outStackSequence(in,out);
	std::cout<<b<<std::endl;
}
bool onlyChangeone(const std::string& cur,const std::string& dict)
{
	if(cur.length()!=dict.length())
		return false;
	int change=0;
	for(int i=0;i<cur.length();++i)
	{
		if(cur[i]!=dict[i])
			++change;
	}
	if(change>1)
		return false;
	return true;
}
int extend(const std::string& cur,std::queue<std::string>& que,const std::set<std::string>& dict,const std::set<std::string>& visited)
{
	int len=0;
	for(auto& i:dict)
	{
		if(onlyChangeone(cur,i)&&(visited.find(i)==visited.end()))
		{
			que.push(i);
			
			++len;
		}
	}
	return len;
}
int wordLadder(const std::string& start,const std::string& end,const std::set<std::string>& dict,std::queue<std::string>& ret)
{
	std::queue<std::string> que;
	
	int step=0;
	que.push(start);
	std::vector<std::string> children;
	std::set<std::string> visited;
	int curLevel=1;
	int nextLevel=0;
	while(!que.empty())
	{
		std::string cur=que.front();
		que.pop();
		--curLevel;
		nextLevel+=extend(cur,que,dict,visited);
		visited.insert(cur);
		ret.push(cur);
		if(onlyChangeone(cur,end))
		{
			return step;
		}
		else if(curLevel==0)
		{
			++step;
			curLevel=nextLevel;
			nextLevel=0;
		}
	}

	return 0;
}
void test_wordLadder()
{
	std::set<std::string> dict;
	std::queue<std::string> ret;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	std::string start="hit";
	std::string end="cog";
	std::cout<<wordLadder(start,end,dict,ret)<<std::endl;

	std::cout<<ret.size()<<std::endl;
	while(!ret.empty())
	{
		std::cout<<ret.front()<<"->";
		ret.pop();
	}
	std::cout<<end<<std::endl;
}
enum class suit { soil,water,lake,ocean};
bool isOcean(const std::vector<std::vector<suit>>& graph,int row,int col)
{
	if(row<0||row>graph.size()||col<0||col>graph[0].size())
		return false;
	return graph[row][col]==suit::water;
}
void fillOcean(std::vector<std::vector<suit>>& graph,int row,int col)
{
	std::vector<int> iDirect{-1,1,0,0};
	std::vector<int> jDirect{0,0,-1,1};
	std::stack<std::pair<int,int>> s;
	s.push(std::make_pair(row,col));
	while(!s.empty())
	{
		int i=s.top().first;
		int j=s.top().second;
		s.pop();
		for(int k=0;k<4;++k)
		{
			int ri=i+iDirect[k];
			int rj=j+jDirect[k];
			if(isOcean(graph,ri,rj))
			{
				graph[ri][rj]=suit::ocean;
				s.push(std::make_pair(ri,rj));
			}
		}
	}
	
}
void ocean(std::vector<std::vector<suit>>& graph)
{
	
	for(int j=0;j<graph[0].size();++j)
	{
		if(graph[0][j]==suit::water)
		{
			graph[0][j]=suit::ocean;
			fillOcean(graph,0,j);//
		}
		if(graph[graph.size()-1][j]==suit::water)
		{
			graph[graph.size()-1][j]=suit::ocean;
			fillOcean(graph,graph.size()-1,j);//
		}
	}
	for(int i=1;i<graph.size()-1;++i)
	{
		if(graph[i][0]==suit::water)
		{
			graph[i][0]=suit::ocean;
			fillOcean(graph,i,0);//
		}
		if(graph[i][graph[0].size()-1]==suit::water)
		{
			graph[i][graph[0].size()-1]=suit::ocean;
			fillOcean(graph,i,graph[0].size()-1);//
		}
	}
}
void fillLake(std::vector<std::vector<suit>>& graph)
{
	ocean(graph);
	for(int i=0;i<graph.size();++i)
	{
		for(int j=0;j<graph[0].size();++j)
		{
			if(graph[i][j]==suit::water)
			{
				graph[i][j]=suit::soil;
			}
			else if(graph[i][j]==suit::ocean)
			{
				graph[i][j]=suit::water;
			}
		}
	}
	
}
void test_fillLake()
{
	//把边界上的water变为ocean，遍历和它相连的water，变为ocean
	//然后把其余的water变为soil，最后把ocean变为water
	
	// const int N=4;
	// std::vector<std::vector<suit>> graph(N,std::vector<suit>(N,suit::soil));
	// graph[1][1]=suit::water;graph[1][2]=suit::water;
	// graph[2][2]=suit::water;graph[3][1]=suit::water;
	const int N=5;
	std::vector<std::vector<suit>> graph(N,std::vector<suit>(N,suit::soil));
	graph[1][1]=suit::water;graph[1][2]=suit::water;graph[1][3]=suit::water;
	graph[3][3]=suit::water;graph[4][3]=suit::water;
	fillLake(graph);
	for(auto& i:graph)
	{
		for(auto& j:i)
		{
			using color_rep_type = std::underlying_type<suit>::type;
			std::cout << static_cast<color_rep_type>(j) <<" ";
		}
		std::cout<<std::endl;
	}
}

class queens
{
public:
	queens(int n):m_size(n),m_path(n,-1),m_cols(n,true),
	m_mainDiagonal(2*(n-1),true),
	m_minorDiagonal(2*(n-1),true)
	{}
	int calc()
	{
		calcQueens(0);
		return m_ret.size();
	}
	void print()
	{
		for(auto& i:m_ret)
		{
			for(auto& j:i)
			{
				std::cout<<j<<" ";
			}
			std::cout<<std::endl;
		}
	}
private:
	bool canLay(int row,int col)
	{
		if((m_path[row]==-1)&&(m_cols[col])
			&&m_mainDiagonal[m_size-1+(col-row)]
			&&m_minorDiagonal[col+row])
			return true;
		
		return false;
	}
	void calcQueens(int row)
	{
		if(row==m_size)
		{
			m_ret.push_back(m_path);
			return;
		}
		else
		{
			for(int col=0;col<m_size;++col)
			{
				if(canLay(row,col))
				{
					m_path[row]=col;
					m_cols[col]=false;
					m_mainDiagonal[m_size-1+(col-row)]=false;
					m_minorDiagonal[col+row]=false;
				
					calcQueens(row+1);
					//回溯
					m_path[row]=-1;
					m_cols[col]=true;
					m_mainDiagonal[m_size-1+(col-row)]=true;
					m_minorDiagonal[col+row]=true;
				}
			}
		}
	}
	
private:
	int m_size;
	std::vector<int> m_path;//第i行的皇后放在第几列
	std::vector<bool> m_cols;
	std::vector<bool> m_mainDiagonal;
	std::vector<bool> m_minorDiagonal;
	std::vector<std::vector<int>> m_ret;
};
void test_queen()
{
	{
		int N=8;
		queens q(N);
		std::cout<<q.calc()<<std::endl;
	}
	{
		int N=6;
		queens q(N);
		std::cout<<q.calc()<<std::endl;
		q.print();
	}
}
class sudoku
{
public:
	sudoku(const std::vector<std::vector<int>>& chess):m_solved(false),m_chess(chess)
	{
		m_size=m_chess.size();
	}
	bool solve()
	{
		for(int i=0;i<m_size;++i)
		{
			for(int j=0;j<m_size;++j)
			{
				if(m_chess[i][j]==0)
				{
					for(int k=1;k<10;++k)
					{
						m_chess[i][j]=k;
						if(isValid(i,j)&&solve())
						{
							if(!m_solved)
								m_ret.push_back(m_chess);
							m_solved=true;
							return true;
						}
						m_chess[i][j]=0;
					}
					return false;
				}
			}
		}
		return true;
	}
	void print()
	{
		std::cout<<m_ret.size()<<std::endl;
		for(auto& i:m_ret)
		{
			for(auto& j:i)
			{
				for(auto& k:j)
					std::cout<<k<<" ";
				std::cout<<std::endl;
			}
			std::cout<<"---------------"<<std::endl;
		}
	}
private:
	bool isValid(int row,int col)
	{
		//std::cout<<row<<":"<<col<<std::endl;
		int value=m_chess[row][col];
		for(int i=0;i<m_size;++i)
		{
			if((i!=row)&&(m_chess[i][col]==value))
				return false;
			if((i!=col)&&(m_chess[row][i]==value))
				return false;
		}
		int rowStart=(row/3)*3;
		int colStart=(col/3)*3;
		for(int i=rowStart;i<rowStart+3;++i)
		{
			for(int j=colStart;j<colStart+3;++j)
			{
				if((i==row)&&(j==col))
					continue;
				if(m_chess[i][j]==value)
					return false;
			}
		}
		return true;
	}
private:
	bool m_solved;
	int m_size;
	std::vector<std::vector<int>> m_chess;
	std::vector<std::vector<std::vector<int>>> m_ret;
};
void test_sudoku()
{
	std::vector<std::vector<int>> chess=
	{
		{0,0,0,0,0,0,0,1,0},
		{4,0,0,0,0,0,0,0,0},
		{0,2,0,0,0,0,0,0,0},
		{0,0,0,0,5,0,4,0,7},
		{0,0,8,0,0,0,3,0,0},
		{0,0,1,0,9,0,0,0,0},
		{3,0,0,4,0,0,2,0,0},
		{0,5,0,1,0,0,0,0,0},
		{0,0,0,8,0,6,0,0,0}
	};
	// std::vector<std::vector<int>> chess=
	// {
	// 	{0, 4, 2, 0, 6, 3, 0, 0, 9},
	// 	{6, 0, 0, 0, 1, 0, 0, 0, 5},
	// 	{3, 0, 0, 0, 2, 0, 4, 8, 0},
	// 	{1, 0, 0, 5, 0, 2, 6, 0, 8},
	// 	{4, 0, 0, 0, 0, 7, 0, 0, 1},
	// 	{9, 0, 5, 6, 0, 0, 0, 0, 7},
	// 	{0, 3, 6, 0, 5, 0, 0, 0, 2},
	// 	{2, 0, 0, 0, 7, 0, 0, 0, 4},
	// 	{7, 0, 0, 2, 9, 0, 8, 5, 0}
	// };
	sudoku s(chess);
	s.solve();
	s.print();
}
namespace test_good
{
	using namespace std;
class CSudoku
{
private:
	int m_chess[9][9];
	int m_result[9][9];
	bool m_bSolve;
	int m_nCount;

public:
	CSudoku(int chess[9][9])
	{
		memcpy(m_chess, chess, sizeof(m_chess));
		m_bSolve = false;
		m_nCount = 0;
	}

	bool IsValid(int i, int j)
	{
		int t = m_chess[i][j];
		int k;
		for(k = 0; k < 9; k++)
		{
			if((j != k) && (t == m_chess[i][k]))	//ÁÐ
				return false;
			if((i != k) && (t == m_chess[k][j]))	//ÐÐ
				return false;
		}
		int iGrid = (i / 3) * 3;
		int jGrid = (j / 3) * 3;
		int k1,k2;
		for(k1 = iGrid; k1 < iGrid+3; k1++)
		{
			for(k2 = jGrid; k2 < jGrid+3; k2++)
			{
				if((k2 == j) && (k1 == i))
					continue;
				if(t == m_chess[k1][k2])
					return false;
			}
		}
		return true;
	}

	bool Sudoku()
	{
		int i,j, k;
		for(i = 0; i < 9; i++)
		{
			for(j = 0; j < 9; j++)
			{
				if(m_chess[i][j] == 0)
				{
					for(k = 1; k < 10; k++)
					{
						m_chess[i][j] = k;
						if(IsValid(i, j) && Sudoku())
						{
							if(!m_bSolve)
								memcpy(m_result, m_chess, sizeof(m_chess));
							m_bSolve = true;
							m_nCount++;
							//return true;
						}
						m_chess[i][j] = 0;
					}
					return false;
				}
			}
		}
		return true;	//ËµÃ÷ËùÓÐÎ»ÖÃ¶¼ÓÐÖµÁË
	}

	void Print(bool bChess)
	{
		int i,j;
		for(i = 0; i < 9; i++)
		{
			for(j = 0; j < 9; j++)
			{
				if(bChess)
					cout << m_chess[i][j] << "  ";
				else
					cout << m_result[i][j] << "  ";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}

	int GetCount() const
	{
		return m_nCount;
	}
};

void test_sudoku()
{
	int chess[9][9] = {
		// {0, 4, 2, 0, 6, 3, 0, 0, 9},
		// {6, 0, 0, 0, 1, 0, 0, 0, 5},
		// {3, 0, 0, 0, 2, 0, 4, 8, 0},
		// {1, 0, 0, 5, 0, 2, 6, 0, 8},
		// {4, 0, 0, 0, 0, 7, 0, 0, 1},
		// {9, 0, 5, 6, 0, 0, 0, 0, 7},
		// {0, 3, 6, 0, 5, 0, 0, 0, 2},
		// {2, 0, 0, 0, 7, 0, 0, 0, 4},
		// {7, 0, 0, 2, 9, 0, 8, 5, 0},
		// {0, 4, 2, 0, 6, 3, 0, 0, 9},
		// {6, 0, 0, 0, 1, 0, 0, 0, 5},
		// {3, 0, 0, 0, 2, 0, 4, 8, 0},
		// {1, 0, 0, 5, 0, 2, 6, 0, 8},
		// {4, 0, 0, 0, 0, 7, 0, 0, 1},
		// {9, 0, 5, 6, 0, 0, 0, 0, 7},
		// {0, 3, 6, 0, 5, 0, 0, 0, 2},
		// {2, 0, 0, 0, 7, 0, 0, 0, 4},
		// {7, 0, 0, 2, 9, 0, 8, 5, 0}
		////////////////////////////
		{0,0,0,0,0,0,0,1,0},
		{4,0,0,0,0,0,0,0,0},
		{0,2,0,0,0,0,0,0,0},
		{0,0,0,0,5,0,4,0,7},
		{0,0,8,0,0,0,3,0,0},
		{0,0,1,0,9,0,0,0,0},
		{3,0,0,4,0,0,2,0,0},
		{0,5,0,1,0,0,0,0,0},
		{0,0,0,8,0,6,0,0,0}
	};
	//memset(chess, 0, sizeof(int)*81);
	CSudoku sudoku(chess);
	sudoku.Print(true);
	sudoku.Sudoku();
	sudoku.Print(false);
	cout << sudoku.GetCount() << endl;
}
}
bool canJump(const std::vector<std::vector<int>>& chess,int row,int col)
{
	int rowLen=chess.size();
	int colLen=chess[0].size();
	if(row<0||row>=rowLen||col<0||col>=colLen)
		return false;
	return (chess[row][col]==0);	
}
bool horseJump(std::vector<std::vector<int>>& chess,int row,int col,int step,std::vector<std::vector<std::vector<int>>>& ret)
{
	int m=chess.size();
	int n=chess[0].size();
	if(step==m*n)
	{
		return true;
	}
	std::vector<int> ri{-2,-2,-1,+1,+2,+2,+1,-1};
	std::vector<int> rj{-1,+1,+2,+2,+1,-1,-2,-2};
	for(int i=0;i<8;++i)
	{
		int icur=row+ri[i];
		int jcur=col+rj[i];
		if(canJump(chess,icur,jcur))
		{
			chess[icur][jcur]=step+1;
			if(horseJump(chess,icur,jcur,step+1,ret))
			{
				ret.push_back(chess);
				// return true;
			}
			chess[icur][jcur]=0;
		}
	}
	return false;
}
void test_horseJump()
{
	// int m=5;
	// int n=6;
	int m=6;
	int n=7;
	std::vector<std::vector<int>> chess(m,std::vector<int>(n,0));
	int step=1;
	chess[0][0]=1;
	std::vector<std::vector<std::vector<int>>> ret;
	std::cout<<horseJump(chess,0,0,step,ret)<<std::endl;

	for(auto& i:ret)
	{
		for(auto& j:i)
		{
			for(auto& k:j)
				std::cout<<k<<" ";
			std::cout<<std::endl;
		}
		std::cout<<"---------------"<<std::endl;
	}
}
void test_out()
{
	test_horseJump();
	// test_good::test_sudoku();
	// test_sudoku();
	// test_queen();
	// test_fillLake();
	// test_wordLadder();
	// test_outStackSequence();
	// test_kruskal();
	// test_prim();
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
