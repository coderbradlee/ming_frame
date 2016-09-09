/************************************************
 * coroutine sample8
************************************************
 * coroutine作为并发编程库使用。
************************************************/
#include <chrono>
#include <iostream>
#include <boost/thread.hpp>
#include "coroutine.h"
#include "win_exit.h"
 #include <ext/vstring.h>
using namespace std;
using namespace std::chrono;

// 大计算量的函数
int c = 0;

const char* convert(char buf[],int value)
{
    static char digits[19]={'9','8','7','6','5','4','3','2','1','0','1','2','3','4','5','6','7','8','9',};
    static const char* zero=digits+9;//alway point to 0
    //works for -2147483648 2147483647
    int i=value;
    char*p=buf;
    do
    {
        int lsd=i%10;
        i/=10;
        *p++=zero[lsd];
    } while (i!=0);
    if(value<0)
    {
        *p++='-';
    } 
    *p='\0';
    std::reverse(buf,p);
    return p;

}
void test_next_permutation()
{
    std::vector<int> v{1,2,3};
    int i=0;
    do
    {
        std::cout<<++i<<":";
        std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout,","));
        std::cout<<std::endl;
    }while(next_permutation(v.begin(),v.end()));
}
void choice()
{
    std::vector<int> v{1,2,3,4,5,6,7};
    std::vector<int> c_choice{1,1,1,0,0,0,0};
    int i=0;
    do
    {
        std::cout<<++i<<":";
        for(size_t j=0;j<v.size();++j)
        {
            if(c_choice[j]!=0)
            std::cout<<v[j]<<",";
        }
        std::cout<<std::endl;
    }while(prev_permutation(c_choice.begin(),c_choice.end()));
}
class both_space
{
public:
    bool operator()(char x,char y)const
    {
        return x==' '&&y==' ';
    }
};
void test_unique()
{
    std::string x{"test  test1      test2"};
    x.erase(std::unique(x.begin(),x.end(),both_space()),x.end());
    std::cout<<x<<endl;
}
struct is_odd
{
    bool operator ()(int x)
    {
        return x%2!=0;
    }
};
void test_odd()
{
    std::vector<int> v{-1,-2,-3,4,5,6};
    std::stable_partition(v.begin(),v.end(),is_odd());
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout,","));
    std::cout<<std::endl;
}
struct IPrange
{
    uint32_t start;
    uint32_t end;
    int value;
    bool operator<(const IPrange& r)const
    {
        return start<r.start;
    }
};
int find_ip_value(const std::vector<IPrange>& ranges,uint32_t ip)
{
    int ret=-1;
    if(!ranges.empty())
    {
        IPrange needle={ip,0,0};
        auto it=std::lower_bound(ranges.begin(),ranges.end(),needle);
        if(it->start>ip&&it!=ranges.begin())
            --it;
        if(it==ranges.end())
            --it;
        if(ip>=it->start&&ip<=it->end)
            ret=it->value;

    }
    return ret;
}
void test_ip_range()
{
    std::vector<IPrange> v{{300,500,1},{600,750,2}};
    std::cout<<find_ip_value(v,299)<<std::endl;
    std::cout<<find_ip_value(v,300)<<std::endl;
    std::cout<<find_ip_value(v,301)<<std::endl;
    std::cout<<find_ip_value(v,499)<<std::endl;
    std::cout<<find_ip_value(v,500)<<std::endl;
    std::cout<<find_ip_value(v,599)<<std::endl;
    std::cout<<find_ip_value(v,600)<<std::endl;
}
class bar
{
public:
    bar(std::initializer_list<int> x)
    {
        for(auto& m:x)
        std::cout<<m<<std::endl;
    }
    void test(){}
};
void foo()
{
    // int v = 1;
    // for (int i = 1; i < 20000000; ++i)
    //     v *= i;
    // c += v;
    // char buf[9]={0};
    // for (int i = 1; i < 20000000; ++i)
    //     convert(buf,i);
    //test_next_permutation();
    //choice();
    //test_unique();
    //test_odd();
    //test_ip_range();
    bar bbbb{1,2,3,4,5};
    bbbb.test();
    bar cccc={2,3,4,6,7};
    cccc.test();
}
int main()
{
    // 普通的for循环做法
    auto start = system_clock::now();
    // for (int i = 0; i < 100; ++i)
    //     foo();
    auto end = system_clock::now();
    // cout << "for-loop, cost ";
    // cout << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

    // 使用libgo做并行计算
    start = system_clock::now();
    for (int i = 0; i < 1; ++i)
        go foo;

    // 创建8个线程去并行执行所有协程
    boost::thread_group tg;
    for (int i = 0; i < 8; ++i)
        tg.create_thread([] {
                co_sched.RunUntilNoTask();
                });
    tg.join_all();

    end = system_clock::now();
    cout << "go with coroutine, cost ";
    cout << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
	cout << "result zero:" << c * 0 << endl;
    std::cout<<sizeof(string)<<std::endl;
    std::cout<<sizeof(__gnu_cxx::__sso_string)<<std::endl;
    return 0;
}

