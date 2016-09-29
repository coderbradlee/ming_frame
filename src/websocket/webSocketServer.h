
#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <muduo/net/TcpServer.h>
#include <boost/noncopyable.hpp>

namespace muduo
{
namespace net
{

class webSocketRequest;
class webSocketResponse;

class webSocketServer : boost::noncopyable
{
 public:
  typedef boost::function<void (const webSocketRequest&,
                                webSocketResponse*)> webSocketOpenCallback;
  typedef boost::function<void (const webSocketRequest&,
                                webSocketResponse*)> webSocketMessageCallback;
  typedef boost::function<void (const webSocketRequest&,
                                webSocketResponse*)> webSocketErrorCallback;
  typedef boost::function<void (const webSocketRequest&,
                                webSocketResponse*)> webSocketCloseCallback;
  webSocketServer(EventLoop* loop,
             const InetAddress& listenAddr,
             const string& name,
             TcpServer::Option option = TcpServer::kNoReusePort);

  ~webSocketServer();  // force out-line dtor, for scoped_ptr members.

  EventLoop* getLoop() const { return server_.getLoop(); }

  /// Not thread safe, callback be registered before calling start().
  void setwebSocketOpenCallback(const webSocketOpenCallback& cb)
  {
    webSocketOpenCallback_ = cb;
  }
  void setwebSocketMessageCallback(const webSocketMessageCallback& cb)
  {
    webSocketMessageCallback_ = cb;
  }
  void setwebSocketErrorCallback(const webSocketErrorCallback& cb)
  {
    webSocketErrorCallback_ = cb;
  }
  void setwebSocketCloseCallback(const webSocketCloseCallback& cb)
  {
    webSocketCloseCallback_ = cb;
  }
  void setThreadNum(int numThreads)
  {
    server_.setThreadNum(numThreads);
  }

  void start();

 private:
  void onConnection(const TcpConnectionPtr& conn);
  void onMessage(const TcpConnectionPtr& conn,
                 Buffer* buf,
                 Timestamp receiveTime);
  void onOpen(const TcpConnectionPtr&, const webSocketRequest&);
  void onMessage(const TcpConnectionPtr&, const webSocketRequest&);
  void onError(const TcpConnectionPtr&, const webSocketRequest&);
  void onClose(const TcpConnectionPtr&, const webSocketRequest&);
  TcpServer server_;
  webSocketOpenCallback webSocketOpenCallback_;
  webSocketMessageCallback webSocketMessageCallback_;
  webSocketErrorCallback webSocketErrorCallback_;
  webSocketCloseCallback webSocketCloseCallback_;
};

}
}

#endif  // MUDUO_NET_HTTP_HTTPSERVER_H
