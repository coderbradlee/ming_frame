#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <boost/thread/thread.hpp> 
#include "procmon.hpp"
using namespace muduo;
using namespace muduo::net;

void start_inspector()
{
  // EventLoop loop;
  // EventLoopThread t;
  // Inspector ins(t.startLoop(), InetAddress(12345), "test");
  // loop.loop();
  EventLoop loop;
  Procmon procmon(&loop, getpid(), 12345, "Inspector");
  procmon.start();

  Inspector ins(&loop, InetAddress(54321), "Inspector");
  loop.loop();


	// EventLoop loop;
 //    EventLoopThread t;
 //    Procmon procmon(t.startLoop(),getpid(), 12345, "Inspector");
 //    procmon.start();
 //    loop.loop();
}
void start_inspector_thread()
{
  muduo::Thread thrd(boost::bind(&start_inspector), "monitor");
	//boost::thread thrd(&start_inspector);  
  thrd.start();
  test_procmon obj;  
  //muduo::Thread thrd2(test_procmon(), "dummyload");
  muduo::Thread thrd2(boost::bind(&test_procmon::start, &obj), "dummyload"); 
                     
  thrd.join();
  thrd2.join();
}