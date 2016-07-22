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
			virtual ~observer(){}
			virtual void update()=0;
			void observe(observable* s);
		protected:
			observable* m_subject;
		};
		class observable
		{
		public:
			void register(const boost::weak_ptr<observer>& x);
			void notify();
		private:
			mutable muduo::MutexLock m_mutex;
			std::vector<boost::weak_ptr<observer>> m_observers;

		};
		class foo:public observer
		{
		public:
			void update();
		}
		void test();
	}
	void test1();
}
#endif

