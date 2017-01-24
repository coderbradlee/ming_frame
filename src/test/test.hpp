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
			void set_windows(const std::string& w)
			{
				windows=w;
			}
			void set_doors(const std::string& d)
			{
				doors=d;
			}
			std::string get_windows()const
			{
				return windows;
			}
			std::string get_doors()const
			{
				return doors;
			}
		protected:
			std::string windows;
			std::string doors;
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
		std::string convert_json(const std::string& source);
	
		void test();

	}
	namespace test_design_model_flyweight
	{
		class font
		{
		public:
			font(const std::string& key);
			std::string get_key()const;
		private:
			std::string m_key;
		};
		class font_factory
		{
		public:
			boost::shared_ptr<font> get_font(const std::string& f);
		private:
			std::map<std::string,boost::shared_ptr<font>> m_font;
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
			component(const std::string& m):m_name(m){}
			virtual void process()=0;
			virtual ~component(){}
			std::string get_name()
			{
				return m_name;
			}
		protected:
			std::string m_name;
		};
		class composite:public component
		{
		public:
			composite(const std::string& s):component(s){}
			void add(boost::shared_ptr<component>);
			void remove(boost::shared_ptr<component>);
			void process();
		
			std::list<boost::shared_ptr<component>> m_elment;
		};
		class leaf:public component
		{
		public:
			leaf(const std::string& s):component(s){}	
			void process();		
		};
		void test();
	}
	namespace test_design_model_chainofresponsibility
	{
		enum class request_type
		{
			handler1,
			handler2,
			handler3
		};
		class request
		{
		public:
			request(request_type r):m_request_type(r){}
			request_type get_request_type()const{return m_request_type;}
		private:
			request_type m_request_type;
		};
		class chain
		{
		public:
			void set_next_chain(boost::shared_ptr<chain> c)
			{
				m_next=c;
			} 
			virtual bool can_handle(boost::shared_ptr<request> re)=0;
			virtual void handle(boost::shared_ptr<request> re)=0;
			void start(boost::shared_ptr<request> re)
			{
				if(can_handle(re))
					handle(re);
				send_request(re);
				
			}
			virtual ~chain(){}
		private:
			void send_request(boost::shared_ptr<request> re)
			{
				if(m_next!=nullptr)
				m_next->start(re);
			}
		private:
			boost::shared_ptr<chain> m_next;
		};
		class handler1_chain:public chain
		{
		public:
			bool can_handle(boost::shared_ptr<request> re);
			void handle(boost::shared_ptr<request> re);
		};
		class handler2_chain:public chain
		{
		public:
			bool can_handle(boost::shared_ptr<request> re);
			void handle(boost::shared_ptr<request> re);
		};
		void test();
	}
	namespace test_design_model_visitor
	{
		class visitor;
		class element
		{
		public:
			virtual void accept(visitor&)=0;
			virtual ~element(){}
		};
		class element1:public element
		{
		public:
			void accept(visitor&);
		};
		class element2:public element
		{
		public:
			void accept(visitor&);
		};
		class visitor
		{
		public:
			virtual void visit_1(element&)=0;
			virtual void visit_2(element&)=0;
			virtual ~visitor(){}

		};
		class visitor1:public visitor
		{
		public:
			void visit_1(element&)override;
			void visit_2(element&)override;
		};
		class visitor2:public visitor
		{
		public:
			void visit_1(element&)override;
			void visit_2(element&)override;
		};
		void test();
	}
	namespace test_design_model_interpreter
	{
		using boost::shared_ptr;
		class expression
		{
		public:
			virtual int interpreter(std::map<char,int>)=0;
			virtual ~expression(){}
		};
		class var_expression:public expression
		{
		public:
			var_expression(char key):m_key(key){}
			int interpreter(std::map<char,int>);
		private:
			char m_key;
		};
		class symbol_expression:public expression
		{
		public:
			symbol_expression(shared_ptr<expression> left,shared_ptr<expression> right):m_left(left),m_right(right){}
			
		protected:
			shared_ptr<expression> m_left;
			shared_ptr<expression> m_right;
		};
		class add_expression:public symbol_expression
		{
		public:
			add_expression(shared_ptr<expression> left,shared_ptr<expression> right):symbol_expression(left,right){}
			int interpreter(std::map<char,int>);
		};
		class sub_expression:public symbol_expression
		{
		public:
			sub_expression(shared_ptr<expression> left,shared_ptr<expression> right):symbol_expression(left,right){}
			int interpreter(std::map<char,int>);
		};
		shared_ptr<expression> analyse(std::string& expr);
		void test();
	}
	void test();
}
#endif
