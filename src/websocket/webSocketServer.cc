// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

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
    webSocketCallback_(detail::defaultwebSocketCallback)
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
  webSocketContext* context = boost::any_cast<webSocketContext>(conn->getMutableContext());

  if (!context->parseRequest(buf, receiveTime))
  {
    conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
    conn->shutdown();
  }

  if (context->gotAll())
  {
    onRequest(conn, context->request());
    context->reset();
  }
}

void webSocketServer::onRequest(const TcpConnectionPtr& conn, const webSocketRequest& req)
{
  const string& connection = req.getHeader("Connection");
  bool close = connection == "close" ||
    (req.getVersion() == webSocketRequest::kHttp10 && connection != "Keep-Alive");
  webSocketResponse response(close);
  webSocketCallback_(req, &response);
  Buffer buf;
  response.appendToBuffer(&buf);
  conn->send(&buf);
  if (response.closeConnection())
  {
    conn->shutdown();
  }
}

