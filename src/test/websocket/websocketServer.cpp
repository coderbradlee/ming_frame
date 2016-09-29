#include "websocketServer.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
websocketServer::websocketServer(muduo::net::EventLoop* loop,const muduo::net::InetAddress& listenAddr):loop_(loop),server_(loop,listenAddr,"websocketServer")
{
	server_.setConnectionCallback(boost::bind(&websocketServer::onConnection,this,_1));
	server_.setMessageCallback(boost::bind(&websocketServer::onMessage,this,_1,_2,_3));
}
void websocketServer::start()
{
	server_.start();
}

void websocketServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	//LOG_INFO<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" is "<<(conn->connected()?"up":"down");
}
void websocketServer::onMessage(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf,muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	//LOG_INFO<<conn->name()<<":"<<msg.size()<<",time:"<<time.toString();
	LOG_INFO<<msg;
}
