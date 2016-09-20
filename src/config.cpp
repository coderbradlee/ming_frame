
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
	
	m_threads = boost::lexical_cast<int>(m_pt.get<std::string>("webserver.threads"));
	m_port = boost::lexical_cast<int>(m_pt.get<std::string>("webserver.port"));
	m_ports = boost::lexical_cast<int>(m_pt.get<std::string>("webserver.ports"));
	m_url=boost::lexical_cast<std::string>(m_pt.get<std::string>("webserver.url"));
	
	m_nfs_path=boost::lexical_cast<std::string>(m_pt.get<std::string>("nfs.path"));
	m_log_name = m_pt.get<std::string>("log.name");
	m_log_level = m_pt.get<std::string>("log.level");
}
	
boost::shared_ptr<iconfig> iconfig::m_ps = nullptr;
boost::mutex iconfig::m_mu;
boost::shared_ptr<iconfig> get_config= iconfig::get_instance("config.ini");
//extern boost::shared_ptr<iconfig> get_config;

