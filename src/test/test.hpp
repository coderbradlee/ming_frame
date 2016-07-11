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
			virtual boost::shared_ptr<ispitter> clone()const=0;
			virtual ~ispitter(){}
		};
		class txt_spitter:public ispitter
		{
		public:
			//txt_spitter(const txt_spitter& t);
			void split();
			boost::shared_ptr<ispitter> clone()const;
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
	namespace test_model_design_builder
	{
		class house
		{
		public:
			virtual ~house(){}
			void set_windows(const string& w)
			{
				windows=w;
			}
			void set_doors(const string& d)
			{
				doors=d;
			}
			string get_windows()const
			{
				return windows;
			}
			string get_doors()const
			{
				return doors;
			}
		protected:
			string windows;
			string doors;
		};
		class stone_house:public house
		{

		};
		class house_builder
		{
		public:
			virtual void build_windows()=0;
			virtual void build_doors()=0;
			virtual ~house_builder(){}
			boost::shared_ptr<house> get_house(){return m_house;}
		protected:
			boost::shared_ptr<house> m_house;
		};
		class stone_house_builder:public house_builder
		{
		public:
			stone_house_builder()
			{
				m_house=boost::shared_ptr<house>(new stone_house());
			}
			void build_windows();
			void build_doors();

		};
		class house_director
		{
		public:
			house_director(boost::shared_ptr<house_builder> m):m_builder(m){}
			boost::shared_ptr<house> constuct();
		private:
			boost::shared_ptr<house_builder> m_builder;
		};
		void test();
	}
	void test();
}
#endif

