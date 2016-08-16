#include "month_report.hpp"

month_report::month_report(boost::shared_ptr<mysql_info_> in)
{
	m_driver = get_driver_instance();
	m_con = boost::shared_ptr<sql::Connection>(m_driver->connect("tcp://"+in->ip+":"+in->port, in->username, in->password));
	
	m_con->setSchema(in->database);
}
void month_report::deal_with_sales_info()
{
	try
	{
	//for(auto i=m_report_datas.begin();i!=m_report_datas.end();++i)
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[&](boost::shared_ptr<report_data>& i)
	{
		std::string query_strings="select sales_id from t_quotation where quotation_id='"+(i)->quotation_id+"'";
		std::cout<<query_strings<<":"<<__FILE__<<":"<<__LINE__<<std::endl;

		{
			boost::scoped_ptr< sql::Statement > stmt(m_con->createStatement());
			boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery(query_strings));
			// boost::scoped_ptr< sql::PreparedStatement > prep_stmt(m_con->prepareStatement(query_string));
			// boost::scoped_ptr< sql::ResultSet > res(prep_stmt->executeQuery());
			
			// query_strings="select employee_no from t_system_account where system_account_id='"+c_string+"'";
			sql::ResultSetMetaData * meta = res->getMetaData();
			std::cout << "#\t\t COLUMN_SIZE = " << meta->getColumnDisplaySize(1) << std::endl;
			std::cout<<__FILE__<<":"<<__LINE__<<":"<<res->rowsCount()<<std::endl;
			std::cout<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			std::string c_string = res->getString("sales_id").asStdString();
			std::cout<<c_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			//query_strings="select employee_no from t_system_account where system_account_id='"+m_res->getString(1).asStdString()+"'";
			//std::cout<<query_strings<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			
		}
		// {
		// 	boost::scoped_ptr< sql::ResultSet > res(m_pstmt->executeQuery(query_string));
		// 	query_string="select  full_name,position_id  from t_employee where employee_id='"+res->getString("employee_no")+"'";
		// }
		
		// {
		// 	boost::scoped_ptr< sql::ResultSet > res(m_pstmt->executeQuery(query_string));
		// 	(i)->sales_full_name=m_res->getString("full_name");
		// 	query_string="select full_name,company_id from t_position where position_id='"+res->getString("position_id")+"'";
		// }
		// {
		// 	boost::scoped_ptr< sql::ResultSet > res(m_pstmt->executeQuery(query_string));
		// 	(i)->sales_type=res->getString("full_name");
		// 	query_string="select full_name from t_company where company_id='"+m_res->getString("company_id")+"'";
		// }
		// {
		// 	boost::scoped_ptr< sql::ResultSet > res(m_pstmt->executeQuery(query_string));
		// 	(i)->account_name=m_res->getString("full_name");
		// }
	});
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
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
	catch (std::exception& e)
  	{
    	LOG_ERROR<<"# ERR: " << e.what();
  	}
  	catch (...)
  	{
    	LOG_ERROR<<"unknown error ";
  	}
}
void month_report::insert_data()
{
	try
	{
		std::cout<<__FILE__<<":"<<__LINE__<<":"<<m_res->rowsCount()<<std::endl;
	while(m_res->next())
	{
		//std::cout<< m_res->getString(1)<<":" << m_res->getString("product_qty_pc")<<std::endl;
	 	boost::shared_ptr<report_data> temp(new report_data());
	 	temp->quotation_id=m_res->getString("quotation_id");
	 	temp->quotation_detail_id=m_res->getString("quotation_detail_id");

	 	temp->quotation_no=m_res->getString("quotation_no");
	 	temp->product_qty_pc=m_res->getDouble("product_qty_pc");
	 	if(!m_res->isNull("guidance_price"))
	 	{
	 		temp->price_total_guided=m_res->getDouble("product_qty_pc")*m_res->getDouble("guidance_price");
	 	}
	 	if(!m_res->isNull("module_extend_prop"))
	 	{
	 		temp->product_qty_w=m_res->getDouble("product_qty_pc")*m_res->getDouble("module_extend_prop");
	 	}
	 	else
	 	{
	 		temp->product_qty_w=0;
	 	}
	 	if(!m_res->isNull("unit_price"))
	 	{
	 		temp->unit_price=m_res->getDouble("unit_price");
	 		temp->price_total=temp->unit_price*temp->product_qty_w;
	 	}
	 	
	 	temp->creat_at=m_res->getString("creat_at");
	 	m_report_datas.push_back(temp);
	 	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
	}
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
	catch (std::exception& e)
  	{
    	LOG_ERROR<<"# ERR: " << e.what();
  	}
  	catch (...)
  	{
    	LOG_ERROR<<"unknown error ";
  	}
}
void month_report::start()
{
	try
	{
	
	std::string query_string="select sales_id from t_quotation where quotation_id='JD9JY8Z3GNH1H09U4XSD'";
	query(query_string);
	std::string c_string = m_res->getString("sales_id").asStdString();
	std::cout<<c_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
	std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
	//insert_data();
	//deal_with_sales_info();
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
	catch (std::exception& e)
  	{
    	LOG_ERROR<<"# ERR: " << e.what();
  	}
  	catch (...)
  	{
    	LOG_ERROR<<"unknown error ";
  	}
}
void month_report::query(const std::string& query_sql)
{
	try 
	{
	  std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
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
	boost::shared_ptr<mysql_info_> info(new mysql_info_());
	info->ip=get_config->m_mysql_js_ip;
	info->username=get_config->m_mysql_js_username;
	info->password=get_config->m_mysql_js_password;
	info->database=get_config->m_mysql_js_database;

	info->port=boost::lexical_cast<std::string>(get_config->m_mysql_js_port);
	boost::shared_ptr<month_report> report(new month_report(info));
	report->start();
}