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
	namespace test_deadline_timer
	{
		class test_deadline:public boost::enable_shared_from_this<test_deadline>
		{
		public:
			test_deadline();
			void start();
			void handle_wait_(const boost::system::error_code& error); 
			void handle_wait_method();
		private:
			boost::asio::io_service m_io_s;
			boost::asio::deadline_timer m_d_t;
			
		};
		
		void test();
	}
	namespace test_json_parser
	{
		string convert_json(const string& source);
	
		void test();

	}
	namespace test_design_model_flyweight
	{
		class font
		{
		public:
			font(const string& key);
			string get_key()const;
		private:
			string m_key;
		};
		class font_factory
		{
		public:
			boost::shared_ptr<font> get_font(const string& f);
		private:
			std::map<string,boost::shared_ptr<font>> m_font;
		};
		void test();
	}
	namespace test_design_model_state
	{
		class network_state
		{
		public:
			virtual void operation1()=0;
			virtual void operation2()=0;
			
			virtual ~network_state(){}
		public:
			boost::shared_ptr<network_state> m_next;

		};
		class open_state:public network_state
		{
		public:
			static boost::shared_ptr<network_state> get_instance();
			virtual void operation1();
			virtual void operation2();
			
		private:
			static boost::shared_ptr<network_state> m_instance;
		};
		class close_state:public network_state
		{
		public:
			static boost::shared_ptr<network_state> get_instance();
			virtual void operation1();
			virtual void operation2();
			
		private:
			static boost::shared_ptr<network_state> m_instance;
		};
		class network_processor
		{
		public:
			network_processor(boost::shared_ptr<network_state> x);
			void operation1();
			void operation2();
			
			void start();
		private:
			boost::shared_ptr<network_state> m_state;
		};
		void test();
	}
	namespace test_design_model_composite
	{
		class component
		{
		public:
			virtual void process()=0;
			virtual ~component(){}
			string get_name()
			{
				return m_name;
			}
		protected:
			string m_name;
		};
		class composite:public component
		{
		public:
			composite(const string& s):component::m_name(s){}
			void add(boost::shared_ptr<component>);
			void remove(boost::shared_ptr<component>);
			void process();
		
			std::list<boost::shared_ptr<component>> m_elment;
		};
		class leaf:public component
		{
		public:
			leaf(const string& s):component::m_name(s){}	
			void process();		
		};
		void test();
	}
	void test();
}
#endif

