#ifndef TEST2_HPP
#define	TEST2_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test2_namespace
{
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
	void test_out();
}
#endif

