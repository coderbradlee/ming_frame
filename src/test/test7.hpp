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
namespace beforePermutation
{
	void print(const int* a,int size)
	{
		for(int i=0;i<size;++i)
			std::cout<<a[i]<<' ';
		std::cout<<std::endl;
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
}
bool isDuplicate(const std::vector<int>& arr,int n,int t)
{
	while(n<t)
	{
		if(arr[n]==arr[t])
		{
			std::cout<<"dup"<<std::endl;
			return true;
		}
		++n;
	}
	return false;
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
void permutation2(std::vector<int>& arr,int size,int n)
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
		if(isDuplicate(arr,n,i))
			continue;
		std::swap(arr[i],arr[n]);
		permutation2(arr,size,n+1);//第二次写又一次写错了这个地方，调用了第一个版本的permutation
		std::swap(arr[i],arr[n]);
	}
}
void test_permutation()
{
	//std::vector<int> arr{1,2,3,4};
	//permutation(arr,4,0);
	std::vector<int> arr2{1,2,2,3};
	permutation2(arr2,4,0);
	//beforePermutation::test_permutation();
}
bool next_permutation(std::vector<int>& arr)
{
	int size=arr.size()-1;
	int swap_index=0;
	//find swap index
	for(int i=size;i>=0;--i)
	{
		if(i==0)
			return false;
		
		if(arr[i]>arr[i-1])
		{
			swap_index=i-1;
			//std::swap(arr[i-1],arr[min_index]);
			break;
		}
	}
	for(int i=size;i>=0;--i)
	{
		if(arr[i]>arr[swap_index])
		{
			std::swap(arr[i],arr[swap_index]);
			break;
		}
	}
	std::reverse(arr.begin()+swap_index+1,arr.end());
	return true;
}
void test_next_permutation()
{
	std::vector<int> arr{1,2,2,3};
	while(next_permutation(arr))
	{
		for(auto& i:arr)
		{
			std::cout<<i;
		}
		std::cout<<std::endl;
	}
}
void manacher(const std::vector<int>& arr,std::vector<int>& p)
{
	const int len=arr.size();
	int id=0;
	p[0]=1;
	int mx=1;
	for(int i=0;i<len;++i)
	{
		if(mx>i)
		{
			p[i]=std::min(p[2*id-i],mx-i);
		}
		while(arr[i+p[i]]==arr[i-p[i]])
		{
			++p[i];
		}
		if(i+p[i]>mx)
		{
			id=i;
			mx=i+p[i];
		}
	}
}
void test_manacher()
{
	std::vector<int> arr{-2,-1,1,-1,2,-1,2,-1,1,-1,2,-1,3,-1,2,-1,1,-1};
	const int len=arr.size();
	std::vector<int> p(len,0);
	manacher(arr,p);
	for(auto& i:p)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void get_next(const std::vector<char>& arr,std::vector<int>& next)
{
	next[1]=0;
	for(int i=2;i<arr.size();++i)
	{
		int k=next[i-1];
		while(1)
		{
			if((k==-1)||(arr[i-1]==arr[k]))
			{
				next[i]=k+1;
				break;
			}
			else
			{
				k=next[k];
			}
		}
	}
}
void get_next2(const std::vector<char>& arr,std::vector<int>& next)
{
	next[1]=0;
	int i=2;
	int k=-1;
	while(i<arr.size())
	{
		if((k==-1)||(arr[i-1]==arr[k]))
		{
			int temp=k+1;
			if(arr[i]==arr[temp])
			{
				std::cout<<arr[i]<<":"<<temp<<std::endl;
				next[i]=next[temp];
			}
			else
			{
				next[i]=temp;
			}
			++i;
			++k;
		}
		else
		{
			k=next[k];
		}
	}
	
}
void test_KMP()
{
	// std::vector<char> arr{'a','b','a','a','b','c','a','b','a'};
	std::vector<char> arr{'a','b','c','a','b','c','a','b','c','a','b','c','\0'};
	std::vector<int> next(arr.size(),-1);
	get_next(arr,next);
	// get_next2(arr,next);
	for(auto& i:next)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void count()
{
	const int N=10;
	std::vector<std::vector<int>> dp(N,std::vector<int>(2,0));
	dp[0][0]=3;
	dp[0][1]=0;
	for(int i=1;i<N;++i)
	{
		dp[i][0]=(dp[i-1][0]+dp[i-1][1])*2;
		dp[i][1]=dp[i-1][0];
	}
	for(auto& i:dp)
	{
		for(auto& j:i)
		{
			std::cout<<j<<" ";
		}
		std::cout<<std::endl;
	}
}
void count2()
{
	const int N=10;
	std::vector<int> dp(N,0);
	int notEqual=3;
	int equ=0;
	for(int i=1;i<N;++i)
	{
		int temp=notEqual;
		notEqual=(notEqual+equ)*2;
		equ=temp;
		dp[i]=notEqual+equ;
	}
	for(auto& i:dp)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
typedef struct Matrix
{
	int a;
	int b;
	int c;
	int d;
	void set(int aa,int bb,int cc,int dd)
	{
		a=aa;
		b=bb;
		c=cc;
		d=dd;
	}
}matrix;
void multiMatrix(matrix& m,const matrix& n)
{
	int a=m.a*n.a+m.c*n.b;
	int b=m.b*n.a+m.d*n.b;
	int c=m.a*n.c+m.c*n.d;
	int d=m.b*n.c+m.d*n.d;
	m.set(a,b,c,d);
}
void multiN(matrix& m,int n)
{
	if(n==0)
	{
		m.set(1,0,0,1);
		return;
	}
	if(n==1)
	{
		return;
	}
	if(n%2==0)
	{
		multiN(m,n/2);
		multiMatrix(m,m);
	}
	else
	{
		matrix x=m;
		multiN(m,n/2);
		multiMatrix(m,m);
		multiMatrix(m,x);
	}
}
void count3()
{
	const int N=10;
	// int nonRepeat=3;
	// int repeat=1;
	matrix m;
	m.set(2,2,1,0);
	multiN(m,N-1);
	std::cout<<(m.a+m.c)*3<<std::endl;
}
void test_count()
{
	count();
	count2();
	count3();
}
void eratosthenes(std::vector<bool>& v)
{
	int size=std::sqrt(v.size());

	for(int i=2;i<size;++i)
	{
		for(int j=i;j*i<size*size;++j)
		{
			v[i*j]=false;
		}
	}
	for(int i=0;i<v.size();++i)
	{
		if(v[i])
			std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void test_eratosthenes()
{
	std::vector<bool> v(100,true);
	eratosthenes(v);
}
int rotateLeftShift(int x,int N)
{
	int high=x>>(N-1);
	x&=(1<<(N-1))-1;
	x<<=1;
	x|=high;
	return x;
}
void color(int n)
{
	int size=1<<n;
	std::vector<int> v(size,1);
	for(int i=0;i<size;++i)
	{
		int k1=i;
		for(int j=0;j<n;++j)
		{
			int x=rotateLeftShift(k1,n);
			if(x==i)
			{
				break;
			}
			else if(x>i)
			{
				v[x]=0;
			}
			else
			{
				v[i]=0;
				break;
			}
			k1=x;
		}
	}
	int num=0;
	for(int i=0;i<size;++i)
	{
		if(v[i]==1)
		{
			++num;
			std::cout<<i<<" ";
		}
	}
	std::cout<<std::endl<<num<<std::endl;
}
void test_color()
{

	//for(int i)
	int x=-1;
	x=x<<1;

	std::cout<<x<<std::endl;
	color(6);
	color(7);
	color(8);
}
void moveOne(char from,char to)
{
	std::cout<<from<<"-->"<<to<<std::endl;
}
void move(char from,char to,char aux,int n)
{
	if(n==1)
	{
		moveOne(from,to);
		return;
	}
	move(from,aux,to,n-1);
	moveOne(from,to);
	move(aux,to,from,n-1);
}
int calc(const std::string& str,int size,char from,char to,char aux)
{
	if(size==0)
		return 0;
	if(str[size-1]==aux)
	{
		return -1;
	}
	if(str[size-1]==to)
	{
		int i=calc(str,size-1,aux,to,from);
		if(i==-1)
			return i;
		else
		{
			int ret=(1<<(size-1))+i;
			return ret;
		}		
	}
	return calc(str,size-1,from,aux,to);
}
void test_hanoi()
{
	//move('A','C','B',3);
	std::string str="ABC";
	int one=calc(str,3,'A','C','B');
	std::string str1="AAC";
	int two=calc(str1,3,'A','C','B');
	std::cout<<one<<":"<<two<<std::endl;
}
double pow(double x,int n)
{
	if(n==0)
		return 1;
	if(n==1)
		return x;
	if(n==2)
		return x*x;
	double temp=pow(x,n/2)*pow(x,n/2);
	double temps=temp*x;
	return (n%2==0)?temp:temps;
}
double power(double x,int n)
{
	if(n<0)
	{
		return 1/pow(x,-n);
	}
	return pow(x,n);
}
bool searchPath(const std::vector<std::vector<int>>& chess,int i,int j,std::vector<std::vector<bool>>& visit,std::vector<std::pair<int,int>>& path,std::vector<std::vector<std::pair<int,int>>>& all)
{
	if(chess[i][j]==9)
	{
		// for(auto& i:path)
		// {
		// 	std::cout<<i.first<<":"<<i.second<<std::endl;
		// }
		//all.push_back(path);
		return true;
	}
	int row[]={-1,1,0,0};
	int col[]={0,0,-1,1};
	for(int k=0;k<4;++k)
	{
		//visit[i][j]=true;
		int icur=i+row[k];
		int jcur=j+col[k];
		if((icur<0)||(icur>=chess.size())||(jcur<0)||(jcur>=chess[0].size()))
			continue;
		if((!visit[icur][jcur])&&(chess[icur][jcur]!=0))
		{
			path.push_back(std::make_pair(icur,jcur));
			visit[icur][jcur]=true;
			if(searchPath(chess,icur,jcur,visit,path,all))
			{
				// return true;
				all.push_back(path);
			}
			path.pop_back();
			visit[icur][jcur]=false;
		}
	}
	return false;
}
void mousePath(const std::vector<std::vector<int>>& chess)
{
	std::vector<std::pair<int,int>> path;
	std::vector<std::vector<std::pair<int,int>>> all;
	std::vector<std::vector<bool>> visit(chess.size(),std::vector<bool>(chess[0].size(),false));
	path.push_back(std::make_pair(0,0));
	visit[0][0]=true;
	searchPath(chess,0,0,visit,path,all);
	for(auto& a:all)
	{	
		for(auto& i:a)
		{
			std::cout<<i.first<<":"<<i.second<<" ";
		}
		std::cout<<std::endl;
	}
}
void test_mouse()
{
	std::vector<std::vector<int>> chess=
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
	mousePath(chess);
}
int mode(const std::vector<int>& arr)
{
	int count=0;
	int ret;
	for(int i=0;i<arr.size();++i)
	{
		if(count==0)
		{
			ret=arr[i];
			++count;
		}
		else if(arr[i]==ret)
		{
			++count;
		}
		else
		{
			--count;
		}
	}
	std::cout<<count<<std::endl;
	return ret;
}
void test_mode()//众数
{
	std::vector<int> arr{8,8,1,1,1,8,1,1,6,1,8};
	int m=mode(arr);
	std::cout<<m<<std::endl;
}
void localMax(const std::vector<int>& arr)
{
	int high=arr.size()-1;
	int low=0;
	int mid=(low+high)/2;
	while(low<high)
	{
		if(arr[mid]>arr[mid+1])
		{
			high=mid;
		}
		else
		{
			low=mid+1;
		}
		mid=(low+high)/2;
	}
	std::cout<<"arr["<<mid<<"]="<<arr[mid]<<std::endl;
}
void test_localMax()
{
	std::vector<int> arr{8,8,1,11,3,8,4,5,6,2,8};
	localMax(arr);
}
int firstMissingNumber(std::vector<int> arr)
{
	int N=arr.size();
	int size=N-1;
	int i=0;
	while(i<=size)
	{
		if(arr[i]==(i+1))
		{
			++i;
		}
		else if(arr[i]<(i+1)||arr[i]>(N+1)||arr[arr[i]-1]==arr[i])
		{
			std::swap(arr[i],arr[size]);
			--size;
		}
		else if(arr[i]>(i+1))
		{
			std::swap(arr[arr[i]-1],arr[i]);
		}
	}
	return i+1;
}
void test_firstMissingNumber()
{
	std::vector<int> arr{3,5,1,2,-3,7,6,8};
	std::cout<<firstMissingNumber(arr)<<std::endl;
}
void rotateArrayMin(std::vector<int> arr)
{
	int size=arr.size();
	int low=0;
	int high=size-1;
	int mid;//=(low+high)/2;
	while(low<=high)
	{
		mid=(low+high)/2;
		std::cout<<low<<":"<<mid<<":"<<high<<std::endl;
		if(arr[mid]>arr[high])
		{
			low=mid+1;
		}
		else if(mid==high)
		{
			break;
		}
		else
		{
			high=mid;
		}
	}
	
	std::cout<<arr[mid]<<std::endl;
}
void test_rotateArrayMin()
{
	std::vector<int> arr{5,6,7,2,3,4};
	rotateArrayMin(arr);
}
void zeroSubarray(std::vector<int> arr)
{
	std::vector<int> sum(arr.size(),0);
	sum[0]=arr[0];
	for(int i=0;i<arr.size()-1;++i)
	{
		sum[i+1]=sum[i]+arr[i+1];
	}
	std::sort(sum.begin(),sum.end());
	int ml=0;
	for(int i=1;i<sum.size();++i)
	{
		if(sum[i]-sum[i-1]<ml)
			ml=sum[i]-sum[i-1];
	}
	std::cout<<ml<<std::endl;
}
void zeroSubarray2(std::vector<int> arr)
{
	std::vector<std::pair<int,int>> sum(arr.size(),std::pair<int,int>(0,0));
	sum[0]=std::make_pair(arr[0],0);
	for(int i=0;i<arr.size()-1;++i)
	{
		//sum[i+1]=sum[i]+arr[i+1];
		sum[i+1]=std::make_pair(sum[i].first+arr[i+1],i+1);

	}
	std::sort(sum.begin(),sum.end(),
		[](std::pair<int,int> a,std::pair<int,int> b)
		{
			return a.first<b.first;
		});
	// for(auto i:sum)
	// {
	// 	std::cout<<i.first<<":"<<i.second<<std::endl;
	// }
	int ml=100;
	int from=0;
	int to=0;
	for(int i=1;i<sum.size();++i)
	{
		if(sum[i].first-sum[i-1].first<ml)
		{	
			ml=sum[i].first-sum[i-1].first;
			from=sum[i-1].second;
			to=sum[i].second;
			std::cout<<ml<<":"<<from<<":"<<to<<std::endl;
		}
	}
	std::cout<<ml<<":"<<from<<":"<<to<<std::endl;
}
void test_zeroSubarray()
{
	std::vector<int> arr{1,-2,3,10,-4,7,2,-5};
	//zeroSubarray(arr);
	zeroSubarray2(arr);
}
void maxSubarray(std::vector<int> arr)
{
	int size=arr.size();
	std::vector<int> sum(size,0);
	sum[0]=arr[0];
	for(int i=1;i<size;++i)
	{
		sum[i]=std::max(sum[i-1]+arr[i],arr[i]);
	}
	for(auto& i:sum)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void maxSubarray2(std::vector<int> arr)
{
	int size=arr.size();
	std::vector<int> sum(size,0);
	sum[0]=arr[0];
	int from=0;
	int to=0;
	int ml=sum[0];

	for(int i=1;i<size;++i)
	{
		bool updateTo=false;
		bool updateFrom=false;
		int temp=sum[i-1]+arr[i];
		if(temp>arr[i])
		{
			sum[i]=temp;
			//to=i;
			updateTo=true;
		}
		else
		{
			sum[i]=arr[i];
			//from=i;
			updateFrom=true;
		}
		if(ml<sum[i])
		{
			ml=sum[i];
			if(updateTo)
			{
				to=i;
			}
			else
			{
				from=i;
			}
		}
	}
	for(auto& i:sum)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	std::cout<<ml<<":"<<from<<":"<<to<<std::endl;
}
void test_maxSubarray()
{
	std::vector<int> arr{1,-2,3,10,-4,7,2,-5};
	maxSubarray(arr);
	maxSubarray2(arr);
}
void continueSubarray(std::vector<int> arr)
{
	int size=arr.size();
	std::vector<int> len(size,1);
	int ml=1;
	int index=0;
	for(int i=1;i<size;++i)
	{
		if(arr[i]-arr[i-1]==1)
		{
			len[i]=len[i-1]+1;
			if(len[i]>ml)
			{
				ml=len[i];
				index=i;
			}
		}
	}
	std::cout<<ml<<":"<<index<<std::endl;
}
void test_continueSubarray()
{
	std::vector<int> arr{1,2,3,34,56,57,58,59,60,61,99,121};
	continueSubarray(arr);
}
void holland(std::vector<int>& arr)
{
	int begin=0;
	int cur=0;
	int end=arr.size()-1;
	while(cur<end)
	{
		if(arr[cur]==2)
		{
			std::swap(arr[cur],arr[end]);
			--end;
		}
		else
		{
			if(arr[cur]==0)
			{
				std::swap(arr[begin],arr[cur]);
				++begin;
			}
			++cur;
		}
	}
	for(auto& i:arr)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void test_holland()
{
	std::vector<int> arr{1,2,2,1,2,1,2,1,0,2,1,0};
	holland(arr);
}
typedef struct Bucket
{
	int maxValue;
	int minValue;
	bool valid;
	Bucket():valid(false){}
	void add(int n)
	{
		if(!valid)
		{
			maxValue=minValue=n;
			valid=true;
		}
		else
		{
			if(maxValue<n)
			{
				maxValue=n;
			}
			else if(minValue>n)
			{
				minValue=n;
			}
		}
	}
}bucket;
void maxGap(std::vector<int> arr)
{
	int maxValue=arr[0];
	int minValue=arr[0];
	std::vector<bucket> v(arr.size(),bucket());
	for(int i=0;i<arr.size();++i)
	{
		maxValue=std::max(maxValue,arr[i]);
		minValue=std::min(minValue,arr[i]);
	}
	int delta=maxValue-minValue;
	for(int i=0;i<arr.size();++i)
	{
		int loc=(arr[i]-minValue)*arr.size()/delta;
		if(loc>=arr.size())
		{
			loc=arr.size()-1;
		}
		v[loc].add(arr[i]);
	}
	{
		for(auto& i:v)
		{
			if(i.valid)
			{
				std::cout<<i.minValue<<":"<<i.maxValue<<std::endl;
			}
		}
	}
	int ret=0;
	int firstBuckt=0;
	for(int i=1;i<v.size();++i)
	{
		if(v[i].valid)
		{
			ret=std::max(ret,v[i].minValue-v[firstBuckt].maxValue);
			firstBuckt=i;
		}
	}
	std::cout<<ret<<std::endl;
}
void test_maxGap()
{
	std::vector<int> arr{1,7,14,9,4,13,28,23,20,40,30,22};
	maxGap(arr);
}
void cantorR(std::vector<int> can)
{
	int size=can.size();
	std::vector<int> ret(size,0);
	std::vector<int> aux(size,0);
	for(int i=0;i<size;++i)
	{
		aux[i]=i+1;
	}
	for(int i=0;i<size;++i)
	{
		ret[i]=aux[can[i]];
		aux.erase(aux.begin()+can[i]);
	}
	for(auto& i:ret)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void cantorR2(std::vector<int> can)
{
	int size=can.size();
	std::vector<int> ret(size,0);
	int j=1;
	while(j<size+1)
	{
		for(int i=0;i<size;++i)
		{
			if(can[i]!=-1)//提取过一次设置为-1
			{
				if(can[i]!=0)
				{
					--can[i];
				}
				else
				{
					ret[i]=j;
					can[i]=-1;
					++j;
					break;
				}
			}
		}
	}
	for(auto& i:ret)
	{
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;
}
void test_cantor()
{
	std::vector<int> can{3,4,1,2,1,0};
	cantorR(can);
	cantorR2(can);
}
typedef struct Node
{
	int data;
	int parent;
	int left;
	int right;
	Node():data(-1),parent(-1),left(-1),right(-1){}
}node;
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
void select2min(node* huffmanNode,int N,int& one,int& two)
{
	//make two is bigger one of one and two
	one=-1;
	two=-1;
	int min1=-1;
	int min2=min1;
	for(int i=0;i<N;++i)
	{
		if((huffmanNode[i].parent)==-1)
		{
			if((one<0)||(huffmanNode[i].data<min1))
			{
				min2=min1;
				two=one;
				min1=huffmanNode[i].data;
				one=i;
			}
			else if((two<0)||(huffmanNode[i].data<min2))
			{
				min2=huffmanNode[i].data;
				two=i;
			}
			//printf("/////////////%d:%d\n",one,two);
		}
	}
}
void huffman_code(int* frequence,int N,std::vector<std::vector<char>>& huffman)
{
	int size=2*N-1;
	node* huffmanNode=new node[size];
	for(int i=0;i<N;++i)
	{
		huffmanNode[i].data=frequence[i];
	}
	int one,two;
	for(int i=N;i<size;++i)
	{
		//choose two minner between 0-i 
		select2min(huffmanNode,i,one,two);
		//printf("/////////////%d\n",i);
		huffmanNode[i].data=huffmanNode[one].data+huffmanNode[two].data;
		huffmanNode[i].left=one;
		huffmanNode[i].right=two;
		huffmanNode[one].parent=i;
		huffmanNode[two].parent=i;
	}
	for(int i=0;i<N;++i)//前N个为叶子节点，需要求编码
	{
		std::vector<char> code;
		int cur=i;
		while(huffmanNode[cur].parent!=-1)
		{
			if(cur==(huffmanNode[huffmanNode[cur].parent].left))
			{
				code.push_back('0');
			}
			else
			{
				code.push_back('1');
			}
			if(cur!=huffmanNode[cur].parent)
				cur=huffmanNode[cur].parent;
			else
			{
				break;
			}
		}
		std::reverse(code.begin(),code.end());
		huffman[i]=code;
	}
}
void print_huffman(std::vector<int> exist_key,std::vector<std::vector<char>>& huffman)
{
	for(int i=0;i<exist_key.size();++i)
	{
		printf("%c:", exist_key[i]);
		for(auto j:huffman[i])
		{
			printf("%c",j);
		}
		printf("\n");
	}
}
void test_huffman()
{
	const int N=256;
	const char str[]="when I was young I'd listen to the radio\
					waiting for my favorite songs\
					when they played I'd sing along, \
					it make me smile.\
					those were such happy times and not so long ago\
					how I wondered where they'd gone.\
					but they're back again just like a long lost friend\
					all the songs I love so well.\
					every shalala every wo'wo\
					still shines.\
					every shing-a-ling-a-ling\
					that they're starting\
					to sing so fine";

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
	printf("\n------------------\n");
	std::vector<std::vector<char>> v(exist_key.size());
	huffman_code(frequence,exist_key.size(),v);
	
	print_huffman(exist_key,v);
}
void test_out()
{
	test_huffman();
	// test_cantor();
	// test_maxGap();
	// test_holland();
	// test_continueSubarray();
	// test_maxSubarray();
	// test_zeroSubarray();
	// test_rotateArrayMin();
	// test_firstMissingNumber();
	// test_localMax();
	std::vector<int> v;
	v[2]=0;
	//test_localMax();
	// test_mode();
	// test_mouse();
	// std::cout<<power(1.01,365)<<std::endl;
	// test_hanoi();
	// test_color();
	// test_eratosthenes();
	// test_count();
	// test_KMP();
	// test_manacher();
	// test_next_permutation();
	// std::cout<<"--------------------"<<std::endl;
	// std::cout<<sizeof(int)<<std::endl;
	// std::cout<<sizeof(long)<<std::endl;
	// std::cout<<sizeof(long long)<<std::endl;
	
	// std::cout<<sizeof(float)<<std::endl;
	// std::cout<<sizeof(double)<<std::endl;
	// std::cout<<sizeof(long double)<<std::endl;
	// std::cout<<sizeof(std::string)<<std::endl;
	// std::cout<<sizeof(size_t)<<std::endl;
	// test_permutation();
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
