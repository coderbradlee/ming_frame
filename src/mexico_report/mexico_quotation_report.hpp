#ifndef MEXICO_QUOTATION_REPORT_HPP
#define	MEXICO_QUOTATION_REPORT_HPP
#include "mysql_connection.h"
#include "../config.hpp"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../log.hpp"
#include <iomanip>
struct report_data
 {
 	std::string quotation_id;
 	std::string quotation_detail_id;
 	std::string country_id;
 	std::string country;
 	std::string receiving_countries;
 	std::string owner_sales_sys_account_id;
 	std::string sales_employee_id;
 	std::string sales_company_name;
	std::string sales_full_name;
	std::string account_name;
 	std::string quotation_no;
 	std::string approval_status;
 	std::string product_name;
 	double product_qty_pc;
 	double product_qty_w;
 	std::string price_condition;
	std::string currency;
	double unit_price;
	std::string price_total_currency;
	double price_total;
	std::string creat_at;
 	std::string pi_no;
 	std::string payment_term_desc;
 	void print()
 	{
 		std::cout<<std::setprecision(8)<<quotation_id
 		<<","<<quotation_detail_id<<","<<sales_full_name<<","<<sales_company_name<<","<<account_name<<","<<quotation_no<<","<<approval_status<<","<<product_name<<","<<product_qty_pc<<","<<product_qty_w<<","<<price_condition<<","<<currency<<","<<unit_price<<","<<price_total_currency<<","<<price_total<<","<<payment_term_desc<<","<<creat_at
 			<<std::endl;
 	}
 	std::string csv_line()
 	{
 		std::ostringstream stream;
		stream<<std::setprecision(8)<<quotation_no<<","<<sales_full_name<<","<<account_name<<","<<country<<","<<receiving_countries<<","<<receiving_countries<<","<<pi_no<<","<<product_qty_pc<<","<<product_qty_w<<","<<price_condition<<","<<currency<<","<<unit_price<<","<<price_total_currency<<","<<price_total<<","<<payment_term_desc<<","<<creat_at<<"\r\n";
 		return stream.str();
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
	void insert_data();
	void deal_with_sales_info();
	void deal_with_customer_info();
	void deal_with_currency_info();
	void deal_with_payment_method_info();
	void deal_with_product_info();
	void deal_with_trade_term_info();
	void deal_with_sales_country();
	void deal_with_approved_status();
	void deal_with_pi();
	void write_to_csv();
private:
	std::vector<boost::shared_ptr<report_data>> m_report_datas;
	boost::shared_ptr<sql::ResultSet> m_res;
	boost::shared_ptr<sql::Statement> m_stmt;
	boost::shared_ptr<sql::PreparedStatement> m_pstmt;
	boost::shared_ptr<sql::Driver> m_drivers;
	boost::shared_ptr<sql::Connection> m_con;

	sql::Driver* m_driver;
};
class write_csv
{
public:
	write_csv(std::string filename)
	{
		setFilename(filename);
		m_fp = std::ofstream(filename);
	}
	void close()
	{
		m_fp.close();
	}
	~write_csv()
	{
		m_fp.close();
	}
	void addData(std::string data)
	{
		m_fp.write(data.c_str(), data.length());
	}
private:
	void setFilename(std::string filename)
	{
		m_filename = filename;
	}
	
private:
		std::string m_filename;
		std::ofstream m_fp;
};
void start_report();

#endif