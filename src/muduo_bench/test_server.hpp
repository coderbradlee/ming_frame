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
class ChargenServer
{
 public:
  ChargenServer(muduo::net::EventLoop* loop,
                const muduo::net::InetAddress& listenAddr,
                bool print = false): server_(loop, listenAddr, "ChargenServer"),
    transferred_(0),
    startTime_(Timestamp::now())
{
  server_.setConnectionCallback(
      boost::bind(&ChargenServer::onConnection, this, _1));
  server_.setMessageCallback(
      boost::bind(&ChargenServer::onMessage, this, _1, _2, _3));
  server_.setWriteCompleteCallback(
      boost::bind(&ChargenServer::onWriteComplete, this, _1));
  if (print)
  {
    loop->runEvery(3.0, boost::bind(&ChargenServer::printThroughput, this));
  }

  string line;
  for (int i = 33; i < 127; ++i)
  {
    line.push_back(char(i));
  }
  line += line;

  for (size_t i = 0; i < 127-33; ++i)
  {
    message_ += line.substr(i, 72) + '\n';
  }
}

  void start()
  {
  	server_.start();
  }
 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn)
  {
	  LOG_INFO << "ChargenServer - " << conn->peerAddress().toIpPort() << " -> "
	           << conn->localAddress().toIpPort() << " is "
	           << (conn->connected() ? "UP" : "DOWN");
	  if (conn->connected())
	  {
	    conn->setTcpNoDelay(true);
	    conn->send(message_);
	  }
  }
  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time){}

  void onWriteComplete(const muduo::net::TcpConnectionPtr& conn)
  {
	  transferred_ += message_.size();
	  conn->send(message_);
  }
  void printThroughput()
  {
	  Timestamp endTime = Timestamp::now();
	  double time = timeDifference(endTime, startTime_);
	  printf("%4.3f MiB/s\n", static_cast<double>(transferred_)/time/1024/1024);
	  transferred_ = 0;
	  startTime_ = endTime;
  }

  muduo::net::TcpServer server_;

  muduo::string message_;
  int64_t transferred_;
  muduo::Timestamp startTime_;
};
#endif  // MUDUO_EXAMPLES_SIMPLE_TIME_TIME_H
