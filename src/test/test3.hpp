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
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
namespace test3_namespace
{
	using muduo::string;
	class foo;
	class observer:public boost::enable_shared_from_this<observer>
	{
	public:
		observer(boost::shared_ptr<foo> s);
		~observer();
		void update()
		{
			std::cout<<"observer update"<<std::endl;
		}
	private:
		boost::shared_ptr<foo> m_foo;
	};
	class foo
	{
	public:
		void register_observer(boost::weak_ptr<observer> s)
		{
			std::cout<<"foo::register_observer"<<std::endl;
			m_observers.push_back(s);
		}
		// void unregister_observer(boost::weak_ptr<observer> s)
		// {
		// 	for(auto i=m_observers.begin();i!=m_observers.end();++i)
		// 	{
		// 		boost::shared_ptr<observer> temp(i->lock());
		// 		if(temp)
		// 		{
		// 			m_observers.erase(i);
		// 			break;
		// 		}
				
		// 	}
			
		// }
		void test()
		{
			std::cout<<"foo::test"<<std::endl;
			for(auto i=m_observers.begin();i!=m_observers.end();++i)
			{
				boost::shared_ptr<observer> temp(i->lock());
				if(temp)
				{
					temp->update();
				}
				else
				{
					m_observers.erase(i);
				}
			}
		}
	private:
		std::vector<std::weak_ptr<observer>> m_observers;
	};
	observer::observer(boost::shared_ptr<observer> s):m_foo(s)
	{
		std::cout<<"observer::observer"<<std::endl;
		m_foo->register_observer(shared_from_this());
	}
	observer::~observer()
	{
		std::cout<<"observer::~observer"<<std::endl;
		// m_foo->unregister_observer(shared_from_this());
	}
	void test_out()
	{
		boost::shared_ptr<foo> f=boost::make_shared<foo>();
		{
			boost::shared_ptr<observer> o=boost::make_shared<observer>(f);
			f->test();
		}
		
		
	}
}