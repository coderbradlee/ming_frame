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
typedef std::set<muduo::string> ConnectionSubscription;
parse_result parse_message(
  muduo::net::Buffer* buf,
  muduo::string* cmd,
  muduo::string* topics,
  muduo::string* content)
{
  parse_result result=k_error;
  const char* crlf=buf->findCRLF();
  if(crlf)
  {
    const char* space=std::find(buf->peek(),crlf,' ');
    if(space!=crlf)
    {
      cmd->assign(buf->peek(),space);
      topics->assign(space+1,crlf);
      if(*cmd=="pub")
      {
        const char* start=crlf+2;
        crlf=buf->findCRLF(start);
        if(crlf)
        {
          content->assign(start,crlf);
          buf->retrieveUntil(crlf+2);
          result=k_success;
        }
        else
        {
          result=k_continue;
        }
      }
      else
      {
        buf->retrieveUntil(crlf+2);
        result=k_success;
      }
    }
    else
    {
      result=k_error;
    }
  }
  else
  {
    result=k_continue;
  }
  return result;
}
pubsubclient::pubsubclient(EventLoop* loop,const InetAddress& addr,const string&name):m_client(loop,addr,name)
{
  m_client.setConnectionCallback(boost::bind(&pubsubclient::on_connection,this,_1));
  m_client.setMessageCallback(boost::bind(&pubsubclient::on_message,this,_1,_2,_3));
}
void pubsubclient::start()
{
  m_client.connect();
}
void pubsubclient::stop()
{
  m_client.disconnect();
}
bool pubsubclient::connected()const
{
  return m_conn&&m_conn->connected();
}
bool pubsubclient::subscribe(const string& topic,const subscribe_callback& cb)
{
  string message="sub "+topic+"\r\n";
  m_subscribe_callback=cb;
  return send(message);
}
void pubsubclient::unsubscribe(const string& topic)
{
  string message="unsub "+topic+"\r\n";
  send(message);
}
bool pubsubclient::publish(const string& topic,const string& content)
{
  string message="pub "+topic+"\r\n"+content+"\r\n";
  return send(message);
}
void pubsubclient::on_connection(const TcpConnectionPtr& conn)
{
  if(conn->connected())
  {
    m_conn=conn;
  }
  else
  {
    m_conn.reset();
  }
  if(m_connection_callback)
  {
    m_connection_callback(this);
  }

}
void pubsubclient::on_message(const TcpConnectionPtr& conn,Buffer* buf,Timestamp receive)
{
  parse_result result=k_success;
  while(result==k_success)
  {
    string cmd;
    string topic;
    string content;
    result=parse_message(buf,&cmd,&topic,&content);
    if(result==k_success)
    {
      if(cmd=="pub"&&m_subscribe_callback)
      {
        m_subscribe_callback(topic,content,receive);
      }

    }
    else if(result==k_error)
    {
      conn->shutdown();
    }

  }
}
bool pubsubclient::send(const string& message)
{
  bool succeed=false;
  if(m_conn&&m_conn->connected())
  {
    m_conn->send(message);
    succeed=true;
  }
  return succeed;
}