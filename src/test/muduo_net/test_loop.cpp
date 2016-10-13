#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <stdio.h>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <stdio.h>
#include <sstream>
using namespace muduo::net;

EventLoop* g_loop = NULL;

int main(int argc, char* argv[])
{
  muduo::Logger::setLogLevel(muduo::Logger::LogLevel::TRACE);
  EventLoop loop;
  g_loop = &loop;
  muduo::Thread t([&](){g_loop.loop();});
  t.start();
  t.join();
  
}
