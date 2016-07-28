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
std::vector<string> g_topics;
void subscription(const string& topic,const string& content,Timestamp)
{
  printf("%s:%s\n",topic.c_str(),content.c_str() );
}
void on_connection(pubsubclient* client)
{
  if(client->connected())
  {
    for(auto& i:g_topics)
    {
      client->subscribe(i,subscription);
    }
  }
  else
  {
    g_loop->quit();
  }
}
int main()
{
  string name=ProcessInfo::username()+"@"+ProcessInfo::hostname()+":"+ProcessInfo::pidString();
  g_topics.push_back("mytopic");
  EventLoop loop;
  g_loop=&loop;

  pubsubclient client(g_loop,InetAddress("127.0.0.1",12345),name);
  client.set_connection_callback(on_connection);
  client.start();
  loop.loop();
}