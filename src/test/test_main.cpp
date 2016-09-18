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
void foo()
{
    //std::cout<<__LINE__<<std::endl;
    std::vector<int> nums{6,4,8,1,3,2,7};

    //std::cout<<__LINE__<<std::endl;

    std::cout<<solution(nums)<<std::endl;
    std::cout<<solution2(nums)<<std::endl;
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

