#include "test1.hpp"
namespace test1
{
	namespace test_thread_safe_counter
	{
		
		int64_t counter::value()const
		{
			muduo::MutexLockGuard lock(m_mutex);
			return m_value;
		}
		int64_t counter::get_increase()
		{
			muduo::MutexLockGuard lock(m_mutex);
			int64_t ret=m_value++;
			return ret;
		}
		
		void test()
		{

		}
	}
	
	void test()
	{
		//test_model_design_factory::test();
		//test_model_design_prototype::test();
		//test_model_design_builder::test();
		//test_deadline_timer::test();
		//test_json_parser::test();
		//test_design_model_flyweight::test();
		//test_design_model_state::test();
		//test_design_model_composite::test();
		//test_design_model_chainofresponsibility::test();
		//test_design_model_visitor::test();
		test_design_model_interpreter::test();
	}
}