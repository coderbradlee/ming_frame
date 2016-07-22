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
	namespace test_observer_thread_safe
	{
		void observer::observe(observable* s)
		{
			s->register1(shared_from_this());
			m_subject=s;
		}
		
		//void observable::register1(const boost::weak_ptr<observer>& x)
		void observable::register1(const boost::shared_ptr<observer>& x)
		{
			m_observers.push_back(x);
		}
		void observable::notify()
		{
			muduo::MutexLockGuard lock(m_mutex);
			auto it=m_observers.begin();
			while(it!=m_observers.end())
			{
				//boost::shared_ptr<observer> obj(it->lock());
				boost::shared_ptr<observer> obj=*it;
				if(obj)
				{
					obj->update();
					++it;
				}
				else
				{
					LOG_INFO<<"erase observer";
					it=m_observers.erase(it);
				}
			}
		}
		
		void foo::update()
		{
			LOG_INFO<<"FOO update:"<<(size_t)this;
		}
		
		void test()
		{
			{
				observable sub;
				{
					boost::shared_ptr<foo> p(new foo());
					p->observe(&sub);
					sub.notify();
				}
				sub.notify();
			}
			LOG_INFO<<"after observable destructor";
			//sub 析构后，observer会不会调用析构函数？
			
		}
	}
	void test1()
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
		//test_design_model_interpreter::test();
		test_observer_thread_safe::test();
	}
}