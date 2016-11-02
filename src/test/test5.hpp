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
namespace test5_namespace
{
	int find_min_in_rotated_array(const int* arr,int size)
	{
		int low=0;
		int high=size-1;
		int mid=(low+high)/2;
		int min=arr[low];
		while(low<high)
		{
			if(min<arr[mid])//min in right half
			{
				low=mid+1;
			}
			else
			{
				high=mid-1;
			}
			mid=(low+high)/2;
			min=arr[low];
		}
		return min; 
	}
	void test_find_min_in_rotated_array()
	{
		int arr[]={4,5,6,7,8,2,3};
		std::cout<<find_min_in_rotated_array(arr,7)<<std::endl;
	}
	void test_out()
	{
		test_find_min_in_rotated_array();
		
	}
}