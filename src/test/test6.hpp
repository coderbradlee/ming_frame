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
#include <set>
namespace test6_namespace
{
	void print(const std::vector<std::pair<int,int>>& path)
	{
		for(auto& i:path)
		std::cout<<"("<<i.first<<","<<i.second<<") ";
		std::cout<<std::endl;
	}
	std::vector<std::vector<std::pair<int,int>>> all;
	bool search(
		const std::vector<std::vector<int>>& chess,
		int i,
		int j,
		std::vector<std::pair<int,int>>& path,
		std::vector<std::vector<bool>>& visit)
	{
		//std::cout<<"1"<<std::endl;
		if(chess[i][j]==9)
		{
			print(path);
			return true;
		}
		int iNext[]={0,0,-1,1};
		int jNext[]={-1,1,0,0};
		int m=chess.size();
		int n=chess[0].size();
		for(int k=0;k<4;++k)
		{
			int iCur=i+iNext[k];
			int jCur=j+jNext[k];
			if((iCur<0)||(iCur>=m)||(jCur<0)||(jCur>=n))
				continue;
			if((!visit[iCur][jCur])&&(chess[iCur][jCur]!=0))
			{
				std::cout<<chess[iCur][jCur]<<std::endl;
				path.push_back(std::make_pair(iCur,jCur));
				visit[iCur][jCur]=true;
				if(search(chess,iCur,jCur,path,visit))
				{
					all.push_back(path);
					return true;
				}	
				path.pop_back();
				visit[iCur][jCur]=false;
			}
		}
		return false;
	}
	void mouse(const std::vector<std::vector<int>>& chess)
	{
		std::vector<std::pair<int,int>> path;
		std::vector<std::vector<bool>> visit(chess.size(), 
		std::vector<bool>(chess[0].size(), false));

		path.push_back(std::make_pair(0, 0));
		visit[0][0] = true;
		search(chess,0,0,path,visit);
	}
	void test_mouseCheese()
	{
		const int N = 8;
		std::vector<std::vector<int>> c = 
		{
			{1, 1, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 1, 0, 0, 1},
			{1, 1, 1, 0, 1, 0, 0, 1},
			{0, 1, 0, 0, 1, 1, 1, 1},
			{0, 1, 0, 0, 0, 0, 0, 1},
			{0, 1, 0, 9, 1, 1, 1, 1},
			{0, 1, 1, 1, 0, 0, 1, 0}
		};
		mouse(c);
		std::cout<<"==========="<<std::endl;
		for(auto j:all)
		{
			for(auto i:j)
				std::cout<<"("<<i.first<<","<<i.second<<") ";
			std::cout<<std::endl;
		}
	}
	void Print(int index, const int* a, const std::vector<std::pair<int, char> >& op, int size)
	{
		std::cout << index << ":\t";
		std::vector<std::pair<int, char> >::const_iterator o = op.begin();
		for(int i = 0; i < size; i++)
		{
			std::cout << a[i];
			if(i == size-1)
				break;
			if((o != op.end()) && (o->first == i))
			{
				std::cout << " " << o->second  << " ";
				o++;
			}
		}
		std::cout << '\n';
	}
	bool lastOperatorIsAdd(std::vector<std::pair<int,char>> op)
	{
		if(op.empty())
			return true;
		return op.back().second=='+';
	}
	bool Calc(const int* a,int size,int cur,int n,int last,
		std::vector<std::pair<int,char>>& op,int sum,int& count)
	{
		if(cur==size-1)
		{
			last=10*last+a[size-1];
			if((lastOperatorIsAdd(op) ? (n+last) : (n-last)) == sum)
			{
				count++;
				Print(count, a, op, size);
				return true;
			}
			return false;
		}
		last=10*last+a[cur];
		Calc(a,size,cur+1,n,last,op,sum,count);
		bool isAdd=lastOperatorIsAdd(op);
		op.push_back(std::make_pair(cur,'+'));
		Calc(a,size,cur+1,isAdd?n+last:n-last,0,op,sum,count);
		op.back().second='-';
		Calc(a,size,cur+1,isAdd?n+last:n-last,0,op,sum,count);
		op.pop_back();
		return count!=0;
	}
	void convertTo3(int i,std::vector<char>& v)
	{
		int j=7;
		while(i!=0)
		{
			//v[j]=char(i%3+48);
			if(i%3==0)
			{
				v[j]='0';
			}
			else if(i%3==1)
			{
				 v[j]='-';
				//v[j]='1';
			}
			else if(i%3==2)
			{
				v[j]='+';
				//v[j]='2';
			}
			i/=3;
			--j;
		}
	}
	void bruteForce(const int* a,int size,std::vector<std::string>& expressions)
	{
		//1,2,3,4,5,6,7,8,9 每个间隔有三种情况，+ - 空白
		int N=3*3*3*3*3*3*3*3;
		// std::vector<std::string> expressions;
		for(int i=0;i<N;++i)
		{
			std::vector<char> v(8);
			convertTo3(i,v);
			std::string expression({'1'});
			for(int j=0;j<8;++j)
			{
				// char temp1=v[j];
				// char temp2=char(j+2+48);
				// std::cout<<temp1<<":"<<j<<":"<<temp2<<std::endl;
				if(v[j]!='0')
				expression.append({v[j]});
				expression.append({char(j+2+48)});
			}
			v.clear();
			expressions.push_back(expression);
		}
	}
	bool isDigit(char c)
	{
		return c>='0'&&c<='9';
	}
	int calExpression(const std::string& exp)
	{
		int left=0;
		int ret=0;
		std::stack<int> digit;
		std::stack<char> op;
		for(int i=0;i<exp.length();++i)
		{
			if(isDigit(exp[i]))
			{
				left+=left*10+(int)exp[i]-48;
				//std::cout<<left<<std::endl;
			}
			else
			{
				digit.push(left);
				left=0;
				op.push(exp[i]);
			}
			if(digit.size()==2)
			{		
				ret=digit.top();
				digit.pop();
				if(op.top()=='+')
				{
					ret+=digit.top();
				}
				else
				{
					ret-=digit.top();
				}
				digit.pop();
				digit.push(ret);
				op.pop();
			}
		}
		//std::cout<<digit.top()<<" ";
		return digit.top();
	}
	void calExpression(std::vector<std::string>& expressions,std::vector<std::string>& left)
	{
		for(auto& i:expressions)
		{
			if(i=="1+2+3-4+5+6+78+9")
				std::cout<<"found "<<std::endl;
			int ret=calExpression(i);
			if(ret==100)
				left.push_back(i);
		}
	}
	void test_handred()
	{
		int a[] = {1,2,3,4,5,6,7,8,9};
		int size = sizeof(a)/sizeof(int);
		// std::vector<std::pair<int,char>> op;
		// int count = 0;
		// Calc(a, size, 0, 0, 0, op, 100, count);
		// std::vector<char> v(8);
		// convertTo3(4124,v);

		// for(int i=0;i<81*81;++i)
		// {
		// 	std::vector<char> v(8);
		// 	convertTo3(i,v);
			
		// 	for(auto& j:v)
		// 	{	
		// 		if(j)
		// 			std::cout<<j;
		// 		else
		// 			std::cout<<"#";
		// 	}
		// 	std::cout<<std::endl;
			
		// // 	//1+2+3-4+5+6+78+9
		// // 	// if((v[0]=='+')&&(v[1]=='+')
		// // 	// 	&&(v[2]=='-')&&(v[3]=='+')
		// // 	// 	&&(v[4]=='+')&&(v[5]=='+')
		// // 	// 	&&(!v[6])&&(v[7]=='+'))
		// // 	// 	std::cout<<"xxxxxxxxxx"<<std::endl;
		// 	v.clear();
		// }
		std::vector<std::string> expressions;
		bruteForce(a,9,expressions);
		// for(auto i:expressions)
		// 	std::cout<<i<<" ";
		std::cout<<std::endl;
		std::vector<std::string> left;
		calExpression(expressions,left);
		for(auto& i:left)
		{
			std::cout<<i<<std::endl;
		}
		//std::cout<<"::"<<calExpression("1+2+3-4+5+6+78+9")<<std::endl;
		std::cout<<std::endl;

	}
	void test_out()
	{
		test_handred();
		//std::cout<<"1"<<std::endl;
		// test_mouseCheese();
		//std::cout<<"2"<<std::endl;
	}
}
