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
class horseJump
{
	typedef struct HorseStep
	{
		int directIndex;
		int numOfchoices;
		HorseStep():directIndex(0),numOfchoices(0){}
		// bool operator <(const horseStep& h)
		// {
		// 	return numOfchoices<h.numOfchoices;
		// }
		// bool operator()(const horseStep&  a, const horseStep&  b)
  //       {   
  //           return a.numOfchoices < b.numOfchoices;
  //       } 
	}horseStep;
public:
	horseJump(int m,int n):m_rowSize(m),m_colSize(n),m_chess(m,std::vector<int>(n,0)),m_adjacentRow({-2,-1,2,1,-2,-1,2,1}),m_adjacentCol({1,2,1,2,-1,-2,-1,-2})
	{}
	void solve(int i,int j)
	{
		m_chess[i][j]=1;
		//jump(i,j,1);//jump from (i,j)
		jumpWithNumOfChoices(i,j,1);
	}
	void print()
	{
		for(auto& i:m_chess)
		{
			for(auto& j:i)
			{
				std::cout<<j<<" ";
			}
			std::cout<<std::endl;
		}
	}
private:
	int getNextStep(int i,int j)
	{
		int ret=0;
		for(int k=0;k<8;++k)
		{
			int iCur=i+m_adjacentRow[k];
			int jCur=j+m_adjacentCol[k];
			if(canJump(iCur,jCur))
			{
				++ret;
			}
		}
		return ret;
	}
	int gatherHorseStep(std::vector<horseStep>& hs,int i,int j,bool last)
	{
		int numOfchoices=0;
		for(int k=0;k<8;++k)
		{
			int iCur=i+m_adjacentRow[k];
			int jCur=j+m_adjacentCol[k];
			if(last)
			{
				if(canJump(iCur,jCur))
				{
					hs[numOfchoices].numOfchoices=1;
					hs[numOfchoices].directIndex=k;
					++numOfchoices;
					break;
				}
			}
			else
			{
				hs[numOfchoices].numOfchoices=getNextStep(iCur,jCur);
				if(hs[numOfchoices].numOfchoices!=0)
				{
					hs[numOfchoices].directIndex=k;
					++numOfchoices;
				}
			}
		}

		std::sort(hs.begin(),hs.begin()+numOfchoices,[](const horseStep&  a, const horseStep&  b)
	        {   
	            return a.numOfchoices < b.numOfchoices;
	        } );
		//std::cout<<numOfchoices<<std::endl;
		return numOfchoices;
	}
	bool jumpWithNumOfChoices(int i,int j,int step)
	{
		if(step==m_rowSize*m_colSize)
		{
			m_all.push_back(m_chess);
			return true;
		}
		std::vector<horseStep> hs(8,horseStep());
		int numOfNextStep=gatherHorseStep(hs,i,j,step==m_rowSize*m_colSize);
		// for(auto& h:hs)
		// {
		// 	std::cout<<h.directIndex<<":"<<h.numOfchoices<<std::endl;
		// }
		std::cout<<numOfNextStep<<":"<<step+1<<std::endl;
		for(int k=0;k<numOfNextStep;++k)
		{
			int direct=hs[k].directIndex;
			int iCur=i+m_adjacentRow[direct];
			int jCur=j+m_adjacentCol[direct];
			//std::cout<<direct<<":"<<iCur<<":"<<jCur<<std::endl;
			if(canJump(iCur,jCur))
			{
				m_chess[iCur][jCur]=step+1;

				if(jumpWithNumOfChoices(iCur,jCur,step+1))
				{
					return true;
				}
				m_chess[iCur][jCur]=0;
			}
		}
		return false;
	}
	bool canJump(int iCur,int jCur)
	{
		if((iCur<0)||(iCur>=m_rowSize)||(jCur<0)||(jCur>=m_colSize))
			return false;
		return (m_chess[iCur][jCur]==0);
	}
	bool jump(int i,int j,int step)
	{
		std::cout<<"("<<i<<","<<j<<"):"<<step<<std::endl;
		if(step==m_rowSize*m_colSize)
			return true;
		for(int k=0;k<8;++k)
		{
			int iCur=i+m_adjacentRow[k];
			int jCur=j+m_adjacentCol[k];
			if(canJump(iCur,jCur))
			{
				m_chess[iCur][jCur]=step+1;
				if(jump(iCur,jCur,step+1))
				{
					return true;
				}
				m_chess[iCur][jCur]=0;
			}
		}
		return false;
	}
private:
	int m_rowSize;	
	int m_colSize;
	std::vector<std::vector<int>> m_chess;
	std::vector<int> m_adjacentRow;
	std::vector<int> m_adjacentCol;
	std::vector<std::vector<std::vector<int>>> m_all;
};
void test_horseJump()
{
	//horseJump h(8,9);
	horseJump h(4,5);
	h.solve(0,0);
	h.print();
}
void merge(std::vector<int>& arr,int low,int mid,int high,int& count)
{
	std::vector<int> temp;
	int midIndex=mid+1;
	int lowIndex=low;
	//++midIndex;
	while((lowIndex<=mid)&&(midIndex<=high))
	{	
		if(arr[lowIndex]<arr[midIndex])
		{
			temp.push_back(arr[lowIndex]);
			++lowIndex;
		}
		else
		{
			temp.push_back(arr[midIndex]);
			count+=mid-lowIndex+1;
			for(int k=lowIndex;k<=mid;++k)
			{
				std::cout<<"("<<arr[k]<<","<<arr[midIndex]<<")"<<std::endl;
			}
			
			++midIndex;
			
		}
	}
	
	if(lowIndex<=mid)
	{
		std::copy(arr.begin()+lowIndex,arr.begin()+mid+1,std::back_inserter(temp));
	}
	if(midIndex<=high)
	{
		std::copy(arr.begin()+midIndex,arr.begin()+high+1,std::back_inserter(temp));
	}
	for(int i=0;i<temp.size();++i)
	{
		arr[low+i]=temp[i];
	}
}
void mergeSort(std::vector<int>& arr,int low,int high,int& count)
{
	if(low>=high)
		return;
	int mid=(low+high)/2;
	
	mergeSort(arr,low,mid,count);
	mergeSort(arr,mid+1,high,count);
	merge(arr,low,mid,high,count);
}
void test_merge()
{
	//std::vector<int> arr{3,56,2,7,45,8,1};
	std::vector<int> arr{2,4,6,34,9,7,5,44,3};
	int count=0;
	mergeSort(arr,0,arr.size()-1,count);
	for(auto& i:arr)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl<<count<<std::endl;
}
class youngTableau
{
public:
	youngTableau(int rowSize,int colSize):m_rowSize(rowSize),m_colSize(colSize),m_young(rowSize,std::vector<int>(colSize,99))
	{}
	void prints()
	{
		for(auto& i:m_young)
		{
			for(auto& j:i)
			{
				//std::cout<<j<<" ";
				printf("%2d ",j );
			}
			std::cout<<std::endl;
		}
		std::cout<<"--------------------"<<std::endl;
	}
	void inserts(int num)
	{
		int i=m_rowSize-1;
		int j=m_colSize-1;
		if(m_young[i][j]<99)
			return;//matrix is full 
		m_young[i][j]=num;
		int r=i;
		int c=j;
		while(i>=0||j>=0)
		{
			if((i>=1)&&(m_young[i-1][j]>m_young[r][c]))
			{
				//std::swap(m_young[i-1][j],m_young[i][j]);
				r=i-1;
				c=j;	
			}
			if((j>=1)&&(m_young[i][j-1]>m_young[r][c]))
			{
				//std::cout<<i<<":"<<j<<" "<<m_young[i][j]<<std::endl;
				r=i;
				c=j-1;
			}
			if((r==i)&&(j==c))
			{
				break;
			}
			std::swap(m_young[i][j],m_young[r][c]);
			i=r;
			j=c;
		}
	}
	bool isBig(int a,int b)
	{
		if(rand()%2==0)
		return a>=b;
		return a>b;
	}
	void inserts2(int num)
	{
		int i=m_rowSize-1;
		int j=m_colSize-1;
		if(m_young[i][j]<99)
			return;//matrix is full 
		m_young[i][j]=num;
		int r=i;
		int c=j;
		while(i>=0||j>=0)
		{
			if((i>=1)&&(m_young[i-1][j]>m_young[r][c]))
			{
				//std::swap(m_young[i-1][j],m_young[i][j]);
				r=i-1;
				c=j;	
			}
			if((j>=1)&&isBig(m_young[i][j-1],m_young[r][c]))
			{
				//std::cout<<i<<":"<<j<<" "<<m_young[i][j]<<std::endl;
				r=i;
				c=j-1;
			}
			if((r==i)&&(j==c))
			{
				break;
			}
			std::swap(m_young[i][j],m_young[r][c]);
			i=r;
			j=c;
		}
	}
	bool finds(int num,int& row,int& col)
	{
		//search from top right
		
		// while(m_young[row][col]>num)
		// {
		// 	if(col==0)
		// 		return false;
		// 	--col;
		// }
		// while(m_young[row][col]<num)
		// {
		// 	if(row==m_rowSize-1)
		// 		return false;
		// 	++row;
		// }
		col=m_colSize-1;
		for(row=0;row<m_rowSize;++row)
		{
			for(;col>=0;--col)
			{
				if(m_young[row][col]<num)
				{
					break;
				}
				else if(m_young[row][col]==num)
					return true;
			}
		}
		
		return false;
	}
	bool deletes(int num)
	{
		int i=0;
		int j=0;
		if(finds(num,i,j))
		{
			int r=i;
			int c=j;
			while(i<m_rowSize&&j<m_colSize)
			{
				if(m_young[r][c]==99)
					break;
				//if((i<m_rowSize-1)&&(m_young[i+1][j]<m_young[r][c]))
				if(i<m_rowSize-1)
				{
					//std::swap(m_young[i-1][j],m_young[i][j]);
					r=i+1;
					c=j;	
				}
				if((j<m_colSize-1)&&m_young[i][j+1]<m_young[r][c])
				{
					//std::cout<<i<<":"<<j<<" "<<m_young[i][j]<<std::endl;
					r=i;
					c=j+1;
				}
				if((r==i)&&(j==c))
				{

					return true;
				}
				m_young[i][j]=m_young[r][c];
				i=r;
				j=c;
			}
		}
		return false;
	}
	bool deletes2(int num)
	{
		int row=0;
		int col=0;
		std::vector<int> v;
		if(finds(num,row,col))
		{
			for(int i=row;i<m_rowSize;++i)
			{
				for(int j=col;j<m_colSize;++j)
				{
					if(i==row&&j==col)
					{	
						m_young[i][j]=99;
						continue;
					}
					v.push_back(m_young[i][j]);
					m_young[i][j]=99;
				}
			}
			
			for(auto& i:v)
			{
				inserts2(i);
			}
		
		}
		return false;
	}
private:
	int m_rowSize;
	int m_colSize;
	std::vector<std::vector<int>> m_young;
};
void test_youngTableau()
{
	{
		youngTableau you(4,5);
		you.inserts(5);
		you.inserts(4);
		you.inserts(10);
		you.inserts(9);
		you.inserts(3);
		//you.prints();
		you.inserts(2);
		//you.prints();
		you.inserts(8);
		//you.prints();
		you.inserts(6);
		//you.prints();
	}
	{
		youngTableau you(4,5);
		you.inserts2(5);
		you.inserts2(4);
		you.inserts2(10);
		you.inserts2(9);
		you.inserts2(3);
		you.inserts2(2);
		you.inserts2(8);
		you.inserts2(6);
		you.prints();
		int row=0;
		int col=0;
		if(you.finds(8,row,col))
		{
			std::cout<<row<<":"<<col<<std::endl;
		}
		// if(!you.finds(20,row,col))
		// {
		// 	std::cout<<row<<":"<<col<<std::endl;
		// }
		if(you.finds(5,row,col))
		{
			std::cout<<row<<":"<<col<<std::endl;
		}
		// you.deletes2(5);
		// you.prints();
		// you.deletes2(8);
		// you.prints();
		you.deletes(5);
		you.prints();
		you.deletes(8);
		you.prints();
	}
	
}
void twoSum(std::vector<int> arr,int sum)
{
	int i=0;
	int j=arr.size()-1;
	while(i<j)
	{
		if(arr[i]+arr[j]>sum)
		{
			--j;
		}
		else if(arr[i]+arr[j]<sum)
		{
			++i;
		}
		else
		{
			std::cout<<arr[i]<<"+"<<arr[j]<<"="<<sum<<std::endl;
			++i;
			--j;
		}
	}
}
void eratosthenes(std::vector<int>& prime,int n)
{
	std::vector<bool> v(n+1,true);//set all prime
	for(int i=2;i<=(int)std::sqrt(n);++i)
	{
		if(v[i])
		{
			for(int t=i;;++t)
			{
				int num=t*i;
				if(num<=n)
				{
					
					v[num]=false;
				}
				else
				{
					//std::cout<<num<<std::endl;
					break;
				}
			}
		}			
	}
	std::cout<<"---------------------"<<std::endl;
	for(int j=2;j<n+1;++j)
	{
		if(v[j])
			prime.push_back(j);
	}
}
void test_twoSum()
{
	std::vector<int> v{0,3,7,9,11,14,16,17};
	twoSum(v,20);
}
int twoSum2(const std::vector<int>& arr,int index,int sum)
{
	int i=0;
	int j=index-1;
	int count=0;
	//int sum=arr[index];
	while(i<j)
	{
		if((arr[i]+arr[j])>sum)
		{
			--j;
		}
		else if((arr[i]+arr[j])<sum)
		{
			++i;
		}
		else
		{
			++count;
			//std::cout<<arr[i]<<"+"<<arr[j]<<"="<<sum<<"---->"<<count<<std::endl;
			++i;
			--j;
		}
	}
	return count;
}
int findMinIndex(const std::vector<int>& arr,int interNum)
{
	int low=0;
	int high=arr.size()-1;
	
    while(low<=high)
    {
    	int mid=(low+high)/2;
    	if(arr[mid]==interNum)
    	{
    		return mid;
    	}
    	else if(arr[mid]>interNum)
    	{
    		high=mid-1;
    	}
    	else
    	{
    		low=mid+1;
    	}
    }
    return low;
}
void primeSum(const std::vector<int>& arr,int size)
{
	int num=0;
	int prime=0;
	for(int i=0;i<size;++i)
	{
		int j=findMinIndex(arr,i);
		j=twoSum2(arr,j,i);
		//std::cout<<arr[i]<<": "<<j<<std::endl;
		if(j>num)
		{
			num=j;
			prime=i;
			std::cout<<prime<<": "<<num<<std::endl;
		}
	}
	std::cout<<prime<<": "<<num<<std::endl;
}
void test_primeSum()
{
	std::vector<int> v;
	const int N=1000000;
	eratosthenes(v,N);
	
	// for(auto& i:v)
	// {
	// 	std::cout<<i<<" ";
	// }
	// std::cout<<std::endl;
	// std::cout<<v.size()<<std::endl;
	 primeSum(v,N);
	// {
	// 	int index=findMinIndex(v,10);
	// 	std::cout<<index<<":"<<v[index]<<std::endl;
	// 	index=findMinIndex(v,50);
	// 	std::cout<<index<<":"<<v[index]<<std::endl;
	// 	index=findMinIndex(v,100);
	// 	std::cout<<index<<":"<<v[index]<<std::endl;
	// }
}
void countSort(std::vector<int>& arr)
{
	int maxN=0;
	int minN=0;
	for(auto& i:arr)
	{
		if(i>maxN)
			maxN=i;
		if(i<minN)
			minN=i;
	}
	std::vector<int> aux(maxN-minN+1,0);
	for(int i=0;i<arr.size();++i)
	{
		++aux[arr[i]];
	}
	for(int i=1;i<aux.size();++i)
	{
		aux[i]+=aux[i-1];
	}
	// for(auto& i:aux)
	// {
	// 	std::cout<<i<<" ";
	// }
	// std::cout<<std::endl;
	std::vector<int> ret(arr.size(),0);
	for(int i=arr.size()-1;i>=0;--i)
	{
		int temp=arr[i];
		int locate=--aux[temp];
		ret[locate]=arr[i];
	}
	arr=ret;
}
void test_countSort()
{
	std::vector<int> arr{2,5,3,0,2,3,0,3};
	countSort(arr);
	for(auto& i:arr)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
int LIS1(const std::vector<int>& arr,std::vector<int>& pre)
{
	int size=arr.size();
	std::vector<int> lis(size,1);
	//std::vector<int> pre(size,-1);
	int ret=0;
	int index=0;
	for(int i=1;i<size;++i)
	{
		for(int j=0;j<i;++j)
		{
			if(arr[i]>arr[j])
			{
				//lis[i]=std::max(lis[i],lis[j]+1);
				if(lis[i]<lis[j]+1)
				{
					//pre[i]=j;
					index=j;
					lis[i]=lis[j]+1;
				}
			}
		}
		if(ret<lis[i])
		{
			ret=lis[i];
			pre[i]=index;
		}
		//ret=std::max(ret,lis[i]);
	}
	return ret;
}
void getLis(const std::vector<int>& arr,const std::vector<int>& pre)
{
	for(auto& i:pre)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	int lis=0;
	for(int i=0;i<arr.size();++i)
	{
		if(pre[i]!=-1)
		{
			std::cout<<arr[pre[i]]<<" ";
			lis=i;
		}
	}
	std::cout<<arr[lis]<<std::endl;
}
void test_LIS()
{
	{
		std::vector<int> arr{1,4,6,2,8,9,7};
		std::vector<int> pre(arr.size(),-1);
		std::cout<<LIS1(arr,pre)<<std::endl;
		getLis(arr,pre);
	}
	{
		std::vector<int> arr{1,2,3,4,5,6,7};
		std::vector<int> pre(arr.size(),-1);
		std::cout<<LIS1(arr,pre)<<std::endl;
		getLis(arr,pre);
	}
	{
		std::vector<int> arr{2,3,1,4,9,5};
		std::vector<int> pre(arr.size(),-1);
		std::cout<<LIS1(arr,pre)<<std::endl;
		getLis(arr,pre);
	}
}
int maxProfitOneTime(const std::vector<int> arr)
{
	int size=arr.size();
	int minValue=arr[0];
	int profit=0;
	for(int i=1;i<size;++i)
	{
		minValue=std::min(minValue,arr[i-1]);
		profit=std::max(profit,arr[i]-minValue);
	}
	return profit;
}
void test_maxProfitOneTime()
{
	std::vector<int> arr{7,1,5,3,6,4};
	int one=maxProfitOneTime(arr);
	std::cout<<one<<std::endl;
}
int maxProfitMultiTimes(const std::vector<int>& prices)
{
	const int N=3;
	int size=prices.size();
	std::vector<std::vector<int>> dp(N+1,std::vector<int>(size,0));
	int ret=0;
	for(int k=1;k<=N;++k)
	{
		for(int i=1;i<size;++i)
		{
			int maxSell=0;
			for(int j=0;j<i;++j)
			{
				if(prices[i]>prices[j])
				maxSell=std::max(maxSell,dp[k-1][j]+prices[i]-prices[j]);
				std::cout<<maxSell<<std::endl;
			}
			dp[k][i]=std::max(maxSell,dp[k][i-1]);
			ret=std::max(dp[k][i],ret);
		}
	}
	for(auto& i:dp)
	{
		for(auto& j:i)
		{
			std::cout<<j<<" ";
		}
		std::cout<<std::endl;
	}
	return ret;
}
int maxProfitMultiTimes2(const std::vector<int>& prices)
{
	const int N=3;
	int size=prices.size();
	std::vector<std::vector<int>> dp(N+1,std::vector<int>(size,0));
	for(int k=1;k<=N;++k)
	{
		int maxSell=dp[k-1][0]-prices[0];
		for(int i=1;i<size;++i)
		{
			dp[k][i]=std::max(maxSell+prices[i],dp[k][i-1]);			
			maxSell=std::max(maxSell,dp[k-1][i]-prices[i]);
			std::cout<<maxSell<<std::endl;
		}
	}
	for(auto& i:dp)
	{
		for(auto& j:i)
		{
			std::cout<<j<<" ";
		}
		std::cout<<std::endl;
	}
	return dp[N][size-1];
}
void test_maxProfitMultiTimes()
{
	std::vector<int> arr{7,1,5,3,6,4};
	int mul=maxProfitMultiTimes2(arr);
	std::cout<<mul<<std::endl;
}
bool isTaskable(
	const std::vector<int>& runUseMemory,
	const std::vector<int>& useMemory,
	int memorySize)
{
	int size=runUseMemory.size();
	std::vector<std::pair<int,int>> ele;
	for(int i=0;i<size;++i)
	{
		ele.push_back(std::make_pair(i,runUseMemory[i]-useMemory[i]));
	}
	std::sort(ele.begin(),ele.end(),[](std::pair<int,int> a,std::pair<int,int> b)
		{
			return a.second>b.second;
		});
	for(auto& i:ele)
	{
		std::cout<<i.first<<":"<<i.second<<" ";
	}
	std::cout<<std::endl;
	bool ret=true;
	int sum=0;
	for(int i=0;i<size;++i)
	{
		sum+=useMemory[ele[i].first];
		std::cout<<sum<<std::endl;
		if(sum>memorySize)
			ret=false;
	}
	return ret;
}
void test_taskSchedule()
{
	const int N=3;//3 tasks
	const int M=14;//memory size
	std::vector<int> runUseMemory{10,8,14};
	std::vector<int> useMemory{4,3,10};
	bool b=isTaskable(runUseMemory,useMemory,M);
	std::cout<<b<<std::endl;
}
int countToNum(int num)
{
	std::vector<int> footprint;
	int step=0;
	for(int i=num;i>=1;)
	{
		footprint.push_back(i);
		if(i%2!=0)
		{
			//step[i]=step[i-1]+1;
			--i;
		}
		else
		{
			// if(step[i-1]>step[i/2])
			// {
			// 	//step[i]=step(i/2)+1;
			// 	i/=2;
			// }
			// else
			{
				//step[i]=step[i-1]+1;
				i/=2;
			}
		}
		++step;
	}
	std::reverse(footprint.begin(),footprint.end());
	for(auto& i:footprint)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	return step;
}
int countToNum2(int n,std::vector<int>& count)
{
	std::cout<<n<<std::endl;
	if(n==1)
		return 0;
	if(n%2!=0)
	{
		if(count[n-1]==0)
		{
			count[n-1]=countToNum2(n-1,count)+1;
			return count[n-1];
		}
		
	}
	else
	{
		int one=0;
		int two=0;
		if(count[n-1]==0)
		{
			one=countToNum2(n-1,count)+1;
		}
		if(count[n/2]==0)
		{
			two=countToNum2(n/2,count)+1;
		}
		
		if(one>two)
		{
			count[n/2]=1;
			return two;
		}
		else
		{
			count[n-1]=1;
			return one;
		}
		
	}
}
void test_countToNum()
{
	//int step=countToNum(2015);
	std::vector<int> v(2016,0);
	int step=countToNum2(2015,v);
	std::cout<<step<<std::endl;
}
void test_out()
{
	test_countToNum();
	// test_taskSchedule();
	// test_maxProfitMultiTimes();
	//test_maxProfitOneTime();
	// test_LIS();
	// test_countSort();
	// test_primeSum();
	//test_twoSum();
	// test_youngTableau();
	// test_merge();
	// test_horseJump();
	// test_sudoku();
	// test_queen();
	//test_fillLake();
	// test_handred();
	//std::cout<<"1"<<std::endl;
	// test_mouseCheese();
	//std::cout<<"2"<<std::endl;
}
}
