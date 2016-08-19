#include "italy_lead_report.hpp"

month_report::month_report(boost::shared_ptr<mysql_info_> in)
{
	m_driver = get_driver_instance();
	m_con = boost::shared_ptr<sql::Connection>(m_driver->connect("tcp://"+in->ip+":"+in->port, in->username, in->password));
	
	m_con->setSchema(in->database);
}
void month_report::deal_with()
{
	try
	{
	for(auto& i:m_report_datas)
	{
		std::string query_string="select alphabet_shortname from t_country where country_id='"+i->country_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("alphabet_shortname")||m_res->getString(1)=="") 
		{
			
		}
		else
		{
			i->country=m_res->getString(1);
		}
		

		
		query_string="select account_name from t_system_account where system_account_id='"+i->owner_sales_sys_account_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("account_name")||m_res->getString(1)=="") 
		{
			
		}
		else
		{
			i->lead_owner=m_res->getString(1);
		}
		

		query_string="select full_name from t_state where state_id='"+i->state_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("full_name")||m_res->getString(1)=="") {}
		else
		{
			i->state=m_res->getString("full_name");
		}
		
   
   		query_string="select full_name from t_city where city_id='"+i->city_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("full_name")||m_res->getString(1)=="") {}
		else
		{
			i->city=m_res->getString("full_name");
		}
		
		query_string="select employee_no from t_system_account where system_account_id='"+i->owner_sales_sys_account_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("employee_no")||m_res->getString(1)=="") 
		{
			std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		}
		else
		{
			i->sales_employee_id=m_res->getString("employee_no");
		}
		
		query_string="\
		select master_file_obj_id \
		from t_wf_role_resolve \
		where master_file_type='COMPANY' \
		and employee_id='"+i->sales_employee_id+"'";
		//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		if(m_res->rowsCount()<1||m_res->isNull("master_file_obj_id")||m_res->getString(1)=="") 
		{
			
		}
		else
		{
			query_string="select short_name from t_company where company_id='"+m_res->getString(1)+"'";
			//std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
			query(query_string);
			m_res->next();
			if(m_res->rowsCount()<1||m_res->isNull("short_name")||m_res->getString(1)=="") 
			{
				
			}
			else
			{
				i->sales_company_name=m_res->getString("short_name");
			}	
		}

		query_string="select employee_no from t_system_account where system_account_id='"+i->last_modified_by+"'";
		std::cout<<query_string<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
		query(query_string);
		m_res->next();
		
		if(m_res->rowsCount()>1&&!m_res->isNull("employee_no"))
		{
			query_string="select full_name from t_employee where employee_id='"+m_res->getString("employee_no")+"'";
			if(!m_res->isNull("full_name"))
			{
				i->last_modified_by=m_res->getString("full_name");
			}
		}	
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

void month_report::insert_data()
{
	try
	{
		std::cout<<__FILE__<<":"<<__LINE__<<":"<<m_res->rowsCount()<<std::endl;
	while(m_res->next())
	{
		//std::cout<< m_res->getString(1)<<":" << m_res->getString("product_qty_pc")<<std::endl;
	 	boost::shared_ptr<report_data> temp(new report_data());
	 	temp->lead_id=m_res->getString("lead_id");
	 	temp->owner_sales_sys_account_id=m_res->getString("owner_sales_sys_account_id");
	 	temp->account_name=m_res->getString("trade_name");
	 	temp->country_id=m_res->getString("country_id");
	 	temp->state_id=m_res->getString("state_id");
	 	temp->city_id=m_res->getString("city_id");
	 	temp->allocated_time=m_res->getString("createAt");
	 	temp->last_modified=m_res->getString("updateAt");
	 	if(m_res->isNull("updateBy")||m_res->getString(9)=="") 
		{
			
		}
		else
		{
			temp->last_modified_by=m_res->getString("updateBy");
		}
	 	
	 	m_report_datas.push_back(temp);
	}
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
void month_report::write_to_csv()
{
	write_csv w("italy_lead_report.csv");
	std::for_each(m_report_datas.begin(),m_report_datas.end(),[&](boost::shared_ptr<report_data>& x)
		{
			//if(x->country=="US")
			if(x->sales_company_name=="ReneSola Italy")
			{
				w.addData(x->csv_line());
			}
		});
}
void month_report::start()
{
	try
	{
	std::string query_string=
	"select lead_id,trade_name,owner_sales_sys_account_id,country_id,state_id,city_id,createAt,updateAt,updateBy from t_lead";
	
	query(query_string);

	insert_data();
	deal_with();
	write_to_csv();
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