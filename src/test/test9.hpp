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
namespace test9_namespace
{

int calcpath(const std::vector<std::vector<int>>& graph)
{
	const int N=graph.size();
	std::vector<int> step(N,0);//从0到i的步数
	std::vector<int> path(N,0);//从0到i的路径数
	path[0]=1;
	int i=0;
	int j=1;
	while(j<N)
	{
		if(graph[i][j]==1)
		{
			if(step[j]==0)
			{
				step[j]=step[i]+1;
				path[j]=path[i];
			}
			else if(step[j]==(step[i]+1))
			{
				path[j]+=path[i];
			}
			++i;
			++j;
		}
		else
		{
			++j;
		}
	}
	return path[N-1];
}
void test_sp()
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
void test_out()
{
	test_sp();
	
}
}
