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
	std::vector<int> pre(n+1);
	for(int i=0;i<n+1;++i)
	{
		dp[i]=i;
		pre[i]=i-1;
	}
	pre[0]=0;
	for(int i=1;i<n+1;++i)
	{
		int k=getSqrt2(i);
		if(k*k==i)
		{
			dp[i]=1;
			pre[i]=0;
			continue;
		}
		for(int j=1;j<=k;++j)
		{
			int t=i-j*j;
			if((dp[t]+1)<dp[i])
			{
				dp[i]=dp[t]+1;
				pre[i]=t;
			}
		}
	}
	std::cout<<dp[n]<<std::endl;
	{
		//get answer from pre
		int step=dp[n];
		while(step>0)
		{
			std::cout<<getSqrt2(n-pre[n])<<" ";
			n=pre[n];
			// if(n<0)
			// 	break;
			--step;
		}
		std::cout<<std::endl;
	}
}

int squareSplitRecursion(int n,int dp,int& step)
{
	// if(dp==1)
	 return 1;
	// int k=getSqrt2(dp);
	// for(int j=1;j<k;++j)
	// {
	// 	int t=dp-j*j;
	// 	if((dp[t]+1)<dp[i])
	// 	{
	// 		dp[i]=dp[t]+1;
	// 		pre[i]=t;
	// 	}
	// }
	// int temp=getSqrt2(n-dp);
	// if(temp*temp==(n-dp))
	// {
	// 	++step;
	// }
	// else
	// {
	// 	squareSplitRecursion(n,dp,step);
	// }
	
}
void test_squareSplit()
{
	const int N=201314;
	squareSplit(N);
}
void chargeChange(std::vector<int> dom,int n)
{
	std::vector<std::vector<int>> dp(dom.size(),std::vector<int>(n+1,0));
	 
	for(int i=0;i<=n;++i)
	{
		dp[0][i]=1;
	}
	for(size_t i=0;i<dom.size();++i)
	{
		dp[i][0]=1;
	}
	for(size_t i=1;i<dom.size();++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=dom[i])
			{
				dp[i][j]=dp[i-1][j]+dp[i][j-dom[i]];
			}
			else
				dp[i][j]=dp[i-1][j];
			
		}
	}
	std::cout<<dp[dom.size()-1][n]<<std::endl;
}
void chargeChange2(std::vector<int> dom,int n)
{
	std::vector<int> dp(n+1,1);
	std::vector<int> last(n+1,1);
	 
	for(size_t i=1;i<dom.size();++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=dom[i])
			{
				dp[j]=last[j]+dp[j-dom[i]];
				last[j]=dp[j];
			}
		}
	}
	std::cout<<dp[n]<<std::endl;
}
void test_chargeChange()
{
	std::vector<int> dom{1,2,5,10,20,50,100};
	const int N=5;
	chargeChange(dom,N);
	chargeChange2(dom,N);
}
bool isScramble(std::string one,std::string two)
{
	int oneLength=one.length();
	int twoLength=two.length();

	if(oneLength!=twoLength)
		return false;
	if(oneLength==0)
		return true;
	if(oneLength==1)
		return one[0]==two[0];
	for(int i=1;i<oneLength;++i)
	{
		bool oneWay=isScramble(one.substr(0,i),two.substr(0,i))&&isScramble(one.substr(i,oneLength-i),two.substr(i,oneLength-i));
		bool twoWay=isScramble(one.substr(0,i),two.substr(oneLength-i,i))&&isScramble(one.substr(i,oneLength-i),two.substr(0,oneLength-i));
		if(oneWay||twoWay)
			return true;
	}
	return false;
}
void test_isScramble()
{
	using std::string;
	string one="great";
	string two="rgeat";
	string three="rteac";
	std::cout<<isScramble(one,two)<<std::endl;
	std::cout<<isScramble(one,three)<<std::endl;
}
double buffon2(double a,double L)
{
	double X=a*1000;
	double Y=a*1000;
	int N=100000;
	int c=0;
	double x1,x2,y1,y2;
	double d,y;
	//////////////////////////////////
	std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_y(0,X);  
	auto dice_y= std::bind(dis_y,gen);
	////////////////////////////////////////
	for(int i=0;i<N;++i)
	{
		x1=dice_y();
		y1=dice_y();
		x2=dice_y();
		y2=dice_y();
		d=std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		y=(y2-y1)*L/d+y1;
		if ((int)(y1/a)!=(int)(y/a))
		{
			++c;
		}
	}	
	return 2*L*N/(a*c);
}
double buffon(double a,double L)
{
	double y;
	double theta;
	int c=0;
	int n=1000000;
	std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_y(0,a/2);  
	auto dice_y= std::bind(dis_y,gen);
	std::uniform_real_distribution<> dis_theta(0,180);  
	auto dice_theta= std::bind(dis_theta,gen);
	for(int i=0;i<n;++i)
	{
		y=dice_y();
		theta=dice_theta();
		if(y<L*std::sin(theta)/2)
			++c;
	}
	printf("%10f:%10f||",y,theta);
	return 2*(double)(n*L)/(double)(c*a);
}
void test_buffon()
{
	double a=100;
	double L;
	double pi;
	double avg=0;
	double count=0;
	for(L=a;L>1;L-=1)
	{
		//pi=buffon(a,L);
		pi=buffon2(a,L);
		//std::cout<<"pi:"<<pi<<std::endl;
		printf("%3d:%8f\n",(int)L ,pi);
		avg+=pi;
		++count;
	}
	avg/=count;
	std::cout<<"avg:"<<avg<<std::endl;
}
int randomSong1(const std::vector<int>& song)
{
	int N=song.size();
	std::vector<int> accumulate(N,0);
	accumulate[0]=song[0];
	for(int i=1;i<N;++i)
	{
		accumulate[i]=accumulate[i-1]+song[i];
	}
	std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_y(0,accumulate[N-1]);  
	auto dice_y= std::bind(dis_y,gen);
	int songChoiced=dice_y();
	//std::cout<<songChoiced<<std::endl;
	int low=0;
	int high=N-1;
	int mid=(low+high)/2;
	while(low<high)
	{
		if(accumulate[mid]>songChoiced)
		{
			high=mid;
		}
		else if (accumulate[mid]<songChoiced)
		{
			low=mid+1;
		}
		else
		{
			low=mid;
			break;
		}
		mid=(low+high)/2;
	}
	//std::cout<<"choice song["<<low<<"]:"<<song[low]<<std::endl;
	return low;
}
int randomSong2(const std::vector<int>& song)
{
	int N=song.size();
	int sum=0;
	for(int i=0;i<N;++i)
	{
		sum+=song[i];
	}
	std::vector<float> probability(N,0);
	for(int i=0;i<N;++i)
	{
		probability[i]=(float)song[i]/sum;
		//printf("%f ", probability[i]);
	}
	//printf("\n");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_index(0,N);  
	auto dice_index= std::bind(dis_index,gen);
	////////////////////////////////////
	std::random_device rd1;
	std::mt19937 gen1(rd1());
	std::uniform_real_distribution<> dis_y(0,1);  
	auto dice_y= std::bind(dis_y,gen1);

	while(1)
	{
		int index=(int)dice_index();
		float songChoiced=dice_y();
		
		if(probability[index]>songChoiced)
		{
			//printf("probability[%d]=%f:%f\n", index,probability[index],songChoiced);
			return index;
		}
	}
}
void test_randomSong()
{
	std::vector<int> song{43,63,43,89,322,2,5,32};
	float sum = std::accumulate(song.begin(), song.end(), 0);
	for(auto& i:song)
	{
		printf("%f ", i/sum);
	}
	printf("\n");
	{
		std::cout<<"--------1--------"<<std::endl;
		std::vector<int> accumulateTimes(song.size(),0);
		for(int i=0;i<10000;++i)
		{
			++accumulateTimes[randomSong1(song)];
		}
		for(int i=0;i<accumulateTimes.size();++i)
		{
			printf("%f ", (float)accumulateTimes[i]/10000);
		}
		printf("\n");
	}
	{
		std::cout<<"--------2--------"<<std::endl;
		std::vector<int> accumulateTimes(song.size(),0);
		for(int i=0;i<10000;++i)
		{
			++accumulateTimes[randomSong2(song)];
		}
		for(int i=0;i<accumulateTimes.size();++i)
		{
			//printf("%d ", accumulateTimes[i]);
			printf("%f ", (float)accumulateTimes[i]/10000);
		}
		printf("\n");
	}
}
void test_map()
{
	std::map<int, std::string> maps;
	maps.insert(std::map<int, std::string>::value_type(1,"1"));

	maps.insert(std::make_pair(2,"2"));

	maps.insert(std::pair(3,"3"));
	for(auto& i:maps)
		std::cout<<i.first<<":"<<i.second<<std::endl;
}
void test_out()
{
	test_randomSong();
	// test_buffon();
	// std::cout<<sizeof(float)<<std::endl;//4B,6-7位精度
	// std::cout<<sizeof(double)<<std::endl;//8B，15-16位精度
	// std::cout<<sizeof(long double)<<std::endl;
	// test_isScramble();
	// test_chargeChange();
	// test_squareSplit();
	// 	std::cout<<getSqrt(10)<<std::endl;
	// 	std::cout<<getSqrt(15)<<std::endl;
	// 	std::cout<<getSqrt(16)<<std::endl;
	// std::cout<<getSqrt2(10)<<std::endl;
	// std::cout<<getSqrt2(15)<<std::endl;
	// std::cout<<getSqrt2(16)<<std::endl;
}
}
