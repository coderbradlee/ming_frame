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
	
	void test1();
}
#endif

