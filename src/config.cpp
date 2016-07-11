
#include "config.hpp"
boost::shared_ptr<iconfig> iconfig::get_instance(const std::string& filename)
{
	
	if (m_ps == nullptr)
	{
		boost::mutex::scoped_lock t(m_mu);
		if(m_ps == nullptr)
			m_ps = boost::shared_ptr<iconfig>(new iconfig(filename));
	}
	
	return m_ps;
	//C++ 11版本之后的跨平台实现 (volatile)
	// std::atomic<Singleton*> Singleton::m_instance;
	// std::mutex Singleton::m_mutex;

	// Singleton* Singleton::getInstance() {
	//     Singleton* tmp = m_instance.load(std::memory_order_relaxed);
	//     std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
	//     if (tmp == nullptr) {
	//         std::lock_guard<std::mutex> lock(m_mutex);
	//         tmp = m_instance.load(std::memory_order_relaxed);
	//         if (tmp == nullptr) {
	//             tmp = new Singleton;
	//             std::atomic_thread_fence(std::memory_order_release);//释放内存fence
	//             m_instance.store(tmp, std::memory_order_relaxed);
	//         }
	//     }
	//     return tmp;
	// }
}

iconfig::iconfig(const std::string& filename)
{			
	boost::property_tree::ini_parser::read_ini(filename, m_pt);
	m_mysql_ip = m_pt.get<std::string>("mysql.ip");
	m_mysql_port = boost::lexical_cast<unsigned short>(m_pt.get<std::string>("mysql.port"));
	m_mysql_username = m_pt.get<std::string>("mysql.username");
	m_mysql_password = m_pt.get<std::string>("mysql.password");
	m_mysql_database = m_pt.get<std::string>("mysql.database");
	m_mysql_table = m_pt.get<std::string>("mysql.table");
	m_mysql_table2 = m_pt.get<std::string>("mysql.table2");
	m_threads = boost::lexical_cast<int>(m_pt.get<std::string>("webserver.threads"));
	m_port = boost::lexical_cast<int>(m_pt.get<std::string>("webserver.port"));
	m_url=boost::lexical_cast<std::string>(m_pt.get<std::string>("webserver.url"));
	m_orderbot_username = m_pt.get<std::string>("orderbot.username");
	m_orderbot_password = m_pt.get<std::string>("orderbot.password");
	m_orderbot_url = m_pt.get<std::string>("orderbot.url");	
	m_activemq_username = m_pt.get<std::string>("activemq.username");
	m_activemq_password = m_pt.get<std::string>("activemq.password");
	m_activemq_url = m_pt.get<std::string>("activemq.url");	
	// m_activemq_read_queue = m_pt.get<std::string>("activemq.read_queue");
	// m_activemq_write_queue = m_pt.get<std::string>("activemq.write_queue");	
	m_activemq_write_product_queue= m_pt.get<std::string>("activemq.write_product_queue");
	m_write_product_interval = boost::lexical_cast<size_t>(m_pt.get<std::string>("activemq.write_product_interval"));	
	m_activemq_read_order_queue= m_pt.get<std::string>("activemq.read_order_queue");	
	m_activemq_write_order_queue= m_pt.get<std::string>("activemq.write_order_queue");	
	m_exchange_rate_url=m_pt.get<std::string>("exchange_rate.url");
	m_exchange_rate_request_interval=m_pt.get<size_t>("exchange_rate.request_interval");
	m_exchange_rate_key=m_pt.get<std::string>("exchange_rate.key");
	m_exchange_rate_write_rate_queue=m_pt.get<std::string>("exchange_rate.write_rate_queue");
	/////////////////////////////////////////
	m_mysql_eu_ip = m_pt.get<std::string>("mysql_eu.ip");
	m_mysql_eu_port = boost::lexical_cast<unsigned short>(m_pt.get<std::string>("mysql_eu.port"));
	m_mysql_eu_username = m_pt.get<std::string>("mysql_eu.username");
	m_mysql_eu_password = m_pt.get<std::string>("mysql_eu.password");
	m_mysql_eu_database = m_pt.get<std::string>("mysql_eu.database");

	m_mysql_js_ip = m_pt.get<std::string>("mysql_js.ip");
	m_mysql_js_port = boost::lexical_cast<unsigned short>(m_pt.get<std::string>("mysql_js.port"));
	m_mysql_js_username = m_pt.get<std::string>("mysql_js.username");
	m_mysql_js_password = m_pt.get<std::string>("mysql_js.password");
	m_mysql_js_database = m_pt.get<std::string>("mysql_js.database");

	m_mysql_as_ip = m_pt.get<std::string>("mysql_as.ip");
	m_mysql_as_port = boost::lexical_cast<unsigned short>(m_pt.get<std::string>("mysql_as.port"));
	m_mysql_as_username = m_pt.get<std::string>("mysql_as.username");
	m_mysql_as_password = m_pt.get<std::string>("mysql_as.password");
	m_mysql_as_database = m_pt.get<std::string>("mysql_as.database");

	m_log_name = m_pt.get<std::string>("log.name");
	m_log_level = m_pt.get<std::string>("log.level");
	m_log_console_level= m_pt.get<std::string>("log.console_level");
	m_log_size = m_pt.get<size_t>("log.size");
	m_log_numbers = m_pt.get<size_t>("log.numbers");
}
	
boost::shared_ptr<iconfig> iconfig::m_ps = nullptr;
boost::mutex iconfig::m_mu;
boost::shared_ptr<iconfig> get_config= iconfig::get_instance("config.ini");


