#ifndef TEST2_HPP
#define	TEST2_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test2_namespace
{
	namespace thread_safe_observable
	{
		class observer;
		class observable
		{
		public:
			void register(boost::weak_ptr<observer> x);
			void notify();
		private:
			mutable muduo::MutexLock m_mutex;
			std::vector<boost::weak_ptr<observer>> m_observers;
		};
		class observer:public boost::enable_shared_from_this<observer>
		{
		public:
			virtual ~observer();
			virtual void update();
			void observe(observable* s);
		private:
			observable* m_observable;
		};
	}
	void test_out();
}
#endif

