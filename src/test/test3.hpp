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
namespace test3_namespace
{
	using muduo::string;
	class observer
	{
	public:
		observer(foo* s):m_foo(s)
		{
			m_foo->register_observer(this);
		}
		~observer()
		{
			m_foo->unregister_observer(this);
		}
		void update()
		{
			std::cout<<"observer update"<<std::endl;
		}
	private:
		foo* m_foo;
	};
	class foo
	{
	public:
		void register_observer(observer* s)
		{
			m_observers.push_back(s);
		}
		void unregister_observer(observer* s)
		{
			m_observers.erase(s);
		}
		void test()
		{
			for(auto& i:m_observers)
			{
				i->update();
			}
		}
	private:
		std::vector<observer*> m_observers;
	};
	void test_out()
	{
		foo *f=new foo();
		observer o=new observer(f);
		delete f;
		o->test();
		
	}
}