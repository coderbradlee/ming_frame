#include "month_report.hpp"

month_report::month_report(boost::shared_ptr<mysql_connect> in,boost::shared_ptr<report_data> rd):m_mysql_connect(in),m_report_data(rd){}
void month_report::start()
{
	string query_string=
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
	m_mysql_connect->query(query_string);
	boost::shared_ptr<sql::ResultSet> rs=m_mysql_connect->get_res();
	while (rs->next()) 
    {
		std::cout<< res->getString(0)<<":" << res->getString("quotation_no")<<std::endl;
	 
   }
}
void start_report()
{
	boost::shared_ptr<report_data> r(new report_data());
	boost::shared_ptr<mysql_info> info(new mysql_info());
	info->ip=get_config->m_mysql_js_ip;
	info->username=get_config->m_mysql_js_username;
	info->password=get_config->m_mysql_js_password;
	info->database=get_config->m_mysql_js_database;

	info->port=boost::lexical_cast<string>(get_config->m_mysql_js_port);
	boost::shared_ptr<mysql_connect>  m(new mysql_connect(info));
	month_report report(m,r);
	report.start();
}