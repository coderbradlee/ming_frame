#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <stdio.h>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/Acceptor.h>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <stdio.h>
#include <sstream>
#include <sys/timerfd.h>
#include <muduo/net/Channel.h>
using namespace muduo::net;

void on_new_connnection1(int sockfd,const muduo::net::InetAddress& peerAddr)
{
	 printf("conn1:%s\n", peerAddr.toIpPort().c_str());
   write(sockfd,"to conn1\n",9);
   close(sockfd);
}
void on_new_connnection2(int sockfd,const muduo::net::InetAddress& peerAddr)
{
   printf("conn2:%s\n", peerAddr.toIpPort().c_str());
   write(sockfd,"to conn2\n",9);
   close(sockfd);
}

int main(int argc, char* argv[])
{
  //muduo::Logger::setLogLevel(muduo::Logger::LogLevel::TRACE);
  muduo::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
  printf("main pid=%d\n",getpid() );
  muduo::net::InetAddress lis1(9981);
  muduo::net::InetAddress lis2(9982);
  EventLoop loop;
  muduo::net::Acceptor acc1(&loop,lis1,true);
  muduo::net::Acceptor acc2(&loop,lis2,true);
  acc1.setNewConnectionCallback(on_new_connnection1);
  acc2.setNewConnectionCallback(on_new_connnection2);
  acc1.listen();
  acc2.listen();
  loop.loop();
  // g_loop = &loop;
  // int timerfd=::timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
  // muduo::net::Channel channel(&loop,timerfd);
  // channel.setReadCallback(timeout_func);
  // channel.enableReading();
  // struct itimerspec howlong;
  // bzero(&howlong,sizeof howlong);
  // howlong.it_value.tv_sec=5;
  // ::timerfd_settime(timerfd,0,&howlong,NULL);

  // muduo::Thread t([&](){g_loop->loop();});
  // t.start();
  // t.join();
  // g_loop->loop();
  // ::close(timerfd);
}
