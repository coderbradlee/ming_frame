#ifndef FASTCGI_RESOURCE_H
#define FASTCGI_RESOURCE_H

#include "fastcgi.h"
#include "../sudoku/sudoku.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>
#include "../log.hpp"
#include "../mysql_connect.hpp"
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

class request_parser_base:boost::noncopyable
{
public:
	request_parser_base(const string& query_string,const string& content);
	virtual string get_result()=0;
	virtual ~request_parser_base(){}
protected:
	std::map<string,string> m_query_string;
	string m_content;
};
class request_parser_get:public request_parser_base
{
public:
	request_parser_get(const string& query_string,const string& content);
	string get_result();
};
#endif  