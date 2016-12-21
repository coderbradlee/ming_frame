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
namespace test9_namespace
{
int calcpath1(const std::vector<std::vector<int>>& graph)
{
	const int N=16;
	int step[N]={0};//how many step to i
	int path[N]={0};//how many path to i
	path[0]=1;
	std::queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int from=q.front();
		q.pop();
		for(int i=1;i<N;++i)
		{
			if(graph[from][i]==1)
			{
				if(step[i]==0||step[i]>step[from]+1)
				{
					step[i]=step[from]+1;
					path[i]=path[from];
					q.push(i);
				}
				else if(step[i]==step[from]+1)
				{
					path[i]+=path[from];
				}
			}
			
		}
	}
	return path[N-1];
}
int calcpath(const std::vector<std::vector<int>>& graph)
{
	const int N=graph.size();
	std::vector<int> step(N,0);//从0到i的步数
	std::vector<int> path(N,0);//从0到i的路径数
	path[0]=1;
	int i=0;
	std::queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		i=q.front();
		q.pop();
		for(int j=0;j<N;++j)
		{
			if(graph[i][j]==1)
			{
				if(step[j]==0)
				{
					step[j]=step[i]+1;
					path[j]=path[i];
					q.push(j);
				}
				else if(step[j]==(step[i]+1))
				{
					path[j]+=path[i];
				}
				else if(step[j]>(step[i]+1))
				{
					step[j]=step[i]+1;
					path[j]=path[i];
					q.push(j);
				}
				
			}
		}
	}
	return path[N-1];
}
void test_sp()
{
	const int N=16;
	std::vector<std::vector<int>> graph(N ,std::vector<int>(N,0));
	graph[0][1]=graph[0][4]=1;
	graph[1][5]=graph[1][0]=graph[1][2]=1;
	graph[2][1]=graph[2][6]=graph[2][3]=1;
	graph[3][2]=graph[3][7]=1;
	graph[4][0]=graph[4][5]=1;
	graph[5][1]=graph[5][4]=graph[5][6]=graph[5][9]=1;
	graph[6][2]=graph[6][5]=graph[6][7]=graph[6][10]=1;
	graph[7][3]=graph[7][6]=1;
	graph[8][9]=graph[8][12]=1;
	graph[9][8]=graph[9][13]=graph[9][10]=1;
	graph[10][9]=graph[10][14]=graph[10][11]=1;
	graph[11][10]=graph[11][15]=1;
	graph[12][8]=graph[12][13]=1;
	graph[13][9]=graph[13][12]=graph[13][14]=1;
	graph[14][10]=graph[14][13]=graph[14][15]=1;
	graph[15][11]=graph[15][14]=1;
	std::cout<<calcpath(graph)<<std::endl;
	std::cout<<calcpath1(graph)<<std::endl;
}
int parenthesisLen1(const string& p)
{
	int ret=0;
	int len=0;
	std::stack<int> s;
	for(int i=0;i<p.length();++i)
	{
		if(p[i]=='(')
		{
			s.push(i);
		}
		else
		{
			if(!s.empty())
			{
				int start=s.top();
				s.pop();
				if(s.empty())
				{
					len+=i-start+1;
				}
				else
				{
					// len=0;
				}
				if(len>ret)
				{
					ret=len;
				}
			}
			else
			{
				len=0;
				// allStart=i;
			}
		}
	}
	return ret;
}
int parenthesisLen(const string& p)
{
	int ret=0;
	int len=0;
	std::stack<int> s;
	for(int i=0;i<p.length();++i)
	{
		if(p[i]=='(')
		{
			s.push(i);
		}
		else if(!s.empty())
		{
			int start=s.top();
			s.pop();
			if(s.empty())
			{
				len+=i-start+1;
			}
			
			if(len>ret)
			{
				ret=len;
			}
		}
		else
		{
			len=0;
		}
		
	}
	return ret;
}
void test_parenthesisLen()
{
	string p="()(())";//6
	string p2="((((()))))";//10
	string p3="(())(";//4
	string p4="()(()))";//6
	std::cout<<parenthesisLen(p)<<std::endl;
	std::cout<<parenthesisLen(p2)<<std::endl;
	std::cout<<parenthesisLen(p3)<<std::endl;
	std::cout<<parenthesisLen(p4)<<std::endl;
}
bool isDigit(char c)
{
	return (c<='z')&&(c>='a');
}
bool priorityIsLess(char left,char right)
{
	if(left=='(')
		return true;

	if(((left=='+')||(left=='-'))&&((right=='*')||(right=='/')))
		return true;
	return false;
}
void changeToPolishNotation(const string& in,string& out)
{
	const int len=in.length();
	std::stack<char> s;
	for(int i=0;i<len;++i)
	{
		if(isDigit(in[i]))
		{
			out+=in[i];
		}
		else if(in[i]=='(')
		{
			s.push(in[i]);
		}
		else if(in[i]==')')
		{
			while((!s.empty())&&(s.top()!='('))
			{
				out+=s.top();
				s.pop();
			}
			s.pop();
		}
		else
		{
			if(!s.empty())
			{
				if(priorityIsLess(s.top(),in[i]))//in[i]优先级高
				{
					s.push(in[i]);
				}
				else
				{
					while((!s.empty())&&(!priorityIsLess(s.top(),in[i])))
					{
						out+=s.top();
						s.pop();
					}
					s.push(in[i]);
				}
			}
			else
			{
				s.push(in[i]);
			}
		}
	}
	while(!s.empty())
	{
		out+=s.top();
		s.pop();
	}
}
void test_changeToPolishNotation()
{
	//a + b*c + (d * e + f) * g
	//a b c * + d e * f  + g * +
	string in="a+b*c+(d*e+f)*g";
	string out;
	changeToPolishNotation(in,out);
	std::cout<<out<<std::endl;
}
struct test_struct
{
	
};
class test_class
{
public:
	test_class();
	~test_class();
	
};
union s
{
	int i;
	char x;
};
void test_endian()
{
	s u;
	u.i=0x12345678;
	printf("%x\n", u.x);
}
void test_out()
{
	test_endian();
	// test_changeToPolishNotation();
	// test_parenthesisLen();
	// std::cout<<sizeof(test_struct)<<std::endl;
	// std::cout<<sizeof(test_class)<<std::endl;
	// test_sp();
	
}
}
