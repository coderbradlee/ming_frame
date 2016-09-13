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
std::vector<int> v{1,2,3,4,5};
std::vector<int> get_range()
{
    std::cout<<"get_range"<<std::endl;
    return v;
}
void test_for_range()
{
    // for(auto& x:get_range())
    //     std::cout<<x<<std::endl;
    std::vector<int> v1{0,9,8,7,6,5};
    auto && __range=(v1);
    for(auto __begin=__range.begin(),__end=__range.end();__begin!=__end;++__begin)
    {
        auto val=*__begin;
        std::cout<<val<<std::endl;
        v1.push_back(1);
        sleep(1);
    }

}
void test_lambda()
{
    // int a=0;
    // auto f=[&a](){return ++a;};
    // //a+=1;
    // std::cout<<f()<<std::endl;
    std::vector<int> v11{1,2,3,4,5};
    int even_count=0;
    for_each(v11.begin(),v11.end(),[&even_count](int val)
        {
            if(!(val%2))
                ++even_count;
        });
    std::cout<<even_count<<std::endl;
}
struct test_static
{
    const static int b=0;
    //static const double c=1.2;
    int d=0;
    char x{'?'};
};
struct A_base
{
    A_base(int){}
};
struct B_base:A_base
{
    using A_base::A_base;
};
class huge_mem
{
public:
    huge_mem(int size):sz(size>0?size:1)
    {
        c=new int[sz];
        std::cout<<"huge_mem constructor"<<std::endl;
    }
    ~huge_mem()
    {
        delete[] c;
        std::cout<<"huge_mem destructor"<<std::endl;
    }
    huge_mem(const huge_mem& hm):sz(hm.sz),c(new int(*hm.c))
    {
        std::cout<<"huge_mem copy constructor"<<std::endl;
    }
    huge_mem(huge_mem&& hm):sz(hm.sz),c(hm.c)
    {
        hm.c=nullptr;
        std::cout<<"huge_mem rvalue constructor"<<std::endl;
    }
    huge_mem& operator=(const huge_mem& hm)
    {
        if(this==&hm)
            return *this;
        sz=hm.sz;
        delete[] c;
        c=new int[sz];
        for(int i=0;i<sz;++i)
            c[i]=hm.c[i];
        std::cout<<"huge_mem operator="<<std::endl;
        return *this;
    }
public:
    int sz;
    int *c;
    
};
class moveable
{
public:
    moveable():i(new int(3)),h(1024)
    {
        std::cout<<"moveable constructor"<<std::endl;
    }
    ~moveable()
    {
        delete i;
        std::cout<<"moveable destructor"<<std::endl;
    }
    moveable(const moveable& m):i(new int(*m.i)),h(m.h)
    {
        std::cout<<"moveable copy constructor"<<std::endl;
    }
    moveable(moveable&& m):i(m.i),h(std::move(m.h))
    {
        std::cout<<"moveable rvalue constructor"<<std::endl;
        m.i=nullptr;
    }
    moveable& operator=(const moveable& m)
    {
        if(this==&m)
            return *this;
        delete i;
        i=new int(*m.i);
        h=m.h;
        std::cout<<"moveable operator="<<std::endl;
        return *this;
    }
public:
    int* i;
    huge_mem h;
};
moveable get_temp()
{
    moveable tmp=moveable();
    std::cout<<"huge_mem from "<<__func__<<" @"<<tmp.h.c<<std::endl;
    return tmp;
}
struct  non_trivial
{
    non_trivial();
    int w;
};
non_trivial::non_trivial()=default;
union test_union
{
    string s;
    int n;
    test_union()
    {
        new(&s)string;
    }
    ~test_union()
    {
        s.~string();
    }
};
using uint8=unsigned char;
struct RGBA
{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
    RGBA(uint8 R,uint8 G,uint8 B,uint8 A=0):r(R),g(G),b(B),a(A){}
};
RGBA operator ""_C(const char* col,size_t n)
{
    const char* p=col;
    const char* end=col+n;
    const char* r,*g,*b,*a;
    r=g=b=a=nullptr;
    for(;p!=end;++p)
    {
        if(*p=='r') r=p;
        else if(*p=='g') g=p;
        else if(*p=='b') b=p;
        else if(*p=='a') a=p;
    }
    if(a==nullptr)
        return RGBA(atoi(r+1),atoi(g+1),atoi(b+1));
    else
        return  RGBA(atoi(r+1),atoi(g+1),atoi(b+1),atoi(a+1));
}
void blend(RGBA&& col1,RGBA&& col2)
{

}
struct constexpr_type
{
    constexpr constexpr_type(int x):i(x){}
    int i;
};
constexpr int fibonacci(int n)
{
    return (n==1)?1:((n==2)?1:fibonacci(n-1)+fibonacci(n-2));
}
void foo()
{
    std::cout<<fibonacci(11)<<std::endl;
    //constexpr constexpr_type mt={0};
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
    // bar bbbb{1,2,3,4,5};
    // bbbb.test();
    // bar cccc={2,3,4,6,7};
    // cccc.test();
    //test_for_range();
    //test_lambda();
    // int y=0;
    // int& x=y;
    // int&& var1=std::move(x);
    // //decltype(x)&& var2=std::move(y);
    // static_assert(sizeof(int)==4,"this 64-bit machine should follow this");
    // std::cout<<x<<y<<var1<<std::endl;
    // std::cout<<sizeof(((test_static*)0)->d)<<std::endl;
    // std::cout<<sizeof(test_static::x)<<std::endl;
    //B_base b(1);
    //std::cout<<is_rvalue_reference<string&&>::value<<std::endl;
    // moveable a(get_temp());
    // std::cout<<"huge_mem from "<<__func__<<" @"<<a.h.c<<std::endl;
    //std::cout<<is_trivial<non_trivial>::value<<std::endl;
    //test_union t;
    //blend("r255,g230,b123"_C,"r255,g230,b123"_C);
    // int i;
    // decltype(i) a;
    // decltype((i)) b=a;
    // b=1;
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

