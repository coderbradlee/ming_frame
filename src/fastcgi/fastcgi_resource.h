#ifndef FASTCGI_RESOURCE_H
#define FASTCGI_RESOURCE_H

#include "fastcgi.h"
#include "../sudoku/sudoku.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>
#include "../log.hpp"
using namespace muduo::net;

const muduo::string kPath = "/sudoku/";

void onRequest(const TcpConnectionPtr& conn,
               FastCgiCodec::ParamMap& params,
               Buffer* in);

void onConnection(const TcpConnectionPtr& conn);
void parser_param(
	const muduo::string& uri,
  const muduo::string& query_string,
  const muduo::string& content,
  const TcpConnectionPtr& conn);
void start_fastcgi();
class request_parser:public boost::noncopyable
{
private:

};

#endif  