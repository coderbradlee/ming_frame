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
namespace test7_namespace
{
int getSqrt(int a)
{
	int x=(int)std::sqrt(a);
	std::cout<<x<<":"<<std::sqrt(a)<<std::endl;
	if(x*x>a)
	{
		return x-1;
	}
	return x;
}
int getSqrt2(double a)
{
	if(a==1)
		return 1;
	double x=a/2;
	double t=a;
	while(std::fabs(x-t)>1e-6)
	{
		t=x;
		x=(x+a/x)/2;
	}
	// if(x*x>a)
	// 	return (int)x-1;
	return x;
}
void squareSplit(int n)
{
	std::vector<int> dp(n+1);
	for(int i=0;i<n+1;++i)
		dp[i]=i;
	for(int i=1;i<n+1;++i)
	{
		int k=getSqrt2(i);
		if(k*k==i)
		{
			dp[i]=1;
			continue;
		}
		for(int j=1;j<=k;++j)
		{
			int t=i-k*k;
			if((dp[t]+1)<dp[i])
			{
				dp[i]=dp[t]+1;
			}
		}
	}
	std::cout<<dp[n]<<std::endl;
}
void test_squareSplit()
{
	const int N=201314;
	squareSplit(N);
}
void test_out()
{
	test_squareSplit();
// 	std::cout<<getSqrt(10)<<std::endl;
// 	std::cout<<getSqrt(15)<<std::endl;
// 	std::cout<<getSqrt(16)<<std::endl;
	// std::cout<<getSqrt2(10)<<std::endl;
	// std::cout<<getSqrt2(15)<<std::endl;
	// std::cout<<getSqrt2(16)<<std::endl;
}
}
