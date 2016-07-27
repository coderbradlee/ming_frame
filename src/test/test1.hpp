#ifndef TEST1_HPP
#define	TEST1_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test1
{
	namespace test_timing_wheel_idleconnection
	{
		class echo_server
		{
		public:
			echo_server(muduo::net::EventLoop* loop,const muduo::net::InetAddress& la,int idle_seconds);
			void start();
		private:
			void on_connection(const muduo::net::TcpConnectionPtr& conn);
			void on_message(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf,muduo::Timestamp time);
			void on_timer();
			void dump_connection_buckets()const;
			typedef boost::weak_ptr<muduo::net::TcpConnection> weak_tcpconnection_ptr;
			struct entry:public muduo::copyable
			{
				explicit entry(const weak_tcpconnection_ptr& w):m_weak_conn(w){}
				~entry()
				{
					muduo::net::TcpConnectionPtr conn=m_weak_conn.lock();
					if(conn)
					{
						conn->shutdown();
					}
				}
				weak_tcpconnection_ptr m_weak_conn;
			};
			typedef boost::shared_ptr<entry> entry_ptr;
			typedef boost::weak_ptr<entry> weak_entry_ptr;
			typedef boost::unordered_set<entry_ptr> bucket;
			typedef boost::circular_buffer<bucket> weak_connection_list;
			muduo::net::TcpServer m_server;
			weak_connection_list m_connection_buckets;
		};
		void test();
	}
	namespace test_round_trip
	{
		typedef boost::shared_ptr<muduo::net::TcpConnection> TcpConnectionPtr;
		void serverConnectionCallback(const TcpConnectionPtr& conn);

		void serverMessageCallback(const TcpConnectionPtr& conn,
		                           muduo::net::Buffer* buffer,
		                           muduo::Timestamp receiveTime);

		void runServer(uint16_t port);

		void clientConnectionCallback(const TcpConnectionPtr& conn);

		void clientMessageCallback(const TcpConnectionPtr&,
		                           muduo::net::Buffer* buffer,
		                           muduo::Timestamp receiveTime);

		void sendMyTime();
		void testHash();
		void runClient(const char* ip, uint16_t port);
		void test();
	}
	namespace test_muduo_multithread_timer_shortcritical_section
	{
		class printer:boost::noncopyable
		{
		public:
			printer(muduo::net::EventLoop* loop1,muduo::net::EventLoop* loop2);
			~printer()
			{
				LOG_INFO<<"printer destructor";
			}
		private:
			void print1();
			void print2();
		private:	
			muduo::MutexLock m_mutex;		
			muduo::net::EventLoop* m_loop1;
			muduo::net::EventLoop* m_loop2;
			int m_count;
		};
		void test();
	}
	namespace test_muduo_multithread_timer
	{
		class printer:boost::noncopyable
		{
		public:
			printer(muduo::net::EventLoop* loop1,muduo::net::EventLoop* loop2);
			~printer()
			{
				LOG_INFO<<"printer destructor";
			}
		private:
			void print1();
			void print2();
		private:	
			muduo::MutexLock m_mutex;		
			muduo::net::EventLoop* m_loop1;
			muduo::net::EventLoop* m_loop2;
			int m_count;
		};
		void test();
	}
	namespace test_muduo_asio_timer
	{
		class printer:boost::noncopyable
		{
		public:
			printer(muduo::net::EventLoop* loop);
			~printer()
			{
				LOG_INFO<<"printer destructor";
			}
		private:
			void print();
		private:			
			muduo::net::EventLoop* m_loop;
			int m_count;
		};
		void test();

	}
	namespace test_exit_thread
	{
		class calendar:boost::noncopyable
		{
		public:
			virtual bool is_holiday(const string&)const=0;
			virtual ~calendar(){}
		};
		class american_calendar:public calendar
		{
		public:
			bool is_holiday(const string&)const;

		};
		class british_calendar:public calendar
		{
		public:
			bool is_holiday(const string&)const;
			
		};
		calendar& get_calendar();

		void test();
	}
	namespace test_thread_safe_counter
	{
		class counter:boost::noncopyable
		{
		public:
			counter():m_value(0){}
			int64_t value()const;
			int64_t get_increase();
		private:
			int64_t m_value;
			mutable muduo::MutexLock m_mutex;
		};
		void test();
	}
	namespace test_observer_thread_safe
	{
		class observable;
		class observer:public boost::enable_shared_from_this<observer>
		{
		public:
			virtual ~observer()
			{
				LOG_INFO<<"observer destructor";
			}
			virtual void update()=0;
			void observe(observable* s);
		protected:
			observable* m_subject;
		};
		class observable
		{
		public:
			//void register1(const boost::weak_ptr<observer>& x);
			void register1(const boost::shared_ptr<observer>& x);
			void notify();
			~observable()
			{
				LOG_INFO<<"observable destructor";
			}
		private:
			mutable muduo::MutexLock m_mutex;
			//std::vector<boost::weak_ptr<observer>> m_observers;
			std::vector<boost::shared_ptr<observer>> m_observers;
			//换成shared_ptr observer的析构不会被调用？
		};
		class foo:public observer
		{
		public:
			void update();
		};
		void test();
	}
	namespace test_weak_ptr
	{
		class stock:boost::noncopyable
		{
		public:
			stock(const string& name):m_name(name)
			{
				LOG_INFO<<"constructor:"<<(intptr_t)this<<":"<<m_name;
			}
			~stock()
			{
				LOG_INFO<<"destructor:"<<(intptr_t)this<<":"<<m_name;
			}
			const string get_key()const
			{
				return m_name;
			}
		private:
			string m_name;
		};
		class stock_factory:public boost::enable_shared_from_this<stock_factory>,boost::noncopyable
		{
		public:
			boost::shared_ptr<stock> get(const string& key);
		
			static 
			void weak_delete_stock(const boost::weak_ptr<stock_factory>& wk,stock* s);
		private:
			void remove_stock(stock* s);
		private:
			mutable muduo::MutexLock m_mutex;
			std::map<string,boost::weak_ptr<stock>> m_stocks;
		};
		void testLongLifeFactory();
		void testShortLifeFactory();
		void test();
	}
	namespace test_using_nonrecursive_mutex
	{
		class foo;
		void post(const foo& f);
		class foo
		{
		public:
			void doit()
			{
				LOG_INFO<<"do";
				post(*this);
			}
		};
		
		void traverse();


		void test();

	}
	namespace test_dead_lock
	{
		class request
		{
		public:
			void process();
			void print()const;
			~request();
		private:
			mutable muduo::MutexLock m_mutex;
		};
		class inventory
		{
		public:
			void add(request* req);
			void remove(request* req);
			void print_all()const;
		private:
			mutable muduo::MutexLock m_mutex;
			std::set<request*> m_requests;
		};
		void thread_func();
		void test();
	}
	void test1();
}
#endif

