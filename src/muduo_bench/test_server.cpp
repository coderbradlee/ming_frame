#include <muduo/net/TcpServer.h>

#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>

#include <utility>

#include <mcheck.h>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

#include "test_server.hpp"
int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid();
  EventLoop loop;  // one loop shared by multiple servers

  // ChargenServer chargenServer(&loop, InetAddress(2019));
  // chargenServer.start();

  DaytimeServer daytimeServer(&loop, InetAddress(2013));
  daytimeServer.start();

  DiscardServer discardServer(&loop, InetAddress(2009));
  discardServer.start();

  EchoServer echoServer(&loop, InetAddress(2007));
  echoServer.start();

  // TimeServer timeServer(&loop, InetAddress(2037));
  // timeServer.start();

  loop.loop();
}
