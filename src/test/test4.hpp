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
namespace test4_namespace
{
	using std::string;
	typedef struct linknode
	{
		int value;
		linknode* next;
		linknode(int val):value(val),next(nullptr){}
	}node;
	void print(node* phead)
	{
		node* p=phead->next;
		while(p!=nullptr)
		{
			std::cout<<p->value<<"-->";
			p=p->next;
		}	
		std::cout<<"end"<<std::endl;
	}
	void destroy(node* phead)
	{
		node* p;
		while(phead!=nullptr)
		{
			std::cout<<"destroy:"<<phead->value<<std::endl;
			p=phead->next;
			delete phead;
			phead=p;
		}
	}
	void reverse(node* phead,int start,int end)
	{
		node* prev;
		for(int i=0;i<start-1;++i)
		{	
			prev=phead->next;
			phead=prev;
		}
		node* pstart=prev;
		prev=prev->next;
		node* pcur=prev->next;
		for(int i=start;i<end;++i)
		{	
			node* temp=pstart->next;
			pstart->next=pcur;
			prev->next=pcur->next;
			pcur->next=temp;
			pcur=prev->next;
		}
	}
	void test()
	{
		node* phead=new node(0);
		node* pindex=phead;
		for(int i=0;i<10;++i)
		{
			node* p=new node(rand()%100);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		reverse(phead,3,5);
		print(phead);
		destroy(phead);
	}
	void deleteDuplicate2(node* phead)
	{
		node* prev=phead;
		node* p=phead->next->next;
		phead=phead->next;
		
		while(p)
		{
			if(p->value==phead->value)
			{
				int temp=p->value;
				while(p->value==temp)
				{
					phead->next=p->next;
					delete p;
					p=phead->next;
				}
				prev->next=p;
				std::cout<<"delete:"<<phead->value<<std::endl;
				delete phead;
				phead=p;
				p=p->next;
				std::cout<<"::"<<prev->value<<std::endl;
				std::cout<<"::"<<phead->value<<std::endl;
				std::cout<<"::"<<p->value<<std::endl;
			}
			else
			{
				p=p->next;
				phead=phead->next;
				prev=prev->next;
			}
		}
	}
	node* partition(node* phead,int value)
	{
		node* left=phead;
		node* right=new node(0);
		node* leftindex=phead;
		node* rightindex=right;
		while(phead&&phead->next)
		{
			if(phead->next->value<value)
			{
				leftindex->next=phead->next;
				phead=phead->next;
				leftindex=leftindex->next;
				std::cout<<":"<<leftindex->value<<std::endl;
			}
			else
			{
				rightindex->next=phead->next;
				leftindex->next=phead->next->next;
				phead=leftindex;
				rightindex=rightindex->next;
				rightindex->next=nullptr;
				std::cout<<"::"<<rightindex->value<<std::endl;
			}
		}
		leftindex->next=right->next;
		return left;
	}
	void test2()
	{
		node* phead=new node(0);
		int digit[]={1,2,8,3,4,4,4,5,6};
		node* pindex=phead;
		for(int i=0;i<8;++i)
		{
			node* p=new node(digit[i]);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		//deleteDuplicate(phead);
		//deleteDuplicate2(phead);
		partition(phead,4);
		print(phead);
		destroy(phead);
	}
	void topologic(std::vector<int>& output,std::vector<std::vector<int>> graph)
	{
		const int cnt=13;
  		std::vector<int> indegree(cnt);
  		for(int i=0;i<cnt;++i)
  		{
  			for(int j=0;j<cnt;++j)
  			{
  				indegree[i]+=graph[j][i];
  			}
  		}
  		std::copy(indegree.begin(), indegree.end(), std::ostream_iterator<int>(std::cout, "->"));
  		std::cout<<std::endl;
  		while(output.size()<cnt)
  		{
  			std::queue<int> temp;
	  		for(int i=0;i<cnt;++i)
	  		{
	  			if(indegree[i]==0)
	  				temp.push(i);
	  		}
	  		while(!temp.empty())
	  		{
	  			int value=temp.front();
	  			temp.pop();
	  			output.push_back(value);
	  			std::cout<<output.size()<<std::endl;
	  			indegree[value]=-1;
	  			for(int i=0;i<cnt;++i)
	  			{
	  				if(graph[value][i]==1)
	  				{
	  					indegree[i]-=1;
	  				}
	  			}
	  		}
  		}
  				
	}
	void testtopologic()
	{
		std::vector<std::vector<int>> v
		{{0,1,0,0,0,1,1,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {1,0,0,1,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,1,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,1,0,0,0,0,0,0,0,0},
		 {0,0,0,0,1,0,0,0,0,1,0,0,0},
		 {0,0,0,0,0,0,1,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,1,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,1,1,1},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0,0,0,1},
		 {0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		std::vector<int> output;
		topologic(output,v);
		std::copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, "->"));
		std::cout<<std::endl;
	}
	int calcpath(const std::vector<std::vector<int>>& graph)
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
	void testshortpath()
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
	}
	int get_ml(const string& p)
	{
		int len=p.length();
		std::queue<int> q;
		int ml=0;
		int start=-1;
		for(int i=0;i<len;++i)
		{
			if(p[i]=='(')
			{
				q.push(i);
			}
			else
			{
				if(q.empty())
				{
					start=i;
				}
				else
				{
					q.pop();
					if(q.empty())
					{
						if(ml<i-start)
							ml=i-start;
					}
					else
					{
						if(ml<i-q.front())
							ml=i-q.front();
					}
				}
			}
		}
		return ml;
	}
	void test_parenthesis()
	{
		string parenthesis="(())()()";
		int maxlength=get_ml(parenthesis);
		std::cout<<maxlength<<std::endl;
	}
	bool is_operator(char c)
	{
		return c=='+'||c=='-'||c=='*'||c=='/';
	}
	
	int reversepolishnotation(const string& s)
	{
		int len=s.length();
		int ret=0;
		std::stack<int> stack_num;
		for(int i=0;i<len;++i)
		{
			if(is_operator(s[i]))
			{
				int second=stack_num.top();
				stack_num.pop();
				int first=stack_num.top();
				stack_num.pop();
				std::cout<<first<<":"<<second<<std::endl;
				if(s[i]=='+')
				{
					stack_num.push(first+second);
				}
				else if(s[i]=='-')
				{
					stack_num.push(first-second);
				}
				else if(s[i]=='*')
				{
					stack_num.push(first*second);
				}
				else if(s[i]=='/')
				{
					stack_num.push(first/second);
				}
			}
			else
			{
				char c=s[i];
				const char* num=&c;
				std::cout<<"push:"<<atoi(num)<<std::endl;
				stack_num.push(atoi(num));
			}
		}
		ret=stack_num.top();
		stack_num.pop();
		if(!stack_num.empty())
		{
			ret=0;
		}
		return ret;
	}
	void test_reversepolishnotation()
	{
		string s="21+3*";
		int ret=reversepolishnotation(s);
		std::cout<<ret<<std::endl;
	}
	void reversestring(char* start,char* end)
	{
		while(start<end)
		{
			char c=*start;
			*start=*end;
			*end=c;
			++start;
			--end;
		}
	}
	void shift()
	{
		char s[]="abcdef";
		char* p=s;
		reversestring(p,p+1);
		reversestring(p+2,p+5);
		reversestring(p,p+5);
		std::cout<<s<<std::endl;
	}
	void FindAnswer(const char* str1,const char* str2,const std::vector<std::vector<int>>& graph, std::vector<string>& solution,string& answer,int row,int col)
	{
		while(row>0&&col>0)
		{
			if(str1[row]==str2[col])
			{
				answer.push_back(str1[row]);
				--row;--col;
			}
			else
			{
				if(graph[row][col-1]==graph[row-1][col])
				{
					int s = (int)answer.size();
					FindAnswer(str1,str2, graph,solution,answer,row-1,col);
					answer.resize(s);
					FindAnswer(str1,str2, graph,solution,answer,row,col-1);
					answer.resize(s);
					break;
				}
				else if(graph[row][col-1]>graph[row-1][col])
				{
					--col;
				}
				else
					--row;
			}
		}
		if(row==0||col==0)
		{
			solution.push_back(answer);
			std::cout<<answer<<std::endl;
			std::reverse(solution.back().begin(), solution.back().end());
			return;
		}
	}
	void LCS2(const char* str1, const char* str2, std::vector<string>& solution)
	{
		int len1=strlen(str1);
		int len2=strlen(str2);

		std::vector<std::vector<int>> graph(len1+1,std::vector<int>(len2+1));
		for(int i=0;i<len1+1;++i)
		{
			graph[i][0]=0;
		}
		for(int i=0;i<len2+1;++i)
		{
			graph[0][i]=0;
		}
		for(int i=1;i<len1+1;++i)
		{
			for(int j=1;j<len2+1;++j)
			{
				if(str1[i]==str2[j])
				{
					graph[i][j]=graph[i-1][j-1]+1;
				}
				else
				{
					if(graph[i-1][j]>graph[i][j-1])
						graph[i][j]=graph[i-1][j];
					else
						graph[i][j]=graph[i][j-1];
				}
			}
		}	
		string answer;
		FindAnswer(str1, str2, graph,solution,answer,len1,len2);
	}
	void test_lcs()
	{
		const char* str1 = "BDCABA";//BDCABA
		const char* str2 = "ABCBDAB";//ABCBDAB
		//std::cout<<LCS(str1,str2)<<std::endl;
		std::vector<string> v;
		LCS2(str1,str2,v);
		std::cout<<"----------------"<<std::endl;
		std::copy(v.begin(),v.end(),std::ostream_iterator<string>(std::cout,"\n"));
		std::cout<<std::endl;
	}
	// void insert2(const int* a,int* b,int* prev,int index,int& bsize)
	// {
	// 	if(index<=0)
	// 	{
	// 		b[0]=1;
	// 		v[0]=a[0];
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		insert2(a,b,v,index-1);
	// 		if(a[index]>v[index-1])
	// 		{
	// 			b[index]+=b[index-1];
	// 			v[index]=a[index];
	// 		}
	// 		else
	// 		{
	// 			b[index]=b[index-1];
	// 		}
	// 	}
	// }
	int LIS(int* a,int len)
	{
		int* b=new int[len];
		int* v=new int[len];
		//for(int i=0;i<len;++i)
		{
			//insert2(a,b,v,len-1);
		}
		for(int i=0;i<len;++i)
		{
			std::cout<<v[i]<<"->";
		}
		std::cout<<"end"<<std::endl;
		for(int i=0;i<len;++i)
		{
			std::cout<<b[i]<<"->";
		}
		std::cout<<"end"<<std::endl;
		return b[len-1];
	}
	void test_lis()
	{
		int a[] = {1,4,6,2,8,9,7};
		int size = sizeof(a) / sizeof(int);
		int len = LIS(a, size);
		std::cout << len << std::endl;
	}
	void print(const int* a,int size)
	{
		for(int i=0;i<size;++i)
			std::cout<<a[i]<<' ';
		std::cout<<std::endl;
	}
	void permutation(int* a,int size,int n)
	{
		if(n==size-1)
		{
			print(a,size);
			return;
		}
		for(int i=n;i<size;++i)
		{
			std::swap(a[i],a[n]);
			permutation(a,size,n+1);
			std::swap(a[i],a[n]);
		}
	}
	
	bool is_duplicate(const int* a,int i,int j)
	{
		while(i<j)
		{
			if(a[i]==a[j])
			{
				std::cout<<a[i]<<std::endl;
				return true;
			}	
			++i;
		}
		return false;
	}
	void permutation2(int* a,int size,int n)
	{
		if(n==size-1)
		{
			print(a,size);
			return;
		}
		for(int i=n;i<size;++i)
		{
			if(is_duplicate(a,n,i))
				continue;
			std::swap(a[i],a[n]);
			permutation2(a,size,n+1);
			std::swap(a[i],a[n]);
		}
	}
	void test_permutation()
	{
		//int x[]={1,2,3};
		//permutation(x,3,0);
		//std::cout<<"-----------------"<<std::endl;
		//int y[]={2,1,3};
		//permutation(y,3,0);
		//std::cout<<"-----------------"<<std::endl;
		int z[]={1,2,2,3};
		permutation2(z,4,0);
		std::cout<<"-----------------"<<std::endl;
		int zz[]={2,1,2,3};
		permutation2(zz,4,0);
	}
	int find_min(int *a,int start,int size)
	{
		int place=a[start];
		int min=a[start+1];
		int index=start;
		++start;
		while(start<size)
		{
			if(a[start]>place&&a[start]<min)
			{
				min=a[start];
				index=start;
			}	
			++start;
		}
		return index;
	}
	bool next_permutation(int *a,int size)
	{
		int place_to_swap=-1;
		for(int i=size-1;i>0;--i)
		{
			if(a[i-1]<a[i])
			{
				place_to_swap=i-1;
			}
		}
		if(place_to_swap==-1)
			return false;
		int min=find_min(a,place_to_swap,size);
		std::swap(a[place_to_swap],a[min]);
		print(a,size);
		std::reverse(&a[place_to_swap+1],&a[size]);
		return true;
	}  
	void test_next_permutation()
	{
		int a[]={9,2,6,5,2,0};
		next_permutation(a,6);
		print(a,6);
	}
	void manacher(char* s,int* p,int len)
	{
		//s="abba"; after pad:"$#a#b#b#a"
		int size=2*len+1;
		p[0]=1;
		int mx=1;
		int id=0;
		for(int i=1;i<size;++i)
		{
			if(i<mx)
			{
				p[i]=std::min(p[2*id-i],mx-i);
			}
			else
			{
				p[i]=1;
			}
			//for(;(s[i-p[i]]==s[i+p[i]]);p[i]++);
			// while((i != p[i]) && (((i+p[i]) % 2 == 1)
			// || (s[(i+p[i])/2-1] == s[(i-p[i])/2-1])))
			// p[i]++;
			while(i!=p[i])
			{
				char prev=s[i-p[i]-1];
				char after=s[i+p[i]-1];
				if(prev==after)
				{
					p[i]++;
				}
				else
				{
					break;
				}
			}
			if(mx<i + p[i])
			{
				mx=i + p[i];
				id=i;
			}
		}
	}
	void test_manacher()
	{
		char s[17]="12212321";
		int len=strlen(s);
		int size=2*len+1;
		int p[size]={0};
		manacher(s,p,len);
		print(p,size);
	}
	void test_out()
	{
		test_manacher();
		//test_next_permutation();
		//test_permutation();
		//test_lis();//result is not right,rewrite it later
		//test_lcs();
		//shift();
		//test_reversepolishnotation();
		//test_parenthesis();
		//testshortpath();
		//testtopologic();
	}
}