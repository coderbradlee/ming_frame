#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <stdio.h>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/Connector.h>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <stdio.h>
#include <sstream>
using namespace muduo::net;

EventLoop* g_loop = NULL;
void onConnect(int sockfd)
{
	printf("connected\n");
	g_loop->quit();
}
int main(int argc, char* argv[])
{
  muduo::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
  EventLoop loop;
  g_loop = &loop;
  muduo::net::InetAddress addr("127.0.0.1",32769);
  // for(int i=0;i<10000;++i)
  // {
  	  muduo::net::Connector* conn(new muduo::net::Connector(&loop,addr));
	  conn->setNewConnectionCallback(onConnect);
	  conn->start();
  
  
  loop.loop();
  //}
  
}
