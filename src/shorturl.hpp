#ifndef SHORTURL_HPP
#define SHORTURL_HPP

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThreadPool.h>
#include <muduo/base/Logging.h>

#include <map>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <sys/socket.h>  // SO_REUSEPORT

//using namespace muduo;
using namespace muduo::net;
namespace short_url
{
  void onRequest(const HttpRequest& req, HttpResponse* resp);

  int test();

}
#endif