#include "test2.hpp"
namespace test2_namespace
{
	using muduo::string;
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
	
		void inventory::add(request* r)
		{
			muduo::MutexLockGuard lock(m_mutex);
			m_requests.insert(r);
		}
		void inventory::remove(request* r)
		{
			muduo::MutexLockGuard lock(m_mutex);
			m_requests.erase(r);
		}
		void inventory::print_all()const
		{
			muduo::MutexLockGuard lock(m_mutex);
			sleep(1);
			for(auto& i:m_requests)
			{
				i->print();
			}
			std::cout<<"print all"<<std::endl;
		}
 		inventory g_inventorys;
		void request::process()
		{
			muduo::MutexLockGuard lock(m_mutex);
			g_inventorys.add(this);
		}
		request::~request()
		{
			muduo::MutexLockGuard lock(m_mutex);
			sleep(1);
			g_inventorys.remove(this);
		}
		void request::print()
		{
			muduo::MutexLockGuard lock(m_mutex);
			std::cout<<"print"<<std::endl;
		}
		void thread_func()
		{
			request* r=new request();
			r->process();
			delete r;
		}

		void test()
		{
			muduo::Thread t(thread_func);
			t.start();
			//usleep(500*1000);
			sleep(5);
			g_inventorys.print_all();
			t.join();
		}
	}
	void test_out()
	{
		//thread_safe_observable::test();
		//test_weak_call_back::test();
		//test_mutex::test();
		test_mutex_between_threads::test();
	}
	
}