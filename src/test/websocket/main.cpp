#include "websocketServer.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
int main()
{
	LOG_INFO<<"pid="<<getpid();
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(8000);
	websocketServer server(&loop,listenAddr);
	server.start();
	loop.loop();
}