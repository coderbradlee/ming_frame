#ifndef TEST2_HPP
#define	TEST2_HPP
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
namespace test2_namespace
{
	namespace test_inline
	{
		class printer
		{
		public:
			printer();
			//~printer();
		private:
			class impl;
			boost::scoped_ptr<impl> m_impl;
		};
		void test();
	}
	namespace test_multithreadloop_multiconnect
	{
		void connectCallback(int sockfd);
		void test();
	}
	namespace test_mutex_between_threads
	{
		class request;
		class inventory
		{
		public:
			void add(boost::shared_ptr<request> r);
			void remove(boost::shared_ptr<request> r);
			void print_all()const;
		private:
			mutable muduo::MutexLock m_mutex;
			boost::shared_ptr<std::set<boost::shared_ptr<request>>> m_requests;
		};

		class request:public boost::enable_shared_from_this<request>
		{
		public:
			void process();
			void print()__attribute__((noinline));
			~request()__attribute__((noinline));
			void cancel()__attribute__((noinline));
		private:
			mutable muduo::MutexLock m_mutex;
		};
		void thread_func();
		void test();
	}
	namespace test_mutex
	{
		class request
		{
		public:
			void process();
			void print();
		private:
			mutable muduo::MutexLock m_mutex;
		};
		void test();
	}
	namespace thread_safe_observable
	{
		class observable;
		class observer:public boost::enable_shared_from_this<observer>
		{
		public:
			virtual ~observer();
			virtual void update();
			void observe(observable* s);
		private:
			observable* m_observable;
		};
		class observable
		{
		public:
			void register_(boost::weak_ptr<observer> x);
			void notify();
			~observable();
		private:
			mutable muduo::MutexLock m_mutex;
			std::vector<boost::weak_ptr<observer>> m_observers;
		};
	}
	namespace test_weak_call_back
	{
		using muduo::string;
		class stock
		{
		public:
			stock(const string& name);
			~stock();
			const string& key()const;
		private:
			string m_name;
		};
		class stock_factory:public boost::enable_shared_from_this<stock_factory>
		{
		public:
			boost::shared_ptr<stock> get(const string& key);
		private:
			static void weak_call_back(const boost::weak_ptr<stock_factory>&,stock* s);
			void remove_stock(stock* s);
		private:
			mutable muduo::MutexLock m_mutex;
			std::map<string,boost::weak_ptr<stock>> m_stocks;
		};

		void test();
	}
	void test_out();
}
#endif

