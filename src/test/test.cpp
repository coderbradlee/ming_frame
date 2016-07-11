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
void test()
{
	test_model_design_factory::test();
}
}