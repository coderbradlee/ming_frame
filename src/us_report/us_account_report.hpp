#ifndef US_ACCOUNT_REPORT_HPP
#define	US_ACCOUNT_REPORT_HPP
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
 	std::string customer_basic_id;
 	std::string account_owner;
 	std::string account_name;
 	std::string country;
 	std::string country_id;
 	std::string state_id;
 	std::string city_id;
 	std::string state;
 	std::string city;
 	std::string allocated_time;
 	
 	void print()
 	{
 		std::cout<<customer_basic_id
 			<<","<<account_owner
 			<<","<<account_name
 			<<","<<country
			<<","<<state
 			<<","<<city
			<<","<<allocated_time
 			<<std::endl;
 	}
 	std::string csv_line()
 	{
 		std::ostringstream stream;
			stream<<account_owner
 			<<","<<account_name
 			<<","<<country
			<<","<<state
 			<<","<<city
			<<","<<allocated_time
			<<"\r\n";
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
	void deal_with();
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