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
		while(low<high)
		{

			if(arr[high]<arr[mid])//min in right half
			{
				low=mid+1;
			}
			else if(arr[high]>arr[mid])
			{
				high=mid;
			}
			// else
			// {

			// 	return arr[mid];
			// }
			mid=(low+high)/2;
			std::cout<<low<<":"<<mid<<":"<<high<<std::endl;
		}
		return arr[mid]; 
	}
	void test_find_min_in_rotated_array()
	{
		int arr[]={4,5,6,7,8,2,3};
		std::cout<<find_min_in_rotated_array(arr,7)<<std::endl;
		int arr1[]={44,55,66,7,8,9,10};
		std::cout<<find_min_in_rotated_array(arr1,7)<<std::endl;
	}
    void min_subarray(int* arr,int size)
    {
    	int* sum=new int[size];
    	sum[0]=0;
    	int index=1;
    	for(int i=1;i<size;++i)
    	{
    		sum[i]=sum[i-1]+arr[i];
    		if(sum[i]==0)
    			index=i;
    	}
    	std::sort(sum,sum+size);
    	int min=std::abs(sum[1]-sum[0]);
    	
    	for(int i=1;i<size;++i)
    	{
    		if(std::abs(sum[i]-sum[i-1])<min)
    		{
    			min=std::abs(sum[i]-sum[i-1]);
    			index=i;
    		}
    	}
    	std::cout<<min<<std::endl;
    }
    void find_min_subarray(int* arr,int size)
    {
    	std::vector<std::pair<int,int>> sum(size,std::pair<int,int>(0,0));
    	sum[0]=std::make_pair(0,0);
    	int index=1;
    	for(int i=1;i<size;++i)
    	{
    		sum[i]=std::make_pair(sum[i-1].first+arr[i],i);
    		// sum[i]=sum[i-1]+arr[i];
    		// if(sum[i]==0)
    		// 	index=i;
    	}
    	std::sort(sum.begin(),sum.end(),[](std::pair<int,int> x,std::pair<int,int> y){return x.first<y.first;});
    	int min=std::abs(sum[1].first-sum[0].first);
    	
    	for(int i=1;i<size;++i)
    	{
    		if(std::abs(sum[i].first-sum[i-1].first)<min)
    		{
    			min=std::abs(sum[i].first-sum[i-1].first);
    			index=i;
    		}
    	}

    	std::cout<<sum[index+1].second<<":"<<sum[index].second<<std::endl;
    }
	void test_min_subarray()
	{
		int arr[]={1,-2,3,10,-4,7,2,-5};
		///////////0 1 -1 2 12 8 15 17 12
		//min_subarray(arr,8);
		find_min_subarray(arr,8);
	}
	void max_subarray(int* arr,int size)
	{
		int ret=arr[0];
		int sum=arr[0];
		for(int i=0;i<size;++i)
		{
			if(sum>0)
			{
				sum+=arr[i];
			}
			else
			{
				sum=arr[i];
			}
			ret=std::max(ret,sum);
		}
		std::cout<<ret<<std::endl;
	}
	void find_max_subarray(int* arr,int size)
	{
		int ret=arr[0];
		int sum=arr[0];
		int ret_low_index=0;
		int ret_high_index=0;
		int sum_low_index=0;
		int sum_high_index=0;
		for(int i=0;i<size;++i)
		{
			if(sum>0)
			{
				sum+=arr[i];
				sum_high_index=i;
			}
			else
			{
				sum=arr[i];
				sum_low_index=sum_high_index=i;
			}
			if(ret<sum)
			{
				ret=sum;
				ret_low_index=sum_low_index;
				ret_high_index=sum_high_index;
			}
		}
		std::cout<<ret_low_index<<":"<<ret_high_index<<std::endl;
		std::cout<<ret<<std::endl;
	}
	void test_max_subarray()
	{
		int arr[]={1,-2,3,10,-4,7,2,-5};
		///////////0 1 -1 2 12 8 15 17 12
		//max_subarray(arr,8);
		find_max_subarray(arr,8);
	}
	void max_subsequence(int* arr,int size)
	{
		int len=1;
		int max=0;
		int to=0;
		for(int i=0;i<size-1;++i)
		{
			if((arr[i]+1)==arr[i+1])
			{
				++len;
				if(len>max)
				{
					max=len;
				}
				//std::cout<<len<<":"<<max<<std::endl;
			}
			else
			{
				//i+=len;
				len=1;
				to=i+1;
			}
		}
		std::cout<<to<<":"<<max<<std::endl;
	}
	void test_max_subsequence()
	{
		int arr[]={1,2,39,2,3,4,5,10,22};
		max_subsequence(arr,9);
		int arr2[]={1,2,39,2,3,4,5,6,10};
		max_subsequence(arr2,9);
		int arr3[]={1,2,3,4,5,6,2,39,10};
		max_subsequence(arr3,9);
	}
	void test_out()
	{
		test_max_subsequence();
		//test_max_subarray();
		//test_min_subarray();
		//test_find_min_in_rotated_array();
	}
}