#include "test2.hpp"
namespace test2_namespace
{
	using muduo::string;
	
	namespace thread_safe_observable
	{
		
		void observable::register(boost::weak_ptr<observer> x)
		{
			m_observers.push_back(x);
		}
		void observable::notify()
		{
			muduo::MutexLockGuard lock(m_mutex);
			m_observers.erase(std::remove_if(m_observers.begin(),m_observers.end(),[](boost::weak_ptr<observer> x)
			{
				boost::shared_ptr<observer> obj(x.lock());
				if(obj)
				{
					obj->update();
					return false;
				}
				return true;
			}),m_observers.end());
		}
		
		observable::~observable()
		{
			std::cout<<"~observable"<<std::endl;
		}
		observer::~observer()
		{
			std::cout<<"~observer"<<std::endl;
		}
		void observer::update()
		{
			std::cout<<"update"<<std::endl;
		}
		void observer::observe(observable* s)
		{
			s->register(shared_from_this());
			m_observable=s;
		}
	
	}
	void test_out()
	{
		observable able;
		{
			boost::shared_ptr<observer> p(new observer());
			p->observe(&able);
			able->notify();
		}
		able.notify();
	}
	
}