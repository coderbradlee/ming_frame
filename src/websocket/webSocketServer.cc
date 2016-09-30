#include "webSocketServer.h"

#include <muduo/base/Logging.h>
#include "webSocketContext.h"
#include "webSocketRequest.h"
#include "webSocketResponse.h"

#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;

namespace muduo
{
namespace net
{
namespace detail
{

void defaultwebSocketCallback(const webSocketRequest&, webSocketResponse* resp)
{
  resp->setStatusCode(webSocketResponse::k404NotFound);
  resp->setStatusMessage("Not Found");
  resp->setCloseConnection(true);
}

}
}
}

webSocketServer::webSocketServer(EventLoop* loop,
                       const InetAddress& listenAddr,
                       const string& name,
                       TcpServer::Option option)
  : server_(loop, listenAddr, name, option),
    webSocketOpenCallback_(detail::defaultwebSocketCallback)
{
  server_.setConnectionCallback(
      boost::bind(&webSocketServer::onConnection, this, _1));
  server_.setMessageCallback(
      boost::bind(&webSocketServer::onMessage, this, _1, _2, _3));
}

webSocketServer::~webSocketServer()
{
}

void webSocketServer::start()
{
  LOG_WARN << "webSocketServer[" << server_.name()
    << "] starts listenning on " << server_.ipPort();
  server_.start();
}

void webSocketServer::onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    conn->setContext(webSocketContext());
  }
  
}

void webSocketServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           Timestamp receiveTime)
{
  //增加状态机，open message error close
  webSocketContext* context = boost::any_cast<webSocketContext>(conn->getMutableContext());
  if(context->getMessageState()==webSocketContext::kOpen)
  {
    if (!context->parseOpen(buf, receiveTime))
    {
      conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
      conn->shutdown();
    }

    if (context->gotAll())
    {
      onOpen(conn, context->request());
      context->reset();
    }
  }
  else if(context->getMessageState()==webSocketContext::kMessage)
  {
    std::cout <<":"<< __LINE__<<":" <<__FILE__ << std::endl;
    if (!context->parseMessage(buf, receiveTime))
    {
      conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
      conn->shutdown();
    }
    if (context->gotAll())
    {
      onMessage(conn, context->request());
      context->reset();
    }
  }
  
}

void webSocketServer::onOpen(const TcpConnectionPtr& conn, const webSocketRequest& req)
{
  const string& connection = req.getHeader("Connection");
  bool close = connection == "close" ||
    (req.getVersion() == webSocketRequest::kHttp10 && connection != "Keep-Alive");
  webSocketResponse response(close);
  webSocketOpenCallback_(req, &response);
  Buffer buf;
  response.appendToBuffer(&buf);
  conn->send(&buf);
  if (response.closeConnection())
  {
    conn->shutdown();
  }
  else
  {
    webSocketContext* context = boost::any_cast<webSocketContext>(conn->getMutableContext());
    context->setMessageState(webSocketContext::kMessage);
  }
}
void webSocketServer::onMessage(const TcpConnectionPtr& conn, const webSocketRequest& req)
{

  webSocketResponse response(close);
  webSocketMessageCallback_(req, &response);
  Buffer buf;
  response.appendToBuffer(&buf);
  conn->send(&buf);
  if (response.closeConnection())
  {
    conn->shutdown();
  }
  else
  {
    webSocketContext* context = boost::any_cast<webSocketContext>(conn->getMutableContext());
    context->setMessageState(webSocketContext::kMessage);
  }
}
