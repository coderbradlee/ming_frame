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
	        	if(hour_minute=="12:00")
	        	{
	        		LOG_INFO<<"XX";
	        		boost::this_thread::sleep(boost::posix_time::millisec(60000));
	        	}
	        	
	        	//cout<<"handle wait"<<endl;
	            m_d_t.expires_from_now(boost::posix_time::seconds(10));  
	            m_d_t.async_wait(boost::bind(&test_deadline::handle_wait_,shared_from_this(), boost::asio::placeholders::error));                 
	    	}   
		}  
		void test_deadline::start()
		{
			m_d_t.expires_from_now(boost::posix_time::seconds(10);
		  
		    m_d_t.async_wait(boost::bind(&test_deadline::handle_wait_, shared_from_this(), boost::asio::placeholders::error));  
			m_io_s.run();
		}
		void test()
		{
			boost::shared_ptr<test_deadline> t(new test_deadline());
			t->start();
		}
	}
void test()
{
	//test_model_design_factory::test();
	//test_model_design_prototype::test();
	//test_model_design_builder::test();
	test_deadline_timer::test();
}
}