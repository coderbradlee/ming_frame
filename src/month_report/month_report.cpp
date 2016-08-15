#include "month_report.hpp"

month_report::month_report(boost::shared_ptr<mysql_info> in,boost::shared_ptr<report_data> rd):m_report_data(rd)
{
	m_driver = get_driver_instance();
	m_con = boost::shared_ptr<sql::Connection>(m_driver->connect("tcp://"+in->ip+":"+in->port, in->username, in->password));
	
	m_con->setSchema(in->database);
}
void month_report::start()
{
	muduo::string query_string=
	"SELECT\
	t_quotation.quotation_no,\
	t_quotation_detail.ss_item_category_id,\
	t_quotation_detail.uom_id,\
	t_quotation_detail.quantity,\
	t_quotation_detail.ss_guidance_price,\
	t_quotation_detail.module_extend_prop,\
	t_quotation_detail.applied_unit_price,\
	t_quotation.createAt\
	FROM\
	t_quotation LEFT JOIN\
	t_quotation_detail\
	on\
	t_quotation_detail.quotation_id = t_quotation.quotation_id\
	and t_quotation_detail.dr=0 and t_quotation.createAt like \"2016-07%\"\
	and t_quotation.i\
	ORDER BY t_quotation.createAt";
	query(query_string);
	while (m_res->next()) 
    {
		std::cout<< m_res->getString(0)<<":" << m_res->getString("quotation_no")<<std::endl;
	 
   }
}
void month_report::query(const muduo::string& query_sql)
{
	try 
	{
	  m_pstmt = boost::shared_ptr<sql::PreparedStatement>(m_con->prepareStatement(query_sql));
	  m_res = boost::shared_ptr<sql::ResultSet>(m_pstmt->executeQuery());

	} 
	catch (sql::SQLException &e) 
	{
	  //ming_log->get_log_console()->info()<< "# ERR: " << e.what();
	  //ming_log->get_log_console()->info()<< " (MySQL error code: " << e.getErrorCode();
	  //ming_log->get_log_console()->info()<< ", SQLState: " << e.getSQLState();
	  LOG_ERROR<<"# ERR: " << e.what();
	  LOG_ERROR<<" (MySQL error code: " << e.getErrorCode();
	  LOG_ERROR<<", SQLState: " << e.getSQLState();

	}
}
boost::shared_ptr<sql::ResultSet> month_report::get_res()const
{
	return m_res;
}
void start_report()
{
	boost::shared_ptr<report_data> r(new report_data());
	boost::shared_ptr<mysql_info> info(new mysql_info());
	info->ip=get_config->m_mysql_js_ip;
	info->username=get_config->m_mysql_js_username;
	info->password=get_config->m_mysql_js_password;
	info->database=get_config->m_mysql_js_database;

	info->port=boost::lexical_cast<std::string>(get_config->m_mysql_js_port);
	month_report report(info,r);
	report.start();
}