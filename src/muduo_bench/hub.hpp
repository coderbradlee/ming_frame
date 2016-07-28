#ifndef TEST_HUB_HPP
#define TEST_HUB_HPP

#include <muduo/base/Types.h>
#include <muduo/net/Buffer.h>
#include <boost/noncopyable.hpp>
enum parse_result
{
   k_error,k_success,k_continue
};
parse_result parse_message(muduo::net::Buffer* buf,string* cmd,string* topic,string* content);
class topic:public muduo::copyable
{
public:
  topic(const string& topic);
  void add(const TcpConnectionPtr& conn);
  void remove(const TcpConnectionPtr& conn);
  void publish(const string& content,Timestamp time);
private:
  string make_message();
private:
  string m_topic;
  string m_content;
  Timestamp m_last_pubtime;
  std::set<TcpConnectionPtr> m_audiences;
};
class hub:boost::noncopyable
{
public:
  hub(muduo::net::EventLoop* loop,const muduo::net::InetAddress& addr);
  void start();
private:
  void on_connection(const TcpConnectionPtr& conn);
  void on_message(const TcpConnectionPtr&conn,muduo::net::Buffer* buf,Timestamp receive_time);
  void time_publish();
  void subscribe(const TcpConnectionPtr& conn,const string& topic);
  void unsubscribe(const TcpConnectionPtr&conn,const string& topic);
  void publish(const string& source,const string& topic,const string& content,Timestamp time);
  topic& get_topic(const string& topic);
private:
  EventLoop* m_loop;
  TcpServer m_server;
  std::map<string,topic> m_topics;
};
#endif
