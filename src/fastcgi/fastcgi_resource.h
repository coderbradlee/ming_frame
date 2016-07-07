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

const string kPath = "/sudoku/";

void onRequest(const TcpConnectionPtr& conn,
               FastCgiCodec::ParamMap& params,
               Buffer* in);

void onConnection(const TcpConnectionPtr& conn);

void start_fastcgi();


#endif  