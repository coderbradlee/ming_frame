#ifndef TEST_HUB_HPP
#define TEST_HUB_HPP

#include <muduo/base/Types.h>
#include <muduo/net/Buffer.h>
#include <boost/noncopyable.hpp>
enum parse_result
{
   k_error,k_success,k_continue
};
parse_result parse_message(muduo::net::Buffer* buf,muduo::string* cmd,muduo::string* topic,muduo::string* content);
class topic:public muduo::copyable
{
public:
  topic(const muduo::string& topic);
  void add(const muduo::net::TcpConnectionPtr& conn);
  void remove(const muduo::net::TcpConnectionPtr& conn);
  void publish(const muduo::string& content,Timestamp time);
private:
  muduo::string make_message();
private:
  muduo::string m_topic;
  muduo::string m_content;
  Timestamp m_last_pubtime;
  std::set<muduo::net::TcpConnectionPtr> m_audiences;
};
class hub:boost::noncopyable
{
public:
  hub(muduo::net::EventLoop* loop,const muduo::net::InetAddress& addr);
  void start();
private:
  void on_connection(const muduo::net::TcpConnectionPtr& conn);
  void on_message(const muduo::net::TcpConnectionPtr&conn,muduo::net::Buffer* buf,Timestamp receive_time);
  void time_publish();
  void subscribe(const muduo::net::TcpConnectionPtr& conn,const muduo::string& topic);
  void unsubscribe(const muduo::net::TcpConnectionPtr&conn,const muduo::string& topic);
  void publish(const muduo::string& source,const muduo::string& topic,const muduo::string& content,Timestamp time);
  topic& get_topic(const muduo::string& topic);
private:
  EventLoop* m_loop;
  TcpServer m_server;
  std::map<muduo::string,topic> m_topics;
};
#endif
