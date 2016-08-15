#ifndef MONTH_REPORT_HPP
#define	MONTH_REPORT_HPP
#include "mysql_connection.h"
#include "../config.hpp"
#include "../mysql_connect.hpp"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../log.hpp"
struct report_data
 {
 	std::string ip;
 	std::string port;
 	std::string username;
 	std::string password;
 	std::string database;
 }; 

class month_report
{
public:
	month_report(boost::shared_ptr<mysql_connect> in,boost::shared_ptr<report_data> rd);
	void start();
private:
	boost::shared_ptr<mysql_connect> m_mysql_connect;
	boost::shared_ptr<report_data> m_report_data;
};

void start_report();

#endif