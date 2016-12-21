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

const std::string kPath = "/sudoku/";

void onRequest(const TcpConnectionPtr& conn,
               FastCgiCodec::ParamMap& params,
               Buffer* in);

void onConnection(const TcpConnectionPtr& conn);
void parser_param(
	const std::string& uri,
  const std::string& query_string,
  const std::string& content,
  const TcpConnectionPtr& conn);
void start_fastcgi();

class request_parser_base:boost::noncopyable
{
public:
	request_parser_base(const std::string& query_string,const std::string& content);
	virtual std::string get_result()=0;
	virtual ~request_parser_base(){}
protected:
	std::map<std::string,std::string> m_query_string;
	std::string m_content;
};
class request_parser_get:public request_parser_base
{
public:
	request_parser_get(const std::string& query_string,const std::string& content);
	std::string get_result();
};
class get_rate
{
public:
	get_rate(const std::string& src,const std::string& des,const std::string& time,boost::shared_ptr<mysql_connect> m_);
	std::string get_rates();
private:
	std::string get_currency_id(const std::string& code);
	std::string get_rate_from_myql(const std::string& exchange_rate_id,const std::string& which_day);
	std::string get_exchange_rate_id(const std::string& source,const std::string& target);
	
	std::string m_src;
	std::string m_des;
	std::string m_time;
	boost::shared_ptr<mysql_connect> m_conn;
};
#endif  