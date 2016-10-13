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
#include <sys/timerfd.h>
#include <muduo/net/Channel.h>
using namespace muduo::net;

EventLoop* g_loop = NULL;

int main(int argc, char* argv[])
{
  muduo::Logger::setLogLevel(muduo::Logger::LogLevel::TRACE);
  EventLoop loop;
  g_loop = &loop;
  int timerfd=timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
  muduo::net::Channel channel(&loop,timerfd);
  channel.setReadCallback([&](){g_loop->quit();});
  channel.enableReading();
  struct itimerspec howlong;
  bzero(&howlong,sizeof howlong);
  howlong.it_value.tv_sec=5;
  timerfd_settime(timerfd,0,&howlong,NULL);

  // muduo::Thread t([&](){g_loop->loop();});
  // t.start();
  // t.join();
  g_loop->loop();
  close(timerfd);
}
