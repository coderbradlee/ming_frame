#ifndef MONTH_REPORT_HPP
#define	MONTH_REPORT_HPP
#include "mysql_connection.h"
#include "../config.hpp"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../log.hpp"
struct report_data
 {
 	muduo::string ip;
 	muduo::string port;
 	muduo::string username;
 	muduo::string password;
 	muduo::string database;
 }; 

class month_report
{
public:
	month_report(boost::shared_ptr<mysql_connect> in,boost::shared_ptr<report_data> rd);
	void start();
private:
	void query(const std::string& sql);
	boost::shared_ptr<sql::ResultSet> get_res()const;
private:
	boost::shared_ptr<mysql_connect> m_mysql_connect;
	boost::shared_ptr<report_data> m_report_data;
	boost::shared_ptr<sql::ResultSet> m_res;
	boost::shared_ptr<sql::Statement> m_stmt;
	boost::shared_ptr<sql::PreparedStatement> m_pstmt;
	boost::shared_ptr<sql::Driver> m_drivers;
	boost::shared_ptr<sql::Connection> m_con;

	sql::Driver* m_driver;
};

void start_report();

#endif