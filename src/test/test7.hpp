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
	//double Y=a*1000;
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
		for(size_t i=0;i<accumulateTimes.size();++i)
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
		for(size_t i=0;i<accumulateTimes.size();++i)
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
	maps.insert(std::map<int, std::string>::value_type(0,"0"));
	maps.insert(std::map<int, std::string>::value_type(1,"1"));

	maps.insert(std::make_pair(2,"2"));

	auto test=maps.insert(std::pair<int, std::string>(3,"3"));
	if(test.second)
	{
		std::cout<<"insert successfully"<<std::endl;
	}
	auto test22=maps.insert(std::pair<int, std::string>(3,"3"));
	if(!test22.second)
	{
		std::cout<<"insert fail"<<std::endl;
	}
	// for(auto& i:maps)
	// 	std::cout<<i.first<<":"<<i.second<<std::endl;
	for(auto it=maps.begin();it!=maps.end();)
	{
		if(it->second=="2")
			//it=maps.erase(it);
			maps.erase(it++);
		else
			++it;
	}
	int x=maps.size();
	std::cout<<x<<std::endl;
	// for(int i=0;i<x;++i)
	// {
	// 	std::cout<<i<<"::"<<maps[i]<<std::endl;
	// }
	for(auto& i:maps)
		std::cout<<i.first<<":"<<i.second<<std::endl;
}
int chessCount(int N)
{
	int ret=0;
	for(int i=1;i<N;++i)
	{
		for(int j=1;j<N;++j)
		{
			ret+=std::min(i,j);
		}
	}
	return ret;
}
void test_chessCount()
{
	const int N=19;
	int n=chessCount(N);
	std::cout<<n<<std::endl;
}

void bigInt()
{
	std::list<int> sum{1};

	for(int i=1;i<=100;++i)
	{
		int carry=0;
		for(auto& j:sum)
		{
			int temp=j*i+carry;
			j=temp%10;
			carry=temp/10;
		}
		while(carry!=0)
		{
			sum.push_back(carry%10);
			carry/=10;
		}
	}
	std::cout<<sum.size()<<std::endl;
	int line=0;
	int space=0;
	for(auto i=sum.rbegin();i!=sum.rend();++i)
	{
		std::cout<<*i;
		++space;
		if(space%10==0)
		{
			std::cout<<" ";
			++line;
		}	
		if(line==5)
		{
			std::cout<<std::endl;
			line=0;
		}
	}
}
void test_bigInt()
{
	bigInt();
}
void bfs(const std::vector<std::vector<int>>& chess)
{
	const int N=chess.size();
	std::vector<int> step(N,0);
	std::vector<int> path(N,0);
	path[0]=1;
	std::queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int from =q.front();
		q.pop();
		for(int i=0;i<N;++i)
		{
			if(chess[from][i]!=0)
			{
				if((step[i]>step[from]+1)||(step[i]==0))
				{
					step[i]=step[from]+1;
					q.push(i);
					path[i]=path[from];
				}
				else if(step[i]==step[from]+1)
				{
					path[i]+=path[from];
				}
			}
		}
	}
	std::cout<<step[N-1]<<":"<<path[N-1]<<std::endl;
}
void test_bfs()
{
	const int N=16;
	std::vector<std::vector<int>> chess(N,std::vector<int>(N,0));
	chess[0][1]=chess[0][4]=1;
	chess[1][5]=chess[1][0]=chess[1][2]=1;
	chess[2][1]=chess[2][6]=chess[2][3]=1;
	chess[3][2]=chess[3][7]=1;
	chess[4][0]=chess[4][5]=1;
	chess[5][1]=chess[5][4]=chess[5][6]=chess[5][9]=1;
	chess[6][2]=chess[6][5]=chess[6][7]=chess[6][10]=1;
	chess[7][3]=chess[7][6]=1;
	chess[8][9]=chess[8][12]=1;
	chess[9][8]=chess[9][13]=chess[9][10]=1;
	chess[10][9]=chess[10][14]=chess[10][11]=1;
	chess[11][10]=chess[11][15]=1;
	chess[12][8]=chess[12][13]=1;
	chess[13][9]=chess[13][12]=chess[13][14]=1;
	chess[14][10]=chess[14][13]=chess[14][15]=1;
	chess[15][11]=chess[15][14]=1;
	bfs(chess);
}
void parentheses(const std::string& str)
{
	int start=-1;
	//int t=0;
	std::stack<int> s;
	int maxLength=0;
	for(int i=0;i<str.length();++i)
	{
		if(str[i]=='(')
		{
			s.push(i);
		}
		else//')'
		{
			if(!s.empty())
			{
				//t=s.top();
				s.pop();
				if(s.empty())
				{
					maxLength=std::max(maxLength,i-start);
					//start=i;
				}
				else
				{
					maxLength=std::max(maxLength,i-s.top());
				}
			}
			else
			{
				start=i;
			}
		}
	}
	std::cout<<maxLength<<std::endl;
}
void parentheses2(const std::string& str)
{
	int start=-1;
	int deep=0;
	//std::stack<int> s;
	int maxLength=0;
	for(int i=0;i<str.length();++i)
	{
		if(str[i]=='(')
		{
			//s.push(i);
			++deep;
		}
		else//')'
		{
			--deep;
			if(deep==0)
			{
				maxLength=std::max(maxLength,i-start);
			}
			else if(deep<0)
			{
				deep=0;
				start=i;
			}
		}
	}
	std::cout<<maxLength<<std::endl;
	deep=0;
	start=str.length();
	for(int i=str.length()-1;i>=0;--i)
	{
		if(str[i]==')')
		{
			//s.push(i);
			++deep;
		}
		else//')'
		{
			--deep;
			if(deep>0)
			{
				maxLength=std::max(maxLength,start-i);
			}
			else
			{
				deep=0;
				start=i;
			}
		}
	}
	std::cout<<maxLength<<std::endl;
}
void test_parenthese()
{
	//parentheses("()(())");
	parentheses2("()(())");
}
void rotate(std::vector<char>& arr,int from,int to)
{
	while(from<to)
	{
		char c=arr[from];
		arr[from]=arr[to];
		arr[to]=c;
		++from;
		--to;
	}
}
void rotate(std::vector<char>& arr,int rotateLocate)
{
	rotateLocate%=arr.size();
	rotate(arr,0,rotateLocate-1);
	rotate(arr,rotateLocate,arr.size()-1);
	rotate(arr,0,arr.size()-1);
	std::string t(arr.begin(),arr.end());
	std::cout<<t<<std::endl;
}
void test_rotate()
{
	string str = "abcdef";
	std::vector<char> arr(str.begin(),str.end());
	rotate(arr,2);
}
void FindAnswer(std::vector<std::vector<int>>& chess, std::vector<std::string>& solution, std::string& answer, const std::string str1, const std::string str2, int i, int j)
{
	while((i != 0) && (j != 0))
	{
		if(str1[i] == str2[j])
		{
			answer.push_back(str1[i]);
			i--;
			j--;
		}
		else
		{
			if(chess[i][j-1] == chess[i-1][j])
			{
				int s = (int)answer.size();
				FindAnswer(chess, solution, answer, str1, str2, i-1, j);
				answer.resize(s);

				FindAnswer(chess, solution, answer, str1, str2, i, j-1);
				answer.resize(s);
				break;
			}
			else if(chess[i][j-1] > chess[i-1][j])
			{
				j--;
			}
			else
			{
				i--;
			}
		}
	}

	if((i == 0) || (j == 0))
	{
		solution.push_back(answer);
		reverse(solution.back().begin(), solution.back().end());
		return;
	}
}

void findAnswer(const std::string& str1,int i,const std::string& str2,int j,const std::vector<std::vector<int>>& chess,std::string& oneAnswer,std::vector<std::string>& allAnswer)
{
	while((i>0)&&(j>0))
	{
		if(str1[i-1]==str2[j-1])
		{
			
			oneAnswer.push_back(str1[i-1]);
			--i;
			--j;
		}
		else
		{
			if(chess[i-1][j]==chess[i][j-1])
			{
				std::cout<<oneAnswer<<":"<<__LINE__<<":"<<__FILE__<<std::endl;
				int s = (int)oneAnswer.size();
				findAnswer(str1,i-1,str2,j,chess,oneAnswer, allAnswer);
				//oneAnswer.clear();
				oneAnswer.resize(s);
				std::cout<<oneAnswer<<":"<<__LINE__<<":"<<__FILE__<<std::endl;
				findAnswer(str1,i,str2,j-1,chess,oneAnswer, allAnswer);
				//oneAnswer.clear();
				oneAnswer.resize(s);
				std::cout<<oneAnswer<<":"<<__LINE__<<":"<<__FILE__<<std::endl;
				break;
			}
			else if(chess[i-1][j]>chess[i][j-1])
			{
				--i;
			}
			else
			{
				--j;
			}
		}
	}
	
	if((i==0)||(j==0))
	{
		//std::cout<<i<<":"<<j<<":"<<__LINE__<<":"<<__FILE__<<std::endl;
		allAnswer.push_back(oneAnswer);
		//std::cout<<oneAnswer<<std::endl;		
		std::reverse(allAnswer.back().begin(),allAnswer.back().end());
		//oneAnswer.clear();
		return;
	}
}
int LCS(const std::string& str1,const std::string& str2)
{
	const int M=str1.length();
	const int N=str2.length();
	std::vector<std::vector<int>> ret(M+1,std::vector<int>(N+1,0));
	for(int i=1;i<=M;++i)
	{
		for(int j=1;j<=N;++j)
		{
			if(str1[i]==str2[j])
			{
				
				ret[i][j]=ret[i-1][j-1]+1;
			}
			else
			{

				ret[i][j]=std::max(ret[i-1][j],ret[i][j-1]);
			}
		}
	}
	//findAnswer(ret);
	std::string oneAnswer;
	std::vector<std::string> allAnswer;
	for(auto& x:ret)
	{
		for(auto& y:x)
		{
			std::cout<<y<<" ";
		}
		std::cout<<std::endl;
	}
	 findAnswer(str1,M,str2,N,ret,oneAnswer, allAnswer);
	//FindAnswer(ret, allAnswer, oneAnswer, str1, str2, M, N);
	for(auto& x:allAnswer)
	{
		std::cout<<x<<std::endl;
	}
	return ret[M][N];
}

void test_LCS()
{
	std::string str1="BCDABAB";
	
	std::string str2="CBACBAABA";
	
	std::cout<<LCS(str1,str2)<<std::endl;

}
void LIS(std::vector<int> arr)
{
	const int N=arr.size();
	std::vector<int> b(N,0);
	b[0]=1;
	for(int i=0;i<N;++i)
	{
		//b[i]=0;
		for(int j=0;j<i;++j)
		{
			if(arr[i]>arr[j])
			{
				b[i]=std::max(b[i],b[j]+1);
			}
		}
	}
	for(auto& i:b)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void LIS_HAVA_PRE(const std::vector<int>& arr,std::vector<int>& pathLength,std::vector<int>& pre)
{
	const int N=arr.size();
	//std::vector<int> b(N,0);
	pathLength[0]=1;
	// for(int i=0;i<N;++i)
	// {
	// 	pre[i]=i;
	// }
	for(int i=0;i<N;++i)
	{
		//b[i]=0;
		for(int j=0;j<i;++j)
		{
			if(arr[i]>arr[j])
			{
				//pathLength[i]=std::max(pathLength[i],pathLength[j]+1);
				int len=pathLength[j]+1;
				if(len>pathLength[i])
				{
					pathLength[i]=len;
					pre[i]=j;
				}
			}
		}
	}
}
void get_lis(const std::vector<int>& arr,const std::vector<int>& pathLength,const std::vector<int>& pre)
{
	int ml=0;
	int index=0;
	for(int i=0;i<pathLength.size();++i)
	{
		if(pathLength[i]>ml)
		{
			ml=pathLength[i];
			index=i;
		}
	}
	std::vector<int> seq;

	while(index>=0)
	{
		seq.push_back(arr[index]);
		index=pre[index];
	}
	std::reverse(seq.begin(),seq.end());
	for(auto& i:seq)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void test_LIS()
{
	std::vector<int> arr{1,4,6,2,8,9,7};
	// LIS(arr);
	const int N=7;
	std::vector<int> pathLength(N,0);
	std::vector<int> pre(N,-1);
	LIS_HAVA_PRE(arr,pathLength,pre);
	for(auto& i:pathLength)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	for(auto& i:pre)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	get_lis(arr,pathLength,pre);
}
void permutation(std::vector<int> arr,int size,int n)
{
	if(n==size-1)
	{
		for(auto& i:arr)
		{
			std::cout<<i;
		}
		std::cout<<std::endl;
		return;
	}
	for(int i=n;i<size;++i)
	{
		std::swap(arr[i],arr[n]);
		permutation(arr,size,n+1);
		std::swap(arr[i],arr[n]);
	}
}
void test_permutation()
{
	std::vector<int> arr{1,2,3,4};
	permutation(arr,4,0);
}
void test_out()
{
	test_permutation();
	// test_LIS();
	// test_LCS();
	// test_rotate();
	// test_parenthese();
	// test_bfs();
	// test_bigInt();
	// test_chessCount();
	// test_map();
	// test_randomSong();
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
