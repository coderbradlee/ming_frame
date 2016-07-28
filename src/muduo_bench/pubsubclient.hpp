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
  typedef boost::function<void (const string& topic,const string& content,Timestamp)> subscribe_callback;
  pubsubclient(EventLoop* loop,const InetAddress& hub,const string& name);
  void start();
  void stop();
  bool connected()const;
  void set_connection_callback(const connection_callback& cb)
  {
    m_connection_callback=cb;
  }
  bool subscribe(const string& topic,const subscribe_callback& cb);
  void unsubscribe(const string& topic);
  bool publish(const string& topic,const string& content);
private:
  void on_connection(const TcpConnectionPtr& conn);
  void on_message(const TcpConnectionPtr& conn,Buffer* buf,Timestamp receive);
  bool send(const string& message);
private:
  TcpClient m_client;
  TcpConnectionPtr m_conn;
  connection_callback m_connection_callback;
  subscribe_callback m_subscribe_callback;
};
#endif
