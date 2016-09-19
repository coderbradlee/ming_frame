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
bool one_loop_for_min_window(std::string paper,std::unordered_map<char,int> table,int count,int& low,int& lengths)
{
    int min_window_length=0,min_window_low=0;
    int paper_length=paper.length();
    bool found=false;
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
            //min_window_high=i;
            min_window_length=i;
            found=true;
            break;
        }
    }
    //shrink begin when found
    
    if(found)
    {
        // for(int i=0;i<min_window_high-count;++i)
        // {
        //     if(table.find(paper[i])!=table.end())
        //     {
        //         min_window_low=i;
        //         min_window_length=min_window_high-min_window_low;
        //         break;
        //     }
        // }
        std::string shrink_string=paper.substr(0,min_window_length);
        for(;;)
        {
            if(table.find(shrink_string[0])==table.end())
            {
                shrink_string=shrink_string.substr(1,min_window_length-1);
                ++min_window_low;
                --min_window_length;
            }
            else if(std::count(shrink_string.begin(), shrink_string.end(), shrink_string[0])>1)
            {
                shrink_string=shrink_string.substr(1,min_window_length-1);
                ++min_window_low;
                --min_window_length;
            }
            else
            {
                break;
            }
        }
    }
    lengths=min_window_length;
    low=min_window_low;
    return found;
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
    
    int min_window_low=0,min_window_length=0;
    // for(const auto& c:table)
    // {
    //     //std::cout<<c.first<<":"<<c.second<<std::endl;
    // }
    min_window_length=paper.length();
    bool found=false;
    int i=0;
    //for(int i=0;i<min_window_length-count;++i)
    {
        int temp_min_window_length=0,temp_min_window_low;
        found=one_loop_for_min_window(paper.substr(i,min_window_length),table,count,temp_min_window_low,temp_min_window_length);
        if(found)
        {
            if(min_window_length>temp_min_window_length)
            {
                min_window_low=temp_min_window_low;
                min_window_length=temp_min_window_length;
            }
        }
    }
    
    
    ////////////////////////////////////
    if(!found)
    {
        return "not found";
    }
    return paper.substr(min_window_low,min_window_length);
} 
class test_pod
{
public:
    //test_pod()=default;
    test_pod(){}
    test_pod(int i):data(i){}
private:
    int data;
};
class conv_type
{
public:
    conv_type(int i)
    {
        std::cout<<"int i"<<std::endl;
    }
    explicit conv_type(char c)=delete;
};
void func(conv_type ct)
{

}
void foo()
{
    int j=12;
    auto by_value_lambda=[=]{return j+1;};
    auto by_ref_lambda=[&]{return j+1;};
    std::cout<<by_value_lambda()<<std::endl;
    std::cout<<by_ref_lambda()<<std::endl;
    ++j;
    std::cout<<by_value_lambda()<<std::endl;
    std::cout<<by_ref_lambda()<<std::endl;
    // func(3);
    // func('a');
    // conv_type ci(3);
    //conv_type cc('a');
    //std::cout<<std::is_pod<test_pod>::value<<std::endl;
    // nullptr_t my_null;
    // printf("%x\n",&my_null);
    // const nullptr_t&& def=nullptr;
    // printf("%x\n",&def );

    //std::cout<<sizeof(void*)<<":"<<sizeof(nullptr_t)<<std::endl;
    // if(nullptr)
    // {
    //     std::cout<<__LINE__<<std::endl;
    // }
    // std::string paper=" what the fuck r u doing,tee he waa";
    // std::string message="what ";
    // std::cout<<min_window(paper,message)<<std::endl;
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

