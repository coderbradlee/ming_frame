#ifndef TEST1_HPP
#define	TEST1_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test1
{
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
				LOG_INFO<<"constructor:"<<this<<":"<<m_name;
			}
			~stock()
			{
				LOG_INFO<<"destructor:"<<this<<":"<<m_name;
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
		private:
			static void weak_delete_stock(const boost::weak_ptr<stock_factory>& wk,stock* s);
			void remove_stock(stock* s);
		private:
			mutable muduo::MutexLock m_mutex;
			std::map<string,boost::weak_ptr<stock>> m_stocks;
		};
		void testLongLifeFactory();
		void testShortLifeFactory();
		void test();
	}
	void test1();
}
#endif

