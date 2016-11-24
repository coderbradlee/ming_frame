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
namespace test8_namespace
{
void inpost2pre(std::string in,std::string post)
{
	if(in.length()<=1||post.length()<=1)
	{
		std::cout<<post<<std::endl;
		return;
	}
	int i=in.find(post[post.size()-1]);//i=4
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
void test_out()
{
	test_inpost2pre();
}
}
;