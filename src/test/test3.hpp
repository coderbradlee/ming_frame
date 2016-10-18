#include "../log.hpp"
#include "../include.hpp"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/Connector.h>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <muduo/base/LogStream.h>
#include <execinfo.h>
namespace test3_namespace
{
	using std::string;
	class foo;
	class observer:public boost::enable_shared_from_this<observer>
	{
	public:
		observer(boost::shared_ptr<foo> s);
		void observe();
		~observer();
		void update()
		{
			std::cout<<"observer update"<<std::endl;
		}
	private:
		boost::shared_ptr<foo> m_foo;
	};
	class foo
	{
	public:
		void register_observer(boost::weak_ptr<observer> s)
		{
			std::cout<<"foo::register_observer"<<std::endl;
			m_observers.push_back(s);
		}
		// void unregister_observer(boost::weak_ptr<observer> s)
		// {
		// 	for(auto i=m_observers.begin();i!=m_observers.end();++i)
		// 	{
		// 		boost::shared_ptr<observer> temp(i->lock());
		// 		if(temp)
		// 		{
		// 			m_observers.erase(i);
		// 			break;
		// 		}
				
		// 	}
			
		// }
		void test()
		{
			std::cout<<"foo::test"<<std::endl;
			auto i=m_observers.begin();
			 while (i != m_observers.end())
			{
				boost::shared_ptr<observer> temp(i->lock());
				if(temp)
				{
					temp->update();
					++i;
				}
				else
				{
					std::cout<<"foo::test::erase"<<std::endl;
					i = m_observers.erase(i);
				}
			}
		}
	private:
		std::vector<boost::weak_ptr<observer>> m_observers;
	};
	observer::observer(boost::shared_ptr<foo> s):m_foo(s)
	{
		std::cout<<"observer::observer"<<std::endl;
		//m_foo->register_observer(shared_from_this());
	}
	void observer::observe()
	{
		std::cout<<"observer::observe"<<std::endl;
		m_foo->register_observer(shared_from_this());
	}
	observer::~observer()
	{
		std::cout<<"observer::~observer"<<std::endl;
		// m_foo->unregister_observer(shared_from_this());
	}
	class stock
	{
	public:
		stock(const string& name):m_name(name)
		{
			std::cout<<"stock constructor"<<std::endl;
		}
		~stock()
		{
			std::cout<<"stock destructor"<<std::endl;
		}
		string get_name()const
		{
			return m_name;
		}
	private:
		string m_name;
	};
	class stock_factory:public boost::enable_shared_from_this<stock_factory>,boost::noncopyable
	{
	public:
		stock_factory()
		{
			std::cout<<"stock_factory constructor"<<std::endl;
		}
		~stock_factory()
		{
			std::cout<<"stock_factory destructor"<<std::endl;
		}
		boost::shared_ptr<stock> get_stock(const string& key)
		{
			boost::shared_ptr<stock> temp;
			//boost::weak_ptr<stock> temp_weak;
			
			muduo::MutexLockGuard lo(m_mutex);
			boost::weak_ptr<stock>& temp_weak=m_stocks[key];
			temp=temp_weak.lock();
			
			if(temp)
			{
				return temp;
			}
			else
			{
				temp.reset(new stock(key),boost::bind(&stock_factory::weak_delete_callback,boost::weak_ptr<stock_factory>(shared_from_this()),_1));
				temp_weak=temp;
			}
			return temp;
		}
	private:
		static void weak_delete_callback(const boost::weak_ptr<stock_factory>& ptr_self,stock* s)
		{
			if(ptr_self.lock())
			{
				std::cout<<"weak_delete_callback::remove"<<std::endl;
				ptr_self.lock()->remove_stock(s);
			}
			else
			{
				std::cout<<"weak_delete_callback::stock_factory die"<<std::endl;
			}
			delete s;
		}
		void remove_stock(stock* s)
		{
			if(s)
			{
				muduo::MutexLockGuard lo(m_mutex);
				m_stocks.erase(s->get_name());
			}
		}
	private:
		std::map<string,boost::weak_ptr<stock>> m_stocks;
		mutable muduo::MutexLock m_mutex;

	};
	class test_self_lock
	{
	public:
		test_self_lock()
		{}
		~test_self_lock()
		{}
		void process()__attribute__((noinline))
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"process"<<std::endl;
			print();
		}
		void print()__attribute__((noinline))
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"print"<<std::endl;
		}
	private:
		mutable muduo::MutexLock m_mutex;
	};
	class request
	{
	public:
		//request();
		~request();
		void process();
		void print();
	private:
		mutable muduo::MutexLock m_mutex;
	};
	class inventory
	{
	public:
		inventory(){}
		~inventory(){}
		void add(request* r)
		{
			muduo::MutexLockGuard lo(m_mutex);
			m_requests.insert(r);
		}
		void remove(request* r)
		{
			muduo::MutexLockGuard lo(m_mutex);
			m_requests.erase(r);
		}
		void print_all()const
		{
			muduo::MutexLockGuard lo(m_mutex);
			std::cout<<"void print_all()const"<<std::endl;

			for(auto i=m_requests.begin();i!=m_requests.end();++i)
			{
				std::cout<<"void print_all()const::for"<<std::endl;
				sleep(5);
				(*i)->print();
			}
			std::cout<<"void print_all()const::finish"<<std::endl;
		}
	private:
		std::set<request*> m_requests;
		mutable muduo::MutexLock m_mutex;
	};
	inventory g_inventory;
	
	request::~request()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"request::~request()"<<std::endl;
		sleep(3);
		//usleep(500*1000);
		g_inventory.remove(this);
	}
	void request::process()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"request::process()"<<std::endl;
		g_inventory.add(this);
	}
	void request::print()
	{
		muduo::MutexLockGuard lo(m_mutex);
		std::cout<<"print"<<std::endl;
	}
	muduo::MutexLock mutex;
	muduo::Condition cond(mutex);
	std::deque<int> test_queue;
	int dequeue()
	{
		muduo::MutexLockGuard lo(mutex);
		while(test_queue.empty())
		{
			std::cout<<"before wait"<<std::endl;
			cond.wait();
			std::cout<<"after wait"<<std::endl;
		}
		int top=test_queue.front();
		test_queue.pop_front();
		return top;
	}
	void enqueue(int x)
	{
		muduo::MutexLockGuard lo(mutex);
		test_queue.push_back(x);
		cond.notify();
	}
	class my_mutex
	{
	public:
		my_mutex():m_owner_thread_id(0)
		{
			pthread_mutex_init(&m_mutex,NULL);
			pthread_mutexattr_t mattr;
			pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_NORMAL);
		}
		~my_mutex()
		{
			pthread_mutex_destroy(&m_mutex);
		}
		void lock()
		{
			pthread_mutex_lock(&m_mutex);
			m_owner_thread_id=1;
		}
		void unlock()
		{
			m_owner_thread_id=0;
			pthread_mutex_unlock(&m_mutex);
		}
		pthread_mutex_t* getPhreadMutex()
		{
			return &m_mutex;
		}
	private:
		pthread_mutex_t m_mutex;
		pid_t m_owner_thread_id;
	};
	class my_condition
	{
	public:
		my_condition(my_mutex& mu):m_mutex(mu)
		{
			pthread_cond_init(&m_cond,NULL);
		}
		~my_condition()
		{
			pthread_cond_destroy(&m_cond);
		}
		void wait()
		{
			pthread_cond_wait(&m_cond,m_mutex.getPhreadMutex());
		}
		void notify()
		{
			pthread_cond_signal(&m_cond);
		}
		void notifyall()
		{
			pthread_cond_broadcast(&m_cond);
		}
	private:
		my_mutex& m_mutex;
		pthread_cond_t m_cond;
	};
	template<typename T>
	class my_singleton
	{
	public:
		static T get_instance()
		{
			pthread_once(&m_once,&my_singleton::init);
			return *m_instatnce;
		}
		void init()
		{
			m_instatnce=new T();
		}
	private:
		my_singleton();
		~my_singleton();
	private:
		static pthread_once_t m_once;
		static T* m_instatnce;
	};
	template<typename T>
	pthread_once_t my_singleton<T>::m_once=PTHREAD_ONCE_INIT;
	template<typename T>
	T* my_singleton<T>::m_instatnce=NULL;
	class foo_copy_on_write;
	void post(foo_copy_on_write f);
	class foo_copy_on_write
	{
	public:
		void doit()const
		{
			foo_copy_on_write f;
			post(f);
		}
		
	};
	boost::shared_ptr<std::vector<foo_copy_on_write>> g_foo_copy_on_write;
	muduo::MutexLock mutex_copy_on_write;
	void post(foo_copy_on_write f)
	{
		std::cout<<"post"<<std::endl;
		muduo::MutexLockGuard lo(mutex_copy_on_write);
		if(!g_foo_copy_on_write.unique())
		{
			g_foo_copy_on_write.reset(new std::vector<foo_copy_on_write>(*g_foo_copy_on_write));
			std::cout<<"copy the whole vector"<<std::endl;
		}
		g_foo_copy_on_write->push_back(f);
	}
	void traverse()
	{
		std::cout<<"traverse"<<std::endl;
		boost::shared_ptr<std::vector<foo_copy_on_write>> local_ptr;
		{
			muduo::MutexLockGuard lo(mutex_copy_on_write);
			local_ptr=g_foo_copy_on_write;
		}
		
		for(auto i=local_ptr->begin();i!=local_ptr->end();++i)
		{
			(*i).doit();
		}
		std::cout<<g_foo_copy_on_write->size()<<std::endl;
	}
	class customer_data
	{
	public:
		customer_data():m_data_ptr(new std::map<string,std::vector<std::pair<string,int>>>())
		{

		}
		int query(const string& customer,const string& stock)
		{
			boost::shared_ptr<std::map<string,std::vector<std::pair<string,int>>>> temp_data_ptr;
			{
				muduo::MutexLockGuard lo(m_mutex);
				temp_data_ptr=m_data_ptr;
			}
			auto it=(*temp_data_ptr)[customer].begin();
			auto end=(*temp_data_ptr)[customer].end();
			while(it!=end)
			{
				if(it->first==stock)
				{
					return it->second;
				}
				++it;
			}
			return -1;
		}
		void update_one(const string& customer,const string& stock,int num)
		{
			{
				muduo::MutexLockGuard lo(m_mutex);
				if(!m_data_ptr.unique())
				{
					boost::shared_ptr<std::map<string,std::vector<std::pair<string,int>>>> p_temp(new std::map<string,std::vector<std::pair<string,int>>>(*m_data_ptr));
					m_data_ptr.swap(p_temp);
				}
			}
			
			if((*m_data_ptr).count(customer)>0)
			{
				auto it=(*m_data_ptr)[customer].begin();
			
				auto end=(*m_data_ptr)[customer].end();
				while(it!=end)
				{
					if(it->first==stock)
					{
						it->second=num;
					}
					++it;
				}
				if(it==end)
				{
					(*m_data_ptr)[customer].push_back(std::make_pair(stock, num));
				}
			}
			else
			{
				std::vector<std::pair<string,int>> v;
				v.push_back(std::make_pair(stock, num));
				(*m_data_ptr)[customer]=v;
			}
			
		}
	private:
		mutable muduo::MutexLock m_mutex;
		//std::map<string,std::vector<std::pair<string,int>>> m_data;
		boost::shared_ptr<std::map<string,std::vector<std::pair<string,int>>>> m_data_ptr;
	};
	class test_blocking_queue
	{
	public:
		test_blocking_queue(int threads_num):m_latch(threads_num),m_threads(threads_num)
		{
			for(int i=0;i<threads_num;++i)
			{
				char name[32];
				snprintf(name,sizeof name,"thread:%d",i);
				m_threads.push_back(new muduo::Thread(boost::bind(&test_blocking_queue::thread_func,this),name));
			}
			for_each(m_threads.begin(),m_threads.end(),boost::bind(&muduo::Thread::start,_1));
		}
		void thread_func()
		{
			printf("%d:%s start\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
			m_latch.countDown();
			bool running=true;
			while(running)
			{
				std::string temp(m_queue.take());
				//printf("%d:%s get %s:%d\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name(),temp.c_str(),m_queue.size());
				running=(temp!="stop");
			}
			printf("%d:%s stop\n",muduo::CurrentThread::tid(),muduo::CurrentThread::name());
		}
		void run(int times)
		{
			// printf("wait for countDown\n");
			// m_latch.wait();
			// printf("all threads started\n");
			// for(int i=0;i<times;++i)
			// {
			// 	char data[32];
			// 	snprintf(data,sizeof data,"hello %d",i);
			// 	m_queue.put(data);
			// 	printf("%d:%s put %s:%d\n", muduo::CurrentThread::tid(),muduo::CurrentThread::name(),data,m_queue.size());
			// }
		}
		void joinAll()
		{
			// for(size_t i=0;i<m_threads.size();++i)
			// {
			// 	printf("%d:%s put %s:%d\n", muduo::CurrentThread::tid(),muduo::CurrentThread::name(),"stop",m_queue.size());
			// 	m_queue.put("stop");
			// }
			// for_each(m_threads.begin(),m_threads.end(),boost::bind(&muduo::Thread::join,_1));
		}
		
	private:
		muduo::BlockingQueue<std::string> m_queue;
		muduo::CountDownLatch m_latch;
		boost::ptr_vector<muduo::Thread> m_threads;
	};
	void test_get_pid_benchmark()
	{
		// {
		// 	muduo::Timestamp start = muduo::Timestamp::now();
		// 	for(int i=0;i<1000*1000;++i)
		// 	{
		// 		muduo::CurrentThread::tid();
		// 	}
		// 	printf("%d\n", muduo::CurrentThread::tid());
	 //    	muduo::Timestamp end = muduo::Timestamp::now();

	 //    	printf("%f\n", timeDifference(end, start));
		// }
		// {
		// 	muduo::Timestamp start = muduo::Timestamp::now();
		// 	for(int i=0;i<1000*1000;++i)
		// 	{
		// 		boost::this_thread::get_id();
		// 	}
		// 	printf("%d\n", boost::this_thread::get_id());
	 //    	muduo::Timestamp end = muduo::Timestamp::now();
	 //    	printf("%f\n", timeDifference(end, start));
		// }
	}
	void test_log()
	{
		// muduo::Timestamp start = muduo::Timestamp::now();
		// std::string line="1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ " ;
		// for(int i=0;i<1000*10000;++i)
		// {
		// 	LOG_INFO << line<< i;
		// }
  //   	muduo::Timestamp end = muduo::Timestamp::now();
  //   	printf("%f\n", timeDifference(end, start));
	 //    printf("%fMB/s\n",line.length()*10.0/timeDifference(end, start) );
	}
	void test_snprintf()
	{
		{
			char buf[32];
			int value=10;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<1000000;++i)
			{
				snprintf(buf, sizeof buf, "%d", value);
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"snprintf int:"<<total<<std::endl;
		}
		{
			char buf[32];
			double value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<1000000;++i)
			{
				snprintf(buf, sizeof buf, "%f", value);
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"snprintf double:"<<total<<std::endl;
		}
		{
			char buf[32];
			int64_t value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<1000000;++i)
			{
				snprintf(buf, sizeof buf, "%" PRId64 "\n", value);
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"snprintf int64_t:"<<total<<std::endl;
		}
		{
			char buf[32];
			void* value=buf;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<1000000;++i)
			{
				snprintf(buf, sizeof buf, "%d", value);
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"snprintf void*:"<<total<<std::endl;
		}
	}
	void test_ostringstream()
	{
		{
			int value=10;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			std::ostringstream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"ostringstream int:"<<total<<std::endl;
		}
		{
			double value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			std::ostringstream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"ostringstream double:"<<total<<std::endl;
		}
		{
			int64_t value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			std::ostringstream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"ostringstream int64_t:"<<total<<std::endl;
		}
		{
			void* value=nullptr;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			std::ostringstream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"ostringstream void*:"<<total<<std::endl;
		}
	}
	void test_logstream()
	{
		{
			int value=10;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			muduo::LogStream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"logstream int:"<<total<<std::endl;
		}
		{
			double value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			muduo::LogStream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"logstream double:"<<total<<std::endl;
		}
		{
			int64_t value=10.0;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			muduo::LogStream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"logstream int64_t:"<<total<<std::endl;
		}
		{
			void* value=nullptr;
			muduo::Timestamp g_start=muduo::Timestamp::now();
			muduo::LogStream os;
			for(int i=0;i<1000000;++i)
			{
				os<<value;
			}		
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"logstream void*:"<<total<<std::endl;
		}
	}
	void reverse1(char* str,int n)
	{
		char* begin=str;
		char* end= str+n-1;
		while(begin<end)
		{
			char tmp=*begin;
			*begin=*end;
			*end=tmp;
			++begin;
			--end;
		}
	}
	void reverse2(char* str,int n)
	{
		char* begin=str;
		char* end=str+n-1;
		while(begin<end)
		{
			*begin^=*end;
			*end^=*begin;
			*begin^=*end;
			++begin;
			--end;
		}
	}
	void reverse3(char* str,int n)
	{
		std::reverse(str,str+n);
	}
	void test_reverse()
	{
		char test[]="abcdefghijklmnopqrstuvwxyz";
		{
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<100000000;++i)
			{
				reverse1(test,strlen(test));
			}
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"reverse1:"<<total<<std::endl;
		}
		{
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<100000000;++i)
			{
				reverse2(test,strlen(test));
			}
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"reverse2:"<<total<<std::endl;
		}
		{
			muduo::Timestamp g_start=muduo::Timestamp::now();
			for(int i=0;i<100000000;++i)
			{
				reverse3(test,strlen(test));
			}
			double total = timeDifference(Timestamp::now(), g_start);
	   		std::cout<<"reverse3:"<<total<<std::endl;
		}
	}
	void bt(void) 
	{
	    int c, i;
	    void *addresses[10];
	    char **strings; 

	    c = backtrace(addresses, 10);
	    strings = backtrace_symbols(addresses,c);
	    printf("backtrace returned: %dn", c);
	    for(i = 0; i < c; i++) 
	    {
	        printf("%d: %ld \n", i, (long)addresses[i]);
	        printf("%sn\n", strings[i]); 
	    }
    }
	void test_out()
	{
		bt();
		//test_reverse();
		// test_snprintf();
		// test_ostringstream();
		// test_logstream();
		//test_log();
		//test_get_pid_benchmark();
		// printf("%d: main\n",muduo::CurrentThread::tid);
		// test_blocking_queue t(3);
		// t.run(10);
		// t.joinAll();
		// printf("nums of created threads:%d\n",muduo::Thread::numCreated() );
		// muduo::BlockingQueue<std::unique_ptr<int>> test_queue;
		// test_queue.put(std::unique_ptr<int>(new int(3)));
		// std::unique_ptr<int> x=test_queue.take();
		// printf("%d\n",*x);
		// *x=2;
		// test_queue.put(std::move(x));
		// std::unique_ptr<int> x2=test_queue.take();
		// printf("%d\n", *x2);

		// customer_data data;
		// muduo::Thread t1([&]()
		// 	{
		// 		data.update_one("test_customer1","stock1",1);
		// 		data.update_one("test_customer1","stock2",2);
		// 		data.update_one("test_customer2","stock3",3);
		// 	});
		// t1.start();
		
		// muduo::Thread t2([&]()
		// 	{
		// 		std::cout<<data.query("test_customer1","stock2")<<std::endl;
		// 	});
		// t2.start();
		
		// t1.join();
		// t2.join();
		// g_foo_copy_on_write.reset(new std::vector<foo_copy_on_write>());
		// foo_copy_on_write f;
		// post(f);
		// traverse();
		// my_mutex test_mutex;
		// test_mutex.lock();
		// test_mutex.unlock();
		// my_condition m(test_mutex);
		// muduo::Thread t1([]()
		// 	{
		// 		std::cout<<dequeue()<<std::endl;
		// 	});
		// t1.start();

		// muduo::Thread t2([]()
		// 	{
		// 		enqueue(3);
		// 	});
		// t2.start();
		// t2.join();
		// t1.join();
		
		// muduo::Thread t([]()
		// 	{
		// 		request* r=new request();
		// 		r->process();
		// 		delete r;
		// 	});
		// t.start();
		// //usleep(500*1000);
		// sleep(1);
		// g_inventory.print_all();
		// t.join();
		
		// test_self_lock t;
		// t.process();
		// {
		// 	boost::shared_ptr<stock_factory> sf(new stock_factory());
		// 	{
		// 		boost::shared_ptr<stock> s1=sf->get_stock("us");
		// 		boost::shared_ptr<stock> s2=sf->get_stock("uk");
		// 	}
		// }
		// std::cout<<"------------------------------"<<std::endl;
		// {
		// 	boost::shared_ptr<stock> s;
		// 	{
		// 		boost::shared_ptr<stock_factory> sf(new stock_factory());
		// 		s=sf->get_stock("ll");
		// 	}
		// 	std::cout<<s->get_name()<<std::endl;
		// }
	}
}