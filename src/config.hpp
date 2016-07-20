#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
//#define DEBUG
#include "include.hpp"

//using std::string;
class iconfig:boost::noncopyable
{
	public:
		static boost::shared_ptr<iconfig> get_instance(const std::string& filename);
	private:
		iconfig(const std::string& filename);
		
	public:
		boost::property_tree::ptree m_pt;
		std::string m_mysql_ip;
		unsigned short m_mysql_port;
		std::string m_mysql_username;
		std::string m_mysql_password;
		std::string m_mysql_database;
		///////////////////
		std::string m_mysql_eu_ip;
		unsigned short m_mysql_eu_port;
		std::string m_mysql_eu_username;
		std::string m_mysql_eu_password;
		std::string m_mysql_eu_database;
		//////////////////
		std::string m_mysql_js_ip;
		unsigned short m_mysql_js_port;
		std::string m_mysql_js_username;
		std::string m_mysql_js_password;
		std::string m_mysql_js_database;
		//////////////////
		std::string m_mysql_as_ip;
		unsigned short m_mysql_as_port;
		std::string m_mysql_as_username;
		std::string m_mysql_as_password;
		std::string m_mysql_as_database;
		//////////////////////////
		std::string m_mysql_table;
		std::string m_mysql_table2;
		int m_threads;
		int m_port;
		std::string m_url;
		std::string m_orderbot_username;
		std::string m_orderbot_password;
		std::string m_orderbot_url;	
		std::string m_activemq_username;
		std::string m_activemq_password;
		std::string m_activemq_url;
		std::string m_activemq_read_queue;
		std::string m_activemq_write_queue;	
		std::string m_activemq_write_product_queue;	
		size_t m_write_product_interval;
		std::string m_activemq_read_order_queue;	
		std::string m_activemq_write_order_queue;	
		std::string m_exchange_rate_url;	
		size_t m_exchange_rate_request_interval;	
		std::string m_exchange_rate_key;
		std::string m_exchange_rate_write_rate_queue;
		std::string m_exchange_rate_insert_time;
		std::string m_exchange_rate_username;
		std::string m_exchange_rate_password;
		static boost::mutex m_mu;	
		//static boost::shared_ptr<iconfig> volatile m_ps;
		static boost::shared_ptr<iconfig> m_ps;
		std::string m_log_name;
		std::string m_log_level;
		std::string m_log_console_level;
		size_t m_log_size;
		size_t m_log_numbers;
};
// boost::shared_ptr<iconfig> iconfig::m_ps = nullptr;
// boost::mutex iconfig::m_mu;
 extern boost::shared_ptr<iconfig> get_config;// = iconfig::get_instance("config.ini");
//#define get_config (iconfig::get_instance("config.ini"));
//boost::shared_ptr<iconfig> get_config = iconfig::get_instance("config.ini");
#endif

