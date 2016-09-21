#include "test2.hpp"
namespace test2_namespace
{
	using muduo::string;
	namespace test_inline
	{
		class printer::impl
		{

		};
		printer::printer():m_impl(new impl)
		{

		}
		// printer::~printer()
		// {

		// }
		
		void test()
		{

		}
	}
	namespace test_multithreadloop_multiconnect
	{
		typedef boost::shared_ptr<muduo::net::Connector> ConnectorPtr;
		muduo::net::EventLoop* g_loop;

		void connectCallback(int sockfd)
		{
		  printf("connected.\n");
		  g_loop->quit();
		}
		void test()
		{
			muduo::net::EventLoop loop;
		  g_loop = &loop;
		  muduo::net::InetAddress addr("115.239.211.112", 80);
		  ConnectorPtr connector;
		  for(int i=0;i<10000;++i)
		  {
		  	connector=ConnectorPtr(new muduo::net::Connector(&loop, addr));
		    connector->setNewConnectionCallback(connectCallback);
		    connector->start();
		  }
		  loop.loop();
		}
	}
	namespace test_weak_call_back
	{
	
		stock::stock(const string& name):m_name(name)
		{
			std::cout<<"constructor:"<<this<<":"<<m_name<<std::endl;
		}
		stock::~stock()
		{
			std::cout<<"destructor:"<<this<<":"<<m_name<<std::endl;
		}
		const string& stock::key()const
		{
			return m_name;
		}
		
		boost::shared_ptr<stock> stock_factory::get(const string& key)
		{
			boost::shared_ptr<stock> p;
			muduo::MutexLockGuard lock(m_mutex);
			boost::weak_ptr<stock>& w=m_stocks[key];
			p=w.lock();
			if(!p)
			{
				p.reset(new stock(key),boost::bind(&stock_factory::weak_call_back,boost::weak_ptr<stock_factory>(shared_from_this()),_1));
				w=p;
			}
			return p;
		}
	
		void stock_factory::weak_call_back(const boost::weak_ptr<stock_factory>& w,stock* s)
		{
			boost::shared_ptr<stock_factory> f(w.lock());
			if(f)
			{
				f->remove_stock(s);
			}
			delete s;
		}
		void stock_factory::remove_stock(stock* s)
		{
			if(s)
			{
				muduo::MutexLockGuard lock(m_mutex);
				m_stocks.erase(s->key());
			}
		}
	
		void test()
		{
			{
				boost::shared_ptr<stock_factory> f(new stock_factory());
				{
					boost::shared_ptr<stock> s1=f->get("ibm");

					boost::shared_ptr<stock> s2=f->get("ibm");
				}
			}
			{
				boost::shared_ptr<stock> s;
				{
					boost::shared_ptr<stock_factory> f(new stock_factory());
					s=f->get("ibm");
					boost::shared_ptr<stock> s2=f->get("ibm");
				}
			}
		}
	}
	namespace thread_safe_observable
	{
		
		void observable::register_(boost::weak_ptr<observer> x)
		{
			m_observers.push_back(x);
		}
		void observable::notify()
		{
			muduo::MutexLockGuard lock(m_mutex);
			m_observers.erase(std::remove_if(m_observers.begin(),m_observers.end(),[](boost::weak_ptr<observer> x)
			{
				boost::shared_ptr<observer> obj(x.lock());
				if(obj)
				{
					obj->update();
					return false;
				}
				return true;
			}),m_observers.end());
		}
		
		observable::~observable()
		{
			std::cout<<"~observable"<<std::endl;
		}
		observer::~observer()
		{
			std::cout<<"~observer"<<std::endl;
		}
		void observer::update()
		{
			std::cout<<"update"<<std::endl;
		}
		void observer::observe(observable* s)
		{
			s->register_(shared_from_this());
			m_observable=s;
		}
		void test()
		{
			observable able;
			{
				boost::shared_ptr<observer> p(new observer());
				p->observe(&able);
				able.notify();
			}
			able.notify();
		}
	}
	namespace test_mutex
	{

		void request::process()
		{
			muduo::MutexLockGuard lock(m_mutex);
			std::cout<<"print before"<<std::endl;
			print();
			std::cout<<"print after"<<std::endl;
		}
		void request::print()
		{
			muduo::MutexLockGuard lock(m_mutex);
			std::cout<<"print"<<std::endl;
		}
	
		void test()
		{
			request r;
			r.process();
		}
	}
	namespace test_mutex_between_threads
	{
	
		void inventory::add(boost::shared_ptr<request> r)
		{
			muduo::MutexLockGuard lock(m_mutex);
			if(!m_requests.unique())
			{
				m_requests.reset(new std::set<boost::shared_ptr<request>>(*m_requests));
				std::cout<<__LINE__<<":add"<<std::endl;
			}
			std::cout<<__LINE__<<":"<<m_requests.unique()<<std::endl;
			m_requests->insert(r);
		}
		void inventory::remove(boost::shared_ptr<request> r)
		{
			muduo::MutexLockGuard lock(m_mutex);
			if(!m_requests.unique())
			{
				m_requests.reset(new std::set<boost::shared_ptr<request>>(*m_requests));
				std::cout<<__LINE__<<":erase"<<std::endl;
			}
			std::cout<<__LINE__<<":"<<m_requests.unique()<<std::endl;
			m_requests->erase(r);
		}
		void inventory::print_all()const
		{
			boost::shared_ptr<std::set<boost::shared_ptr<request>>> new_one;
			{
				muduo::MutexLockGuard lock(m_mutex);
				new_one=m_requests;
			}
			
			//for(auto& i:*new_one)
			for(auto it=new_one->begin();it!=new_one->end();++it)
			{
				(*it)->print();
			}
			std::cout<<"print all"<<std::endl;
		}
 		inventory g_inventorys;
		void request::process()
		{
			muduo::MutexLockGuard lock(m_mutex);
			g_inventorys.add(shared_from_this());
		}
		void request::cancel()
		{
			muduo::MutexLockGuard lock(m_mutex);
			std::cout<<"request cancel"<<std::endl;
			g_inventorys.remove(shared_from_this());
		}
		request::~request()
		{
			//muduo::MutexLockGuard lock(m_mutex);
			//sleep(1);
			//g_inventorys.remove(this);
			std::cout<<"~request"<<std::endl;
		}
		void request::print()
		{
			muduo::MutexLockGuard lock(m_mutex);
			std::cout<<"request print"<<std::endl;
		}
		void thread_func()
		{
			boost::shared_ptr<request> r(new request());
			r->process();
			r->cancel();
			//delete r;
		}

		void test()
		{
			muduo::Thread t(thread_func);
			t.start();
			usleep(500*1000);
			//sleep(5);
			g_inventorys.print_all();
			t.join();
		}
	}
	struct how_many_bytes
	{
		char a;
		int b;
	};
	struct alignas(32) color_vector
	{
		double a;
		double b;
		double c;
		double d;
	};
	[[ noreturn ]] void test_no_return(int i)
	//void test_no_return(int i) __attribute__ ((noreturn))
	//__attribute__((noreturn)) void test_no_return(int i)
	{
		if(i<0)
			throw "negative";
		else if(i>0)
			throw "positive";
	}
	struct Person 
	{
	  Person(std::string name):m_name(name) {}
	  
	  std::string greet(std::string other_name) 
	  {
	    return "Hi " + other_name + ", my name is " + m_name;
	  }
	  
	  std::string m_name;
	};

	struct link_list
	{
		int val;
		link_list* next;
		link_list(int x):val(x),next(nullptr){}
	};
	link_list* less_list(link_list* head,int ref)
	{
		link_list *dummy=new link_list(0);
		link_list *great_head=new link_list(0);

		link_list *p=great_head;
		link_list *p_dummy=dummy;
		dummy->next=head;
		great_head->next=head;
		
		while(p->next->next!=nullptr)
		{
			if(p->next->val>ref)
			{
				p=p->next;
				std::cout<<__LINE__<<":"<<p->next->val<<std::endl;
			}	
			else
			{
				p_dummy->next=p->next;
				p->next=p->next->next;
				p_dummy->next->next=nullptr;
				//p=p->next;
				p_dummy=p_dummy->next;
				std::cout<<__LINE__<<":"<<p->next->val<<std::endl;
				std::cout<<__LINE__<<":"<<p_dummy->val<<std::endl;
			}	
		}
		p_dummy->next=great_head->next;
		std::cout<<__LINE__<<":"<<p_dummy->next->val<<std::endl;
		std::cout<<__LINE__<<":"<<dummy->next->val<<std::endl;
		return dummy->next;
	}
	void print_list(link_list* head)
	{
		link_list* p=head;
		while(p!=nullptr)
		{
			std::cout<<p->val<<std::endl;
			p=p->next;
		}
		
	}
	void test_out()
	{ 
		link_list l1(8);
		link_list l2(9);
		link_list l3(3);
		link_list l4(5);
		link_list l5(10);
		l1.next=&l2;
		l2.next=&l3;
		l3.next=&l4;
		l4.next=&l5;
		print_list(&l1);
		link_list* p=less_list(&l1,8);
		print_list(p);
		// Person p("joe");
		// p.greet("kate");
		// char u8string[]=u8R"(你好)"" = hello";
		// std::cout<<u8string<<std::endl;
		// std::cout<<sizeof(u8string)<<std::endl;
		//std::cout<<R"(hello,\n world)"<<std::endl;
		// char utf8[]=u8"\u4F60\u597D\u554A";
		// char16_t utf16[]=u"hello";
		// char32_t utf32[]=U"hello equals \u4F60\u597D\u554A";
		// std::cout<<utf8<<std::endl;
		// std::cout<<utf16<<std::endl;
		// std::cout<<utf32<<std::endl;
		// test_no_return(0);
		// std::cout<<"return"<<std::endl;
		//alignas(float) extern unsigned char c[sizeof(double)];
		//std::cout<<alignof(std::max_align_t)<<std::endl;
		// char d[1024];
		// std::cout<<alignof(d)<<std::endl;
		//std::cout<<alignof(color_vector)<<std::endl;
		// std::cout<<sizeof(char)<<std::endl;
		// std::cout<<sizeof(int)<<std::endl;
		// std::cout<<sizeof(how_many_bytes)<<std::endl;
		// std::cout<<offsetof(how_many_bytes,a)<<std::endl;
		// std::cout<<offsetof(how_many_bytes,b)<<std::endl;
		//thread_safe_observable::test();
		//test_weak_call_back::test();
		//test_mutex::test();
		//test_mutex_between_threads::test();
		//test_multithreadloop_multiconnect::test();
	}
	
}