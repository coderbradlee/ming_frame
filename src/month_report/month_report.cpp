#include "month_report.hpp"

month_report::month_report(boost::shared_ptr<mysql_info_> in)
{
	m_driver = get_driver_instance();
	m_con = boost::shared_ptr<sql::Connection>(m_driver->connect("tcp://"+in->ip+":"+in->port, in->username, in->password));
	
	m_con->setSchema(in->database);
}
void month_report::deal_with_trade_term_info()
{
	try
	{
	for(auto& i:m_report_datas)
	{
		std::string query_string="select trade_term_id from t_quotation where quotation_id='"+i->quotation_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("trade_term_id")||m_res->getString(1)=="") 
		{
			continue;
		}
		
		query_string="select short_name from t_trade_term where trade_term_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("short_name")||m_res->getString(1)=="") continue;
		i->price_condition=m_res->getString("short_name");
   
	};
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
	}
	catch (sql::SQLException &e) 
	{
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
void month_report::deal_with_product_info()
{
	try
	{
	for(auto& i:m_report_datas)
	{
		std::string query_string="select item_master_id from t_quotation_detail where quotation_detail_id='"+i->quotation_detail_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("item_master_id")||m_res->getString(1)=="") 
		{
			continue;
		}
		
		query_string="select item_basic_id,product_code from t_item_master where item_master_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("item_basic_id")||m_res->getString(1)=="") continue;
		i->product_name=m_res->getString("product_code");
   ///////////////////////////////////////////////////////////////////
		query_string="select item_category_id from t_item_basic where item_basic_id='"+m_res->getString(1)+"'";
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("item_category_id")||m_res->getString(1)=="") continue;

		query_string="select product_category_id from t_product_category_item_category_link where item_category_id='"+m_res->getString(1)+"'";
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("product_category_id")||m_res->getString(1)=="") continue;

		query_string="select parent_product_category_id from t_product_category where product_category_id='"+m_res->getString(1)+"'";
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("parent_product_category_id")||m_res->getString(1)=="") continue;
		
		query_string="select name from t_product_category where product_category_id='"+m_res->getString(1)+"'";
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("name")||m_res->getString(1)=="") continue;
		i->product_classification=m_res->getString(1);
	};
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
	}
	catch (sql::SQLException &e) 
	{
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
void month_report::deal_with_payment_method_info()
{
	try
	{
	for(auto& i:m_report_datas)
	{
		std::string query_string="select payment_method_id from t_payment_term where quotation_id='"+i->quotation_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("payment_method_id")||m_res->getString(1)=="") 
		{
			//std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
			continue;
		}
		
		query_string="select name from t_payment_method where payment_method_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("name")||m_res->getString(1)=="") continue;
		i->payment_term_desc=m_res->getString("name");
		
	};
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
	}
	catch (sql::SQLException &e) 
	{
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
void month_report::deal_with_currency_info()
{
	try
	{
	for(auto& i:m_report_datas)
	{
		std::string query_string="select currency_id from t_quotation where quotation_id='"+i->quotation_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("currency_id")||m_res->getString(1)=="") continue;
		query_string="select code from t_currency where currency_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("code")||m_res->getString(1)=="") continue;
		i->currency=m_res->getString("code");
		i->price_total_currency=m_res->getString("code");
		i->guided_currency=m_res->getString("code");
	};
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
	}
	catch (sql::SQLException &e) 
	{
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
void month_report::deal_with_customer_info()
{
	try
	{
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[&](boost::shared_ptr<report_data>& i)
	for(auto& i:m_report_datas)
	{
		std::string query_string="select delivery_country_id from t_quotation where quotation_id='"+i->quotation_id+"'";
		
		query(query_string);
		m_res->next();
		query_string="select full_name from t_country where country_id='"+m_res->getString(1)+"'";
	
		query(query_string);
		m_res->next();
		
		i->receiving_countries=m_res->getString("full_name");
		////////////////////////////////////////////////
		query_string="select customer_basic_id from t_quotation where quotation_id='"+i->quotation_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("customer_basic_id")) continue;
		query_string="select country_id,trade_name from t_customer_basic where customer_basic_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("country_id")||m_res->getString(1)=="") continue;
		if(m_res->isNull("trade_name")||m_res->getString(2)=="") 
		{

		}
		else
		{
			i->account_name=m_res->getString(2);
		}
		query_string="select full_name,area_id from t_country where country_id='"+m_res->getString(1)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("full_name")) continue;
		i->customer_countries=m_res->getString(1);
		if(m_res->isNull("area_id")) continue;
		query_string="select full_name from t_area where area_id='"+m_res->getString(2)+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->isNull("full_name")) continue;
		i->country_region=m_res->getString(1);

	};//);
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
}
	catch (sql::SQLException &e) 
	{
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
void month_report::deal_with_sales_info()
{
	try
	{
	//for(auto i=m_report_datas.begin();i!=m_report_datas.end();++i)
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[&](boost::shared_ptr<report_data>& i)
	{
		std::string query_string="select sales_id from t_quotation where quotation_id='"+(i)->quotation_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;

		query(query_string);
		m_res->next();
		query_string="select employee_no from t_system_account where system_account_id='"+m_res->getString(1)+"'";
	
		query(query_string);
		m_res->next();
		query_string="select full_name,position_id  from t_employee where employee_id='"+m_res->getString("employee_no")+"'";
		
		query(query_string);
		m_res->next();
		
		i->sales_full_name=m_res->getString("full_name");
		query_string="select full_name,company_id from t_position where position_id='"+m_res->getString("position_id")+"'";

		query(query_string);
		m_res->next();

		i->sales_type=m_res->getString("full_name");
		// query_string="select full_name from t_company where company_id='"+m_res->getString("company_id")+"'";

		// query(query_string);
		// m_res->next();
		// i->account_name=m_res->getString("full_name");
		
	});
	//std::for_each(m_report_datas.begin(),m_report_datas.end(),[](boost::shared_ptr<report_data>& x){x->print();});
}
	catch (sql::SQLException &e) 
	{
	  
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
	 	
	 	if(!m_res->isNull("module_extend_prop"))
	 	{
	 		temp->product_qty_w=m_res->getDouble("product_qty_pc")*m_res->getDouble("module_extend_prop");
	 	}
	 	else
	 	{
	 		temp->product_qty_w=0;
	 	}
	 	if(!m_res->isNull("guidance_price"))
	 	{
	 		temp->price_total_guided=temp->product_qty_w*m_res->getDouble("guidance_price");
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
void month_report::write_to_csv()
{
	write_csv w("month_report.csv");
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[&](boost::shared_ptr<report_data>& x)
		{
			w.addData(x->csv_line());
		});
}
void month_report::start()
{
	try
	{
	std::string query_string=
	"SELECT\
	t_quotation.quotation_id as quotation_id,\
	t_quotation_detail.quotation_detail_id as quotation_detail_id,\
	t_quotation.quotation_no as quotation_no,\
	t_quotation_detail.quantity as product_qty_pc,\
	t_quotation_detail.ss_guidance_price as guidance_price,\
	t_quotation_detail.module_extend_prop as module_extend_prop,\
	t_quotation_detail.applied_unit_price as unit_price,\
	t_quotation.createAt as creat_at\
	FROM\
	t_quotation INNER JOIN\
	t_quotation_detail\
	on\
	t_quotation_detail.quotation_id = t_quotation.quotation_id\
	and t_quotation_detail.dr=0 and t_quotation.createAt like \"2016-07%\" and approval_status>=3 and t_quotation.approval_status<>5 \
  and t_quotation.approval_status<>7 \
	ORDER BY t_quotation.createAt";
	
	query(query_string);

	insert_data();
	deal_with_sales_info();
	deal_with_customer_info();
	deal_with_currency_info();
	deal_with_payment_method_info();
	deal_with_product_info();
	deal_with_trade_term_info();
	write_to_csv();
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
	  //std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
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