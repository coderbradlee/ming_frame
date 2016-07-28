#ifndef TEST_PUBSUBCLIENT_HPP
#define TEST_PUBSUBCLIENT_HPP

#include <muduo/base/Types.h>
#include <muduo/net/Buffer.h>
#include <boost/noncopyable.hpp>

#include <set>
#include <boost/any.hpp>
enum parse_result
{
  k_error,
  k_success,
  k_continue,
};
parse_result parse_message(
  muduo::net::Buffer* buf,
  muduo::string* cmd,
  muduo::string* topics,
  muduo::string* content);
class pubsubclient:boost::noncopyable
{
public:
  typedef boost::function<void(pubsubclient*)> connection_callback;
  typedef boost::function<void (const muduo::string& topic,const muduo::string& content,muduo::Timestamp)> subscribe_callback;
  pubsubclient(muduo::net::EventLoop* loop,const muduo::net::InetAddress& hub,const muduo::string& name);
  void start();
  void stop();
  bool connected()const;
  void set_connection_callback(const connection_callback& cb)
  {
    m_connection_callback=cb;
  }
  bool subscribe(const muduo::string& topic,const subscribe_callback& cb);
  void unsubscribe(const muduo::string& topic);
  bool publish(const muduo::string& topic,const muduo::string& content);
private:
  void on_connection(const TcpConnectionPtr& conn);
  void on_message(const TcpConnectionPtr& conn,muduo::net::Buffer* buf,muduo::Timestamp receive);
  bool send(const muduo::string& message);
private:
  TcpClient m_client;
  TcpConnectionPtr m_conn;
  connection_callback m_connection_callback;
  subscribe_callback m_subscribe_callback;
};
#endif
