#ifndef TEST_HPP
#define	TEST_HPP
#include "../log.hpp"
#include "../include.hpp"
namespace test1
{
	namespace test_model_design_factory
	{
		class isplitter_base
		{
		public:
			virtual void split()=0;
			virtual ~isplitter_base(){}
		};
		class binary_spitter:public isplitter_base
		{
		public:
			void split();
		};
		class factory_base
		{
		public:
			virtual boost::shared_ptr<isplitter_base> create()=0;
			virtual ~factory_base(){}
		};
		class binary_factory:public factory_base
		{
		public:
			boost::shared_ptr<isplitter_base> create();
		};
		class caller
		{	
		public:
			caller(boost::shared_ptr<factory_base> fb);
			void start();
		private:
			boost::shared_ptr<factory_base> m_ib;
		};
		void test();
	}
	namespace test_model_design_prototype
	{
		class ispitter
		{
		public:
			virtual void split()=0;
			virtual boost::shared_ptr<ispitter> clone()=0;
			virtual ~ispitter(){}
		};
		class txt_spitter
		{
		public:
			txt_spitter(const txt_spitter& t);
			void split();
			boost::shared_ptr<ispitter> clone();
		};
		class caller
		{
		public:
			caller(boost::shared_ptr<ispitter>);
			void start();
		private:
			boost::shared_ptr<ispitter> m_is;
		};
		void test();
	}
	void test();
}
#endif

