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
	enum class suit { soil,water,lake,ocean};
	bool isOcean(const std::vector<std::vector<suit>>& graph,int row,int col,int i,int j)
	{
		if((i<0)||(i>=row)||(j<0)||(j>=col))
			return false;
		return graph[i][j]==suit::water;
	}
	void ocean(std::vector<std::vector<suit>>& graph,
		int rowSize,
		int colSize,
		int row,
		int col)
	{
		int iDirect[]={-1,1,0,0};
		int jDirect[]={0,0,-1,1};
		std::queue<std::pair<int,int>> q;
		q.push(std::make_pair(row,col));
		while(!q.empty())
		{
			int i=q.front().first;
			int j=q.front().second;
			q.pop();
			for(int k=0;k<4;++k)
			{
				int iCur=i+iDirect[k];
				int jCur=j+jDirect[k];
				if(isOcean(graph,rowSize,colSize,iCur,jCur))
				{
					q.push(std::make_pair(iCur,jCur));
					graph[iCur][jCur]=suit::ocean;
				}
			}
		}
	}
	void fillLake(std::vector<std::vector<suit>>& graph,int rowSize,int colSize)
	{
		for(int i=1;i<colSize-1;++i)
		{
			if(graph[0][i]==suit::water)
			{
				graph[0][i]=suit::ocean;
				ocean(graph,rowSize,colSize,0,i);
			}
			if(graph[rowSize-1][i]==suit::water)
			{
				graph[rowSize-1][i]=suit::ocean;
				ocean(graph,rowSize,colSize,rowSize-1,i);
			}
		}
		for(int i=0;i<rowSize;++i)
		{
			if(graph[i][0]==suit::water)
			{
				graph[i][0]=suit::ocean;
				ocean(graph,rowSize,colSize,i,0);
			}
			if(graph[i][colSize-1]==suit::water)
			{
				graph[i][colSize-1]=suit::ocean;
				ocean(graph,rowSize,colSize,i,colSize-1);
			}
		}
		for(auto& i:graph)
		{
			for(auto& j:i)
			{
				using color_rep_type = std::underlying_type<suit>::type;
				std::cout << static_cast<color_rep_type>(j) <<" ";
				if(j==suit::water)
					j=suit::soil;
			}
			std::cout<<std::endl;
		}
	}
	void test_fillLake()
	{
		//把边界上的water变为ocean，遍历和它相连的water，变为ocean
		//然后把其余的water变为soil，最后把ocean变为water
		
		const int N=4;
		std::vector<std::vector<suit>> graph(N,std::vector<suit>(N,suit::soil));
		graph[1][1]=suit::water;graph[1][2]=suit::water;
		graph[2][2]=suit::water;graph[3][1]=suit::water;
		fillLake(graph,4,4);
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
		queens(int n):m_num(n),
		m_col(n,false),
		m_mainDiagonal(2*n-1,false),
		m_minorDiagonal(2*n-1,false){}
		void queen()
		{
			std::vector<int> onePath(m_num);
			calcNqueen(onePath,0);
		}
		void print()const
		{
			for(auto i:m_Answer)
			{
				for(auto j:i)
				{
					std::cout<<j<<" ";
				}
				std::cout<<std::endl;
			}
			std::cout<<"num of answer:"<<m_Answer.size()<<std::endl;
		}
	private:
		void calcNqueen(std::vector<int>& path,int row)
		{
			if(row==m_num)
			{
				m_Answer.push_back(path);
				return;
			}
			for(int i=0;i<m_num;++i)
			{
				if(canLay(row,i))
				{
					path[row]=i;
					m_col[i]=true;
					m_mainDiagonal[row-i+m_num-1]=true;
					m_minorDiagonal[row+i]=true;
					calcNqueen(path,row+1);
					//回溯 
					m_col[i]=false;
					m_mainDiagonal[row-i+m_num-1]=false;
					m_minorDiagonal[row+i]=false;
				}
			}
		}
		bool canLay(int row,int col)const
		{
			return !m_col[col]&&!m_minorDiagonal[row+col]&&!m_mainDiagonal[m_num-1+row-col];
		}
	private:
		int m_num;
		std::vector<bool> m_col;
		std::vector<bool> m_mainDiagonal;
		std::vector<bool> m_minorDiagonal;
		std::vector<std::vector<int>> m_Answer;
	};
	void test_queen()
	{
		queens q(8);
		q.queen();
		q.print();
	}
	class sudoku
	{
	public:
		sudoku(std::vector<std::vector<int>> chess):m_chess(chess)
		{
			rowSize=m_chess.size();
			colSize=m_chess[0].size();
		}
		bool solve()
		{
			
			for(int i=0;i<rowSize;++i)
			{
				for(int j=0;j<colSize;++j)
				{
					if(m_chess[i][j]==0)
					{
						for(int k=1;k<10;++k)
						{
							m_chess[i][j]=k;
							if(isValid(i,j)&&solve())
							{
								m_ret.push_back(m_chess);
							}
						}
						m_chess[i][j]=0;
						return false;
					}
				}

			}
			return true;
		}
		void print()
		{
			for(auto& i:m_ret)
			{
				for(auto& j:i)
				{
					for(auto& x:j)
					{
						std::cout<<x<<" ";
					}
					std::cout<<std::endl;
				}
				std::cout<<"-------------"<<std::endl;
			}	

		}
	private:
		bool isValid(int row,int col)
		{
			for(int i=0;i<colSize;++i)
			{
				if((m_chess[row][i]==m_chess[row][col])&&i!=col)
					return false;
			}
			for(int i=0;i<rowSize;++i)
			{
				if((m_chess[i][col]==m_chess[row][col])&&i!=row)
					return false;
			}
			//
			int rowIndex=row/3*3;
			int colIndex=col/3*3;
			for(int i=rowIndex;i<rowIndex+3;++i)
			{
				for(int j=colIndex;j<colIndex+3;++j)
				{
					if((row!=i)&&(col!=j)&&(m_chess[i][j]==m_chess[row][col]))
						return false;
				}
			}
			return true;
		}
	private:
		std::vector<std::vector<int>> m_chess;
		int rowSize;
		int colSize;
		std::vector<std::vector<std::vector<int>>> m_ret;
	};
	void test_sudoku()
	{
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
		sudoku s(chess);
		s.solve();
		s.print();
	}
	void test_out()
	{
		test_sudoku();
		// test_queen();
		//test_fillLake();
		// test_handred();
		//std::cout<<"1"<<std::endl;
		// test_mouseCheese();
		//std::cout<<"2"<<std::endl;
	}
}
