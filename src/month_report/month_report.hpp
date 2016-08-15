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
 	muduo::string quotation_id;
 	muduo::string quotation_detail_id;
 	muduo::string quotation_no;
 	muduo::string sales_full_name;
 	muduo::string sales_type;
 	muduo::string account_name;
 	muduo::string country_region;
 	muduo::string customer_countries;
 	muduo::string receiving_countries;
 	muduo::string product_classification;
 	muduo::string product_name;
 	double product_qty_pc;
 	double product_qty_w;
 	muduo::string price_condition;
 	muduo::string currency;
 	double unit_price;
 	muduo::string price_total_currency;
 	muduo::string price_total;
 	muduo::string guided_currency;
 	muduo::string price_total_guided;
 	muduo::string payment_term_desc;
 	muduo::string creat_at;
 	void print()
 	{
 		std::cout<<quotation_id<<":"quotation_detail_id<<":"<<quotation_no<<":"<<sales_full_name<<":"
			<<":"<<sales_type<<":"
 			<<":"<<account_name<<":"
			<<":"<<country_region<<":"
			<<":"<<customer_countries<<":"
 			<<":"<<receiving_countries<<":"
 			<<":"<<product_classification<<":"
			<<":"<<product_name<<":"
 			<<":"<<product_qty_pc<<":"
			<<":"<<product_qty_w<<":"
			<<":"<<price_condition<<":"
 			<<":"<<currency<<":"
 			<<":"<<unit_price<<":"
			<<":"<<price_total_currency<<":"
 			<<":"<<price_total<<":"
			<<":"<<guided_currency<<":"
			<<":"<<price_total_guided<<":"
 			<<":"<<payment_term_desc<<":"
 			<<":"<<creat_at<<":"
 			<<std::endl;
 	}
 }; 
struct mysql_info_
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
	month_report(boost::shared_ptr<mysql_info_> in);
	void start();
private:
	void query(const std::string& sql);
	boost::shared_ptr<sql::ResultSet> get_res()const;
private:
	std::vector<boost::shared_ptr<report_data>> m_report_datas;
	boost::shared_ptr<sql::ResultSet> m_res;
	boost::shared_ptr<sql::Statement> m_stmt;
	boost::shared_ptr<sql::PreparedStatement> m_pstmt;
	boost::shared_ptr<sql::Driver> m_drivers;
	boost::shared_ptr<sql::Connection> m_con;

	sql::Driver* m_driver;
};

void start_report();

#endif