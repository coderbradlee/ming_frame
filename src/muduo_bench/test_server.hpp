#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <muduo/net/TcpServer.h>

class DiscardServer
{
public:
  DiscardServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr):server_(loop,listenAddr,"discardServer")
  {
  	server_.setConnectionCallback(
      boost::bind(&DiscardServer::onConnection, this, _1));
    server_.setMessageCallback(
      boost::bind(&DiscardServer::onMessage, this, _1, _2, _3));
  }
  void start()
  {
  	server_.start();
  }
private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn)
	{
		LOG_INFO<<"DiscardServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
	}

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time)
    {
    	string msg(buf->retrieveAllAsString());
    	LOG_INFO<<conn->name()<<" discards "<<msg.length()<<" "<<msg;
    }

  muduo::net::TcpServer server_;
};
class DaytimeServer
{
public:
  DaytimeServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr):server_(loop,listenAddr,"DaytimeServer")
  {
  	server_.setConnectionCallback(
      boost::bind(&DaytimeServer::onConnection, this, _1));
    server_.setMessageCallback(
      boost::bind(&DaytimeServer::onMessage, this, _1, _2, _3));
  }
  void start()
  {
  	server_.start();
  }
private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn)
	{
		LOG_INFO<<"DaytimeServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
        if(conn->connected())
        {
        	conn->send(Timestamp::now().toFormattedString()+"\n");
        	conn->shutdown();
        }
	}

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time)
    {
    	string msg(buf->retrieveAllAsString());
    	LOG_INFO<<conn->name()<<" "<<msg.length()<<" "<<msg;
    }

  muduo::net::TcpServer server_;
};
class EchoServer
{
public:
  EchoServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr):server_(loop,listenAddr,"EchoServer")
  {
  	server_.setConnectionCallback(
      boost::bind(&EchoServer::onConnection, this, _1));
    server_.setMessageCallback(
      boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
  }
  void start()
  {
  	server_.start();
  }
private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn)
	{
		LOG_INFO<<"EchoServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
        
	}

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time)
    {
    	string msg(buf->retrieveAllAsString());
    	LOG_INFO<<conn->name()<<" "<<msg.length()<<" "<<msg;
    	if(conn->connected())
        {
        	conn->send(msg);
        }
    }

  muduo::net::TcpServer server_;
};
// RFC 868
class TimeServer
{
 public:
  TimeServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);

  void start();

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

  muduo::net::TcpServer server_;
};

#endif  // MUDUO_EXAMPLES_SIMPLE_TIME_TIME_H
