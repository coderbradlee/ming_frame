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
#include "hub.hpp"
using namespace muduo;
using namespace muduo::net;
using muduo::string;



parse_result parse_message(Buffer* buf,string* cmd,string* topics,string* content)
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
          result=k_continue
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
topic::topic(const string& topic):m_topic(topic)
{}
void topic::add(const TcpConnectionPtr& conn)
{
  m_audiences.insert(conn);
  if(m_last_pubtime.valid())
  {
    conn->send(make_message());
  }
}
void topic::remove(const TcpConnectionPtr& conn)
{
  m_audiences.erase(conn);
}
void topic::publish(const string& content,Timestamp time)
{
  m_content=content;
  m_last_pubtime=time;
  string mess=make_message();
  for(auto& i:m_audiences)
  {
    i->send(mess);
  }
}
string topic::make_message()
{
  return "pub "+m_topic+"\r\n"+m_content+"\r\n";
}
hub::hub(muduo::net::EventLoop* loop,const muduo::net::InetAddress& addr):m_loop(loop),m_server(m_loop,addr,"hub server")
{
  m_server.setConnectionCallback(boost::bind(&hub::on_connection,this,_1));
  m_server.setMessageCallback(boost::bind(&hub::on_message,this,_1,_2,_3));
  m_loop->runEvery(1,boost::bind(&hub::time_publish,this));
}
void hub::start()
{
  m_server.start();
}
void hub::on_connection(const TcpConnectionPtr& conn)
{
  if(conn->connected())
  {
    conn->setContext(ConnectionSubscription());
  }
  else
  {
    const ConnectionSubscription& conn_sub=boost::any_cast<const ConnectionSubscription&>(conn->getContext());
    for(auto& i:conn_sub)
    {
      unsubscribe(conn,i);
    }
  }
}
void hub::on_message(const TcpConnectionPtr& conn,Buffer* buf,Timestamp receive_time)
{
  parse_result result=k_success;
  while(result==k_success)
  {
    string cmd;
    string topics;
    string content;
    result=parse_result(buf,&cmd,&topic,&content);
    if(result==k_success)
    {
      if(cmd=="pub")
      {
        publish(conn->name(),topics,content,receive_time);
      }
      else if(cmd=="sub")
      {
        subscribe(conn,topics);
      }
      else if(cmd=="unsub")
      {
        unsubscribe(conn,topics);
      }
      else
      {
        conn->shutdown();
        result=k_error;
      }

    }
    else if(result==k_error)
    {
      conn->shutdown();
    }

  }
}
void hub::time_publish()
{
  Timestamp now=Timestamp::now();
  publish("internal","utc_time",now.toFormattedString(),now);
}
void hub::subscribe(const TcpConnectionPtr& conn,const string& topics)
{
  ConnectionSubscription* conn_sub=boost::any_cast<ConnectionSubscription>(conn->getMutableContext());
  conn_sub->insert(topics);
  get_topic(topics).add(conn);
}
void hub::unsubscribe(const TcpConnectionPtr& conn,const string& topics)
{
  LOG_INFO << conn->name() << " unsubscribes " << topics;
    get_topic(topics).remove(conn);
    // topic could be the one to be destroyed, so don't use it after erasing.
    ConnectionSubscription* connSub
      = boost::any_cast<ConnectionSubscription>(conn->getMutableContext());
    connSub->erase(topics);
}
void hub::publish(const string&,const string& topics,const string& content,Timestamp time)
{
  get_topic(topics).publish(content,time);
}
topic& hub::get_topic(const string& to)
{
  auto it=m_topics.find(to);
  if(it==m_topics.end())
  {
    it=m_topics.insert(make_pair(to,topic(to))).first; 
  }
  return it->second;
}
int main()
{
  EventLoop loop;
  hub server(&loop,InetAddress(12345));
  server.start();
  loop.loop();
}