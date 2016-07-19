#include "test.hpp"
namespace test1
{
	namespace test_model_design_factory
	{ 
		
		void binary_spitter::split()
		{
			LOG_INFO<<"binary_spitter split";
		}
	    boost::shared_ptr<isplitter_base> binary_factory::create()
	    {
	    	return boost::shared_ptr<isplitter_base>(new binary_spitter());
	    }
		
		caller::caller(boost::shared_ptr<factory_base> fb):m_ib(fb){}
		void caller::start()
		{
			boost::shared_ptr<isplitter_base> m=m_ib->create();
			m->split();
		}
		void test()
		{
			boost::shared_ptr<factory_base> fb(new binary_factory());
			boost::shared_ptr<caller> c(new caller(fb));
			c->start();
		}
	}
	namespace test_model_design_prototype
	{
		// txt_spitter::txt_spitter(const txt_spitter& t)
		// {
		// 	LOG_INFO<<"txt_spitter copy constructor";
		// }
		void txt_spitter::split()
		{
			LOG_INFO<<"txt_spitter";
		}
		boost::shared_ptr<ispitter> txt_spitter::clone()const
		{
			return boost::shared_ptr<ispitter>(new txt_spitter(*this));
		}
		caller::caller(boost::shared_ptr<ispitter> is):m_is(is){}
		void caller::start()
		{
			boost::shared_ptr<ispitter> t=m_is->clone();
			t->split();
		}
		
		void test()
		{
			boost::shared_ptr<ispitter> is(new txt_spitter());

			caller c(is);
			c.start();

		}
	}
	namespace test_model_design_builder
	{
		void stone_house_builder::build_windows()
		{
			m_house->set_windows("stone windows");

		}
		void stone_house_builder::build_doors()
		{
			m_house->set_doors("stone doors");
		}

		boost::shared_ptr<house> house_director::constuct()
		{
			m_builder->build_windows();
			m_builder->build_doors();
			return m_builder->get_house();
		}
		
		void test()
		{
			house_director h(boost::shared_ptr<house_builder>(new stone_house_builder()));
			boost::shared_ptr<house> hou=h.constuct();
			LOG_INFO<<hou->get_windows()<<":"<<hou->get_doors();
		}
	}
	namespace test_deadline_timer
	{

		test_deadline::test_deadline():m_d_t(m_io_s){}
		void test_deadline::handle_wait_method()
		{
			boost::this_thread::sleep(boost::posix_time::millisec(60000));
		}
		void test_deadline::handle_wait_(const boost::system::error_code& error)  
	    {  
	        if(!error)  
	        {  
	        	ptime now = second_clock::local_time();			
				string hour_minute_second = to_simple_string(now.time_of_day());
				std::vector<std::string> hms;
	 			
				boost::split(hms,hour_minute_second , boost::is_any_of(":"));
	 			//string [] ymd=to_iso_extended_string(now.date()).split('-');
	 			string hour=hms[0];
	 			string minute=hms[1];
	 			
	        	string hour_minute=hour+":"+minute;
	        	LOG_INFO<<hour_minute;
	        	if(hour_minute==get_config->m_exchange_rate_insert_time)
	        	{
	        		LOG_INFO<<"XX";
	        		handle_wait_method();
	        	}
	        	
	        	//cout<<"handle wait"<<endl;
	            m_d_t.expires_from_now(boost::posix_time::seconds(10));  
	            m_d_t.async_wait(boost::bind(&test_deadline::handle_wait_,shared_from_this(), boost::asio::placeholders::error));                 
	    	}   
		}  
		void test_deadline::start()
		{
			m_d_t.expires_from_now(boost::posix_time::seconds(10));
		  
		    m_d_t.async_wait(boost::bind(&test_deadline::handle_wait_, shared_from_this(), boost::asio::placeholders::error));  
			m_io_s.run();
		}
		void test()
		{

		boost::shared_ptr<test_deadline> t1(new test_deadline());
		boost::shared_ptr<test_deadline> t2(new test_deadline());
		boost::shared_ptr<test_deadline> t3(new test_deadline());
			
		thread t11([&t1](){t1->start();});
		thread t22([&t2](){t2->start();});
		thread t33([&t3](){t3->start();});
		t11.join();
		t22.join();
		t33.join();
			
		}
	}
	namespace test_json_parser
	{
		string convert_json(const string& source)
		{
				//{
	//   "quotes":{
	//     "USDCNY":6.683198,
	//     "USDEUR":0.8993
	//   }
	// }
			//{"query":{"count":27,"created":"2016-07-12T09:16:05Z","lang":"zh-CN","results":{"rate":[{"id":"USDEUR","Rate":"0.9049"},{"id":"USDJPY","Rate":"103.4770"},{"id":"USDBGN","Rate":"1.7701"},{"id":"USDGBP","Rate":"0.7645"},{"id":"USDPLN","Rate":"4.0007"},{"id":"USDRON","Rate":"4.0594"},{"id":"USDSEK","Rate":"8.5780"},{"id":"USDHRK","Rate":"6.7240"},{"id":"USDRUB","Rate":"64.0240"},{"id":"USDTRY","Rate":"2.9010"},{"id":"USDAUD","Rate":"1.3181"},{"id":"USDBRL","Rate":"3.3098"},{"id":"USDCAD","Rate":"1.3097"},{"id":"USDCNY","Rate":"6.6917"},{"id":"USDHKD","Rate":"7.7575"},{"id":"USDIDR","Rate":"13080.0000"},{"id":"USDINR","Rate":"67.1380"},{"id":"USDKRW","Rate":"1148.3000"},{"id":"USDMXN","Rate":"18.4196"},{"id":"USDNZD","Rate":"1.3812"},{"id":"USDPHP","Rate":"47.2500"},{"id":"USDSGD","Rate":"1.3520"},{"id":"USDTHB","Rate":"35.1400"},{"id":"USDZAR","Rate":"14.4255"},{"id":"USDTWD","Rate":"32.1880"},{"id":"USDCNY","Rate":"6.6917"},{"id":"USDPHP","Rate":"47.2500"}]}}}
			const auto& j = nlohmann_map::json::parse(source);
			const auto& query = j["query"];//results":{"rate
			const auto& results =query["results"];
			if (results.find("rate") == results.end()) 
			{
				cout<<"get json error from yahoo.finance.xchange:"<<__FILE__<<":"<<__LINE__<<endl;
				return "";
			}
			const auto& rate=results["rate"];
			string temp="{\"quotes\":{";
			for(const auto& r:rate)
			{
				string id=r["id"];
				string Rate=r["Rate"];
				//cout<<id<<":"<<Rate<<endl;
				temp+="\""+id+"\":"+Rate+",";
			}
			string a=temp.substr(0,temp.length()-1);
			return a+"}}";
		}
	
		void test()
		{
			string source="{\"query\":{\"count\":27,\"created\":\"2016-07-12T09:16:05Z\",\"lang\":\"zh-CN\",\"results\":{\"rate\":[{\"id\":\"USDEUR\",\"Rate\":\"0.9049\"},{\"id\":\"USDJPY\",\"Rate\":\"103.4770\"},{\"id\":\"USDBGN\",\"Rate\":\"1.7701\"},{\"id\":\"USDGBP\",\"Rate\":\"0.7645\"},{\"id\":\"USDPLN\",\"Rate\":\"4.0007\"},{\"id\":\"USDRON\",\"Rate\":\"4.0594\"},{\"id\":\"USDSEK\",\"Rate\":\"8.5780\"},{\"id\":\"USDHRK\",\"Rate\":\"6.7240\"},{\"id\":\"USDRUB\",\"Rate\":\"64.0240\"},{\"id\":\"USDTRY\",\"Rate\":\"2.9010\"},{\"id\":\"USDAUD\",\"Rate\":\"1.3181\"},{\"id\":\"USDBRL\",\"Rate\":\"3.3098\"},{\"id\":\"USDCAD\",\"Rate\":\"1.3097\"},{\"id\":\"USDCNY\",\"Rate\":\"6.6917\"},{\"id\":\"USDHKD\",\"Rate\":\"7.7575\"},{\"id\":\"USDIDR\",\"Rate\":\"13080.0000\"},{\"id\":\"USDINR\",\"Rate\":\"67.1380\"},{\"id\":\"USDKRW\",\"Rate\":\"1148.3000\"},{\"id\":\"USDMXN\",\"Rate\":\"18.4196\"},{\"id\":\"USDNZD\",\"Rate\":\"1.3812\"},{\"id\":\"USDPHP\",\"Rate\":\"47.2500\"},{\"id\":\"USDSGD\",\"Rate\":\"1.3520\"},{\"id\":\"USDTHB\",\"Rate\":\"35.1400\"},{\"id\":\"USDZAR\",\"Rate\":\"14.4255\"},{\"id\":\"USDTWD\",\"Rate\":\"32.1880\"},{\"id\":\"USDCNY\",\"Rate\":\"6.6917\"},{\"id\":\"USDPHP\",\"Rate\":\"47.2500\"}]}}}";
			string temp=convert_json(source);
			cout<<temp<<endl;
			LOG_INFO<<temp;
		}

	}
	namespace test_design_model_flyweight
	{
		
		font::font(const string& key):m_key(key){}
		string font::get_key()const
		{
			return m_key;
		}
		boost::shared_ptr<font> font_factory::get_font(const string& f)
		{
			auto ret=m_font.find(f);
			if(ret!=m_font.end())
				return m_font[f];
			else
			{
				boost::shared_ptr<font> t(new font(f));
				m_font[f]=t;
				cout<<m_font.size()<<endl;
				return t;
			}
		}
		
		void test()
		{
			font_factory f;
			cout<<f.get_font("zheng")->get_key()<<endl;
		}
	}
	namespace test_design_model_state
	{
		
		boost::shared_ptr<network_state> open_state::get_instance()
		{
			if(m_instance==nullptr)
			{
				m_instance=boost::shared_ptr<network_state>(new open_state());
			}
			return m_instance;
		}
		void open_state::operation1()
		{
			LOG_INFO<<"open_state::operation1";
			m_next=boost::shared_ptr<network_state>(new close_state());
		}
		void open_state::operation2()
		{
			LOG_INFO<<"open_state::operation2";
		}
		
	
		boost::shared_ptr<network_state> open_state::m_instance=nullptr;

		boost::shared_ptr<network_state> close_state::get_instance()
		{
			if(m_instance==nullptr)
			{
				m_instance=boost::shared_ptr<network_state>(new close_state());
			}
			return m_instance;
		}
		void close_state::operation1()
		{
			LOG_INFO<<"close_state::operation1";
		}
		
		void close_state::operation2()
		{
			LOG_INFO<<"close_state::operation2";
		}
	
		boost::shared_ptr<network_state> close_state::m_instance=nullptr;

		network_processor::network_processor(boost::shared_ptr<network_state> x):
		m_state(x){}
		
		void network_processor::operation1()
		{
			LOG_INFO<<"network_processor::operation1";
			m_state->operation1();	
			m_state=m_state->m_next;
		}
		void network_processor::operation2()
		{
			LOG_INFO<<"network_processor::operation2";
			m_state->operation2();	
		}
		
		void network_processor::start()
		{
			operation1();
			operation2();
		}
		
		void test()
		{
			boost::shared_ptr<network_state> o(new open_state());
			boost::shared_ptr<network_processor> p(new network_processor(o));
			p->start();
		}
	}
void test()
{
	//test_model_design_factory::test();
	//test_model_design_prototype::test();
	//test_model_design_builder::test();
	//test_deadline_timer::test();
	//test_json_parser::test();
	//test_design_model_flyweight::test();
	test_design_model_state::test();
}
}