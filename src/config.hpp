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
		
		int m_threads;
		int m_port;
		int m_ports;
		std::string m_url;
		std::string m_nfs_path;
		static boost::mutex m_mu;	
		//static boost::shared_ptr<iconfig> volatile m_ps;
		static boost::shared_ptr<iconfig> m_ps;
		std::string m_log_name;
		std::string m_log_level;
		int m_log_size;
};
// boost::shared_ptr<iconfig> iconfig::m_ps = nullptr;
// boost::mutex iconfig::m_mu;
 extern boost::shared_ptr<iconfig> get_config;// = iconfig::get_instance("config.ini");
//#define get_config (iconfig::get_instance("config.ini"));
//boost::shared_ptr<iconfig> get_config = iconfig::get_instance("config.ini");
#endif

