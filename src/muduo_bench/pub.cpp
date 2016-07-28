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
#include "pubsubclient.hpp"
using namespace muduo;
using namespace muduo::net;
using muduo::string;
EventLoop* g_loop=NULL;
string g_topic="mytopic";
string g_content("my content");
void on_connection(pubsubclient* client)
{
  if(client->connected())
  {
    client->publish(g_topic,g_content);
    client->stop();
  }
  else
  {
    g_loop->quit();
  }
}
int main()
{
  string name=ProcessInfo::username()+"@"+ProcessInfo::hostname()+":"+ProcessInfo::pidString();

  EventLoop loop;
  g_loop=&loop;

  pubsubclient client(g_loop,InetAddress("127.0.0.1",12345),name);
  client.set_connection_callback(on_connection);
  client.start();
  loop.loop();
}