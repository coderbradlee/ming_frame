#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
//#define DEBUG
#include "include.hpp"
using std::string;
class iconfig:public boost::enable_shared_from_this<iconfig>, boost::noncopyable
{
	public:
		static boost::shared_ptr<iconfig> get_instance(const std::string& filename);
	private:
		iconfig(const std::string& filename);
		
	public:
		boost::property_tree::ptree m_pt;
		string m_mysql_ip;
		unsigned short m_mysql_port;
		string m_mysql_username;
		string m_mysql_password;
		string m_mysql_database;
		///////////////////
		string m_mysql_eu_ip;
		unsigned short m_mysql_eu_port;
		string m_mysql_eu_username;
		string m_mysql_eu_password;
		string m_mysql_eu_database;
		//////////////////
		string m_mysql_js_ip;
		unsigned short m_mysql_js_port;
		string m_mysql_js_username;
		string m_mysql_js_password;
		string m_mysql_js_database;
		//////////////////////////
		string m_mysql_table;
		string m_mysql_table2;
		size_t m_threads;
		size_t m_port;
		string m_orderbot_username;
		string m_orderbot_password;
		string m_orderbot_url;	
		string m_activemq_username;
		string m_activemq_password;
		string m_activemq_url;
		string m_activemq_read_queue;
		string m_activemq_write_queue;	
		string m_activemq_write_product_queue;	
		size_t m_write_product_interval;
		string m_activemq_read_order_queue;	
		string m_activemq_write_order_queue;	
		string m_exchange_rate_url;	
		size_t m_exchange_rate_request_interval;	
		string m_exchange_rate_key;
		string m_exchange_rate_write_rate_queue;
		static boost::mutex m_mu;	
		static boost::shared_ptr<iconfig> m_ps;
		string m_log_name;
		string m_log_level;
		string m_log_console_level;
		size_t m_log_size;
		size_t m_log_numbers;
};
// boost::shared_ptr<iconfig> iconfig::m_ps = nullptr;
// boost::mutex iconfig::m_mu;
 extern boost::shared_ptr<iconfig> get_config;// = iconfig::get_instance("config.ini");
//#define get_config (iconfig::get_instance("config.ini"));
//boost::shared_ptr<iconfig> get_config = iconfig::get_instance("config.ini");
#endif

