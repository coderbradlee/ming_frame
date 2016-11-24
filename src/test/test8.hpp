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
void test_out()
{
	test_longestKsubstring();
	// test_catalan();
	// test_largestBST();
	// test_inpost2pre();
}
}