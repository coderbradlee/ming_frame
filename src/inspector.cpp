#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
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
  EventLoopThread t;
  Procmon procmon(t.startLoop(), getpid(), 12345, "Inspector");
  //procmon.start();
  loop.loop();
}