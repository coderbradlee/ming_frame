#include <boost/program_options.hpp>
#include "../log.hpp"

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/noncopyable.hpp>
#include "../procmon.hpp"
#include "test2.hpp"
//#include <unistd.h>

using namespace muduo;
using namespace muduo::net;
struct bound
{
    int high;
    int low;
    bound(int h=0,int l=0):high(h),low(l){}
};
int solution(std::vector<int>& nums)
{
    //std::cout<<__LINE__<<std::endl;
    std::sort(nums.begin(),nums.end());
    std::vector<bound> ret;
    //ret.push_back(bound(nums[0],nums[0]));
    //std::cout<<__LINE__<<std::endl;
    int max=0;
    for(const auto& num:nums)
    {
    	bool have_bound=false;
        for(auto it=ret.begin();it!=ret.end();++it)
        {
            if(num==(it->high+1))
            {
                it->high=num;
                have_bound=true;
            }
            else if(num==(it->low-1))
            {
                it->low=num;
                have_bound=true;
            }               
            if(it->high-it->low+1>max)
                max=it->high-it->low+1;
        }
        if(!have_bound)
        {
			std::cout<<__LINE__<<std::endl;
        	ret.push_back(bound(num,num));
        }
        
    }
    std::cout<<__LINE__<<std::endl;
    for(const auto& n:ret)
    {
        std::cout<<n.high<<":"<<n.low<<std::endl;
    }
    return max;
}
int solution2(std::vector<int>& nums)
{
	std::unordered_map<int,bound> table;
	int local;
	int max=0;
	for(const auto& num:nums)
	{
		if(table.count(num)) continue;
		local=num;
		int low=local;
		int high=local;
		if(table.count(local-1))
			low=table[local-1].low;
		if(table.count(local+1))
			high=table[local+1].high;
		table[low].high=table[local].high=high;
		table[high].low=table[local].low=low;
		if(high-low+1>max)
			max=high-low+1;
	}
	return max;
}
void string_reverse()
{
	//std::string temp="i have 36 books,40 pens";
    std::string temp="what the fuck r you 20 doing";
    // std::reverse(temp.begin(), temp.end());
    // std::cout<<temp<<std::endl;
	size_t begin=0,end=0;
	std::string nums="0123456789";
	while(end<temp.size()+1)
	{
        if(temp[end]!=' '&&temp[end]!=','&&end!=temp.size())
        {
            ++end;
            std::cout<<__LINE__<<":"<<begin<<":"<<end<<std::endl;
            // bool tee=(std::string::npos==nums.find(temp[begin]));
            // std::cout<<tee<<std::endl;
        }
        else if(std::string::npos!=nums.find(temp[begin]))
        {
            begin=++end;
            std::cout<<__LINE__<<":"<<begin<<":"<<end<<std::endl;
        }
        else if(std::string::npos==nums.find(temp[begin]))
        {
            std::reverse(&temp[begin], &temp[end]);
            begin=++end;
            std::cout<<__LINE__<<":"<<begin<<":"<<end<<std::endl;
        }
        //std::cout<<__LINE__<<":"<<begin<<":"<<end<<std::endl;	
	}
	std::cout<<temp<<std::endl;
}
std::string min_window(std::string paper,std::string message)
{
    std::unordered_map<char,int> table;
    for(const auto& alphabet:message)
    {
        if(table.find(alphabet)!=table.end())
            ++table[alphabet];
        else
            table[alphabet]=1;
    }
    int count=message.length();
    int paper_length=paper.length();
    int min_window_high=0,min_window_low=0,min_window_length=0;
    // for(const auto& c:table)
    // {
    //     //std::cout<<c.first<<":"<<c.second<<std::endl;
    // }
    {
        for(int i=0;i<paper_length;++i)
        {
            if(count>0)
            {
                std::cout<<__LINE__<<":"<<count<<":"<<i<<std::endl;
                if(table.find(paper[i])!=table.end()&&table[paper[i]]>0)
                {
                    --table[paper[i]];
                    --count;
                }
            }
            else
            {
                std::cout<<__LINE__<<":"<<count<<":"<<i<<std::endl;
                min_window_high=i;
                min_window_length=i;
                break;
            }
        }
        //shrink begin when found
        if(min_window_high!=0)
        {
            for(int i=0;i<min_window_high-count;++i)
            {
                if(table.find(paper[i])!=table.end())
                {
                    min_window_low=i;
                    min_window_length=min_window_high-min_window_low;
                    break;
                }
            }
        }

    }
    if(min_window_length!=0)
    {
        return paper.substr(min_window_low,min_window_length);
    }
    else
    {
        return "not found";
    }
    
} 
void foo()
{
    std::string paper="Polling stations have closed in Russia's parliamentary, regional and municipal elections. With 40 percent of votes counted, early results suggest that the ruling United Russia party heads the polls with 53 percent.\
    With almost half of the votes counted, early results suggest that the ruling United Russia party heads the polls, followed by right-wing party LDPR with 14.3 percent and the Russian Communist Party with 14.2 percent. Fair Russia comes fourth with 6.2 percent, the Russian Central Elections Committee said.";
    std::string message="what the hell";
    std::cout<<min_window(paper,message)<<std::endl;
    //std::cout<<__LINE__<<std::endl;
    // std::vector<int> nums{6,4,8,1,3,2,7};

    // //std::cout<<__LINE__<<std::endl;

    // std::cout<<solution(nums)<<std::endl;
    // std::cout<<solution2(nums)<<std::endl;
    //string_reverse();
}
int main(int argc, char* argv[])
{
    init_log();
    LOG_INFO << argv[0] << " [number of IO threads] [number of worker threads] [-n]";
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  
    test2_namespace::test_out();
    foo();
    sleep(10);
   
}

