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
					to=i+1;
				}
				//std::cout<<len<<":"<<max<<std::endl;
			}
			else
			{
				//i+=len;
				len=1;
			}
		}
		std::cout<<to+1-max<<":"<<to<<std::endl;
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
	void holland(int* arr,int size)
	{
			//begin cur end
		int begin=0;
		int cur=0;
		int end=size-1;
		while(cur<end)
		{
			if(arr[cur]==0)
			{
				if(arr[begin]!=0)
				{
					std::swap(arr[begin],arr[cur]);
				}
				++begin;
				++cur;
			}
			else if(arr[cur]==1)
			{
				++cur;
			}
			else if(arr[cur]==2)
			{
				std::swap(arr[cur],arr[end]);
				--end;
			}
		}
	}
	void test_holland()
	{
		int arr[]={1,2,0,2,1,2,1,0,1};
		holland(arr,9);
		for(auto i:arr)
		{
			std::cout<<i<<" ";
		}
		std::cout<<std::endl;
	}
	typedef struct Bucket
	{
		bool valid;
		int min;
		int max;
		Bucket():valid(false){}
		void add(int n)
		{
			if(!valid)
			{
				min=max=n;
				valid=true;
			}
			else
			{
				if(max<n)
					max=n;
				else if(min>n)
					min=n;
			}
		}
	}bucket;
	int cal_gap(int* arr,int size)
	{
		std::vector<bucket> v(size);
		int max=arr[0];
		int min=arr[0];
		for(int i=1;i<size;++i)
		{
			if(arr[i]>max)
				max=arr[i];
			else if(arr[i]<min)
				min=arr[i];
		}
		int size_of_bucket=(max-min)/size;
		for(int i=0;i<size;++i)
		//arr[i]-min除以桶的大小可得位于哪个桶，桶的大小为max-min/size
		{
			int location=(arr[i]-min)/size_of_bucket;
			if(location>=size)
				location=size-1;
			// bucket b;
			// b.add(arr[i]);
			//v[location]=b;
			v[location].add(arr[i]);
		}
		int j=0;
		int ret=0;
		for(int i=1;i<size;++i)
		{
			if(v[i].valid)
			{
				if(v[i].min-v[j].max>ret)
				{
					ret=v[i].min-v[j].max;
				}	
				j=i;
			}
		}
		for(auto& i:v)
		{
			if(i.valid)
			std::cout<<"["<<i.min<<","<<i.max<<"]"<<std::endl;
		}
		return ret;
	}
	int cal_gap2(int* arr,int size)
	{
		bucket* pbucket=new bucket[size];
		int max=arr[0];
		int min=arr[0];
		for(int i=1;i<size;++i)
		{
			if(max<arr[i])
				max=arr[i];
			else if(min>arr[i])
				min=arr[i];
		}
		int delta=max-min;
		int numbucket;
		for(int i=0;i<size;++i)
		{
			numbucket=(arr[i]-min)*size/delta;
			if(numbucket>=size)
			{
				numbucket=size-1;
			}
			pbucket[numbucket].add(arr[i]);
		}
		int ngap=delta/size;
		int gap;
		int z=0;
		for(int j=1;j<size;++j)
		{
			if(pbucket[j].valid)
			{
				gap=pbucket[j].min-pbucket[z].max;
				if(ngap<gap)
				{
					ngap=gap;
				}
				z=j;
			}
		}
		for(int i=0;i<size;++i)
		{
			if(pbucket[i].valid)
			std::cout<<"["<<pbucket[i].min<<","<<pbucket[i].max<<"]"<<std::endl;
		}
		return ngap;
	}
	void test_cal_gap()
	{
		int arr[]={1,7,14,9,4,13};
		std::cout<<cal_gap(arr,6)<<std::endl;
		int arr2[]={10,7,14,80,4,13,30};
		std::cout<<cal_gap(arr2,7)<<std::endl;
		std::cout<<"----------------"<<std::endl;
		
		std::cout<<cal_gap2(arr,6)<<std::endl;
		
		std::cout<<cal_gap2(arr2,7)<<std::endl;
	}
	void cantor1(std::vector<int> arr,std::vector<int>& ori,int size)
	{
		for(int i=0;i<size;++i)
		{
			for(int j=i+1;j<size;++j)
			{
				if(arr[j]<arr[i])
					++ori[i];
			}
		}
	}
	void cantor2(std::vector<int> arr,std::vector<int>& ori,int size)
	{
		std::vector<int> v(size);
		for(int i=0;i<size;++i)
			v[i]=i+1;
		for(int i=0;i<size;++i)
		{
			ori[i]=v[arr[i]];
			v.erase(v.begin()+arr[i]);
		}
	}
	
	void test_cantor()
	{
		std::vector<int> array{4,6,2,5,3,1};
		std::vector<int> arr{3,4,1,2,1,0};
		std::vector<int> ori(6,0);
		cantor1(array,ori,6);
		
		for(auto i:ori)
		{
			std::cout<<i<<std::endl;
		}
		std::cout<<"-----------------"<<std::endl;
		//ori.clear();
		cantor2(arr,ori,6);
		for(auto i:ori)
		{
			std::cout<<i<<std::endl;
		}
	}
	typedef struct Node
	{
		int data;
		Node* parent;
		Node* left;
		Node* right;
	}Node;
	void cal_frequence(const char* str,int* frequence)
	{
		int len=strlen(str);
		for(int i=0;i<len;++i)
		{
			++frequence[str[i]];
		}
	}
	void print_frequence(int *frequence,int N)
	{
		int j=0;
		for(int i=0;i<N;++i)
		{
			if(i=='\t')
			{
				//std::cout<<i<<std::endl;
				frequence[i]=0;
			}
			if(frequence[i]!=0)
			{
				printf("%c:%d ",i,frequence[i]);
				++j;
			}	
			
			if(j!=0&&j%10==0)
			{
				printf("\n");
				j=0;
			}	
		}
		std::cout<<std::endl;
	}
	void cal_exist_char(int* frequence,int N,std::vector<int>& exist_key)
	{
		int j=0;
		for(int i=0;i<N;++i)
		{
			if(frequence[i]!=0)
			{
				frequence[j]=frequence[i];
				++j;
				exist_key.push_back(i);
			}
		}
	}
	void test_huffman()
	{
		const int N=256;
		const char str[]="When I was young I'd listen to the radio\
						Waitin' for my favorite songs\
						When they played I'd sing along, it made me smile\
						Those were such happy times and not so long ago\
						How I wondered where they'd gone\
						But they're back again just like a long lost friend\
						All the songs I loved so well\
						Every sha-la-la-la\
						Every wo-o-wo-o, still shines\
						Every shing-a-ling-a-ling, that they're startin' to sing's, so fine";

		int frequence[N]={0};
		cal_frequence(str,frequence);
		print_frequence(frequence,N);
		std::vector<int> exist_key;
		//存在的字符保存的exist_key中，个数还是保存在frequence里
		cal_exist_char(frequence,N,exist_key);
		//this should be the same with print_frequence
		for(int i=0;i<exist_key.size();++i)
		{
			printf("%c:%d ",exist_key[i],frequence[i]);
			if(i!=0&&i%10==0)
			{
				printf("\n");
			}	
		}

	}
	void test_out()
	{
		test_huffman();
		// test_cantor();
		// test_cal_gap();
		//test_holland();
		//test_max_subsequence();
		//test_max_subarray();
		//test_min_subarray();
		//test_find_min_in_rotated_array();
	}
}