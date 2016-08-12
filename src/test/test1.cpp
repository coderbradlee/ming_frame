#include "test1.hpp"
namespace test1_namespace
{
	using namespace boost::posix_time;
	using std::string;
	namespace test_intrusive_ptr2
	{
		template<typename T>
		void intrusive_ptr_add_ref(T* t)
		{
			t->add_ref();
		}
		template<typename T>
		void intrusive_ptr_release(T* t)
		{
			if(t->release()<=0)
			{
				delete t;
			}
		}

		class reference_couter
		{
		public:
			reference_couter():m_ref_count(0){}
			virtual ~reference_couter(){}
			void add_ref()
			{
				++m_ref_count;
				std::cout<<"add:"<<m_ref_count<<std::endl;
			}
			int release()
			{
				std::cout<<"release:"<<m_ref_count<<std::endl;
				return --m_ref_count;
			}
		protected:
			reference_couter& operator=(const reference_couter&)
			{
				return *this;
			}
		private:
			reference_couter(const reference_couter&);
		private:
			int m_ref_count;
		};
		///////class B////////////////
		class B;
		void do_stuff(boost::shared_ptr<B> p)
		{
			std::cout<<"shared_ptr do stuff"<<std::endl;
			std::cout<<__LINE__<<":"<<p.use_count() <<std::endl;
		}
		
		class B:public boost::enable_shared_from_this<B>
		{
		public:
			void call()
			{
				//boost::shared_ptr<B> p(this);
				boost::shared_ptr<B> p(shared_from_this());
				do_stuff(p);
				std::cout<<__LINE__<<":"<<p.use_count() <<std::endl;
			}
			~B()
			{

				std::cout<<"~B"<<std::endl;
			}
		private:
			char* x;
		};
		/////////////////////////////////////
		class A:public reference_couter
		//public boost::enable_shared_from_this<A>
		{
		public:
			void call();
		};
		void do_stuff(boost::shared_ptr<A> p);
		void do_stuff(boost::intrusive_ptr<A> p);
		void A::call()
		{
			// boost::shared_ptr<A> p(shared_from_this());
			// boost::shared_ptr<A> p(this);
			// do_stuff(p);
			do_stuff(this);
			// intrusive_ptr_add_ref(this);
			// boost::shared_ptr<A> p(this,&intrusive_ptr_release<A>);
			// do_stuff(p);
		}
		
		void do_stuff(boost::shared_ptr<A> p)
		{
			std::cout<<"shared_ptr do stuff"<<std::endl;
		}
		void do_stuff(boost::intrusive_ptr<A> p)
		{
			std::cout<<"intrusive_ptr do stuff"<<std::endl;
		}
		void test()
		{
			std::cout<<"before"<<std::endl;
			{
			// 	boost::shared_ptr<B> p(new B());
			// 	p->call();
			// 	std::cout<<__LINE__<<":"<<p.use_count() <<std::endl;
			}
			//std::cout<<"middle"<<std::endl;
			//std::cout<<sizeof(int)<<std::endl;
			{
				//boost::shared_ptr<A> p(new A());
				boost::intrusive_ptr<A> p(new A());
				p->call();
			}
			std::cout<<"after"<<std::endl;
		}
	}
	namespace test_intrusive_ptr
	{
		template<typename T>
		void intrusive_ptr_add_ref(T* t)
		{
			t->add_ref();
		}
		template<typename T>
		void intrusive_ptr_release(T* t)
		{
			if(t->release()<=0)
			{
				delete t;
			}
		}
		class reference_couter
		{
		public:
			reference_couter():m_ref_count(0){}
			virtual ~reference_couter(){}
			void add_ref()
			{
				++m_ref_count;
			}
			int release()
			{
				return --m_ref_count;
			}
		protected:
			reference_couter& operator=(const reference_couter&)
			{
				return *this;
			}
		private:
			reference_couter(const reference_couter&);
		private:
			int m_ref_count;
		};
		class test_class:public reference_couter
		{
		public:
			test_class()
			{
				std::cout<<"test_class constructor"<<std::endl;
			}
			test_class(const test_class&):reference_couter()
			{
				std::cout<<"copy constructor"<<std::endl;
			}
			~test_class()
			{
				std::cout<<"~test_class"<<std::endl;
			}
		};
		void test()
		{
			std::cout<<"before"<<std::endl;
			{
				boost::intrusive_ptr<test_class> p(new test_class());
				boost::intrusive_ptr<test_class> p1(p);
				std::cout<<sizeof(p)<<std::endl;
			}
			std::cout<<"after"<<std::endl;
		}
	}

		namespace test_down_cast
		{
			class A
			{
			public:
				//A();
			    void foo()
			    {
			    	std::cout<<"1"<<std::endl;
			    }
			    virtual void fuu()
			    {
			    	std::cout<<"2"<<std::endl;
			    }
			    virtual ~A()
			    {
			    	//printf("~A\n");
			    	std::cout<<"~A"<<std::endl;
			    }
			};

			class B:public A
			{
			public :
				//B();
			    void foo()
			    {
			    	std::cout<<"3"<<std::endl;
			    }
			    void fuu()
			    {
			    	std::cout<<"4"<<std::endl;
			    }
			};
			void test()
			{
					//printf("test()\n");
				std::cout<<"test()"<<std::endl;
			    A a;
			    //B b;               
			    B *ptr =(B *)&a;
			    
			    ptr->foo();
			    
			    ptr->fuu();
	   
			}
		}

		void test11()
		{
			//test_model_design_factory::test();
			//test_model_design_prototype::test();
			//test_model_design_builder::test();
			//test_deadline_timer::test();
			//test_json_parser::test();
			//test_design_model_flyweight::test();
			//test_design_model_state::test();
			//test_design_model_composite::test();
			//test_design_model_chainofresponsibility::test();
			//test_design_model_visitor::test();
			//test_design_model_interpreter::test();
			//test_observer_thread_safe::test();
			//test_weak_ptr::test();
			//test_using_nonrecursive_mutex::test();
			//test_dead_lock::test();
			//test_exit_thread::test();
			//test_muduo_asio_timer::test();
			//test_muduo_multithread_timer::test();
			//test_muduo_multithread_timer_shortcritical_section::test();
			//test_round_trip::test();
			//test_timing_wheel_idleconnection::test();
			//test_down_cast::test();
			//test_intrusive_ptr::test();
			test_intrusive_ptr2::test();
		}
		namespace test_timing_wheel_idleconnection
		{
			using namespace muduo;
			using namespace muduo::net;
			echo_server::echo_server(muduo::net::EventLoop* loop,const muduo::net::InetAddress& la,int idle_seconds):m_server(loop,la,"echo_server"),m_connection_buckets(idle_seconds)
			{
				m_server.setConnectionCallback(boost::bind(&echo_server::on_connection,this,_1));
				m_server.setMessageCallback(boost::bind(&echo_server::on_message,this,_1,_2,_3));
				loop->runEvery(1,boost::bind(&echo_server::on_timer,this));
				//m_connection_buckets.resize(idle_seconds);
				dump_connection_buckets();
			}
			void echo_server::start()
			{
				m_server.start();
			}
		
			void echo_server::on_connection(const muduo::net::TcpConnectionPtr& conn)
			{
				LOG_INFO<< "EchoServer - " << conn->peerAddress().toIpPort() << " -> "<< conn->localAddress().toIpPort() << " is "<< (conn->connected() ? "UP" : "DOWN");
				if(conn->connected())
				{
					entry_ptr en(new entry(conn));
					m_connection_buckets.back().insert(en);
					dump_connection_buckets();
					weak_entry_ptr we(en);
					conn->setContext(we);
				}
				else
				{
					weak_entry_ptr we(boost::any_cast<weak_entry_ptr>(conn->getContext()));
					LOG_INFO<<we.use_count();
				}
				
			}
			void echo_server::on_message(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf,muduo::Timestamp time)
			{
				muduo::string msg(buf->retrieveAllAsString());
				  LOG_INFO << conn->name() << " echo " << msg.size()
				           << " bytes at " << time.toString();
				  conn->send(msg);

				  assert(!conn->getContext().empty());
				  weak_entry_ptr weakEntry(boost::any_cast<weak_entry_ptr>(conn->getContext()));
				  entry_ptr entrys(weakEntry.lock());
				  if (entrys)
				  {
				    m_connection_buckets.back().insert(entrys);
				    dump_connection_buckets();
				  }
			}
			void echo_server::on_timer()
			{
			  m_connection_buckets.push_back(bucket());
			  dump_connection_buckets();
			}
			void echo_server::dump_connection_buckets()const
			{
			  LOG_INFO << "size = " << m_connection_buckets.size();
			  int idx = 0;
			  for (weak_connection_list::const_iterator bucketI = m_connection_buckets.begin();
			      bucketI != m_connection_buckets.end();
			      ++bucketI, ++idx)
			  {
			    const bucket& bu = *bucketI;
			    printf("[%d] len = %zd : ", idx, bu.size());
			    for (bucket::const_iterator it = bu.begin();
			        it != bu.end();
			        ++it)
			    {
			      bool connectionDead = (*it)->m_weak_conn.expired();
			      printf("%p(%ld)%s, ", get_pointer(*it), it->use_count(),
			          connectionDead ? " DEAD" : "live");
			    }
			    puts("");
			  }
			}
			void test()
			{
				EventLoop loop;
			  InetAddress listenAddr(2007);
			  int idleSeconds = 10;
			  
			  LOG_INFO << "pid = " << getpid() << ", idle seconds = " << idleSeconds;
			  echo_server server(&loop, listenAddr, idleSeconds);
			  server.start();
			  loop.loop();
			}
		}
		namespace test_round_trip
		{
			using namespace muduo;
			using namespace muduo::net;
			const size_t frameLen = 2*sizeof(int64_t);

			void serverConnectionCallback(const TcpConnectionPtr& conn)
			{
			  LOG_TRACE << conn->name() << " " << conn->peerAddress().toIpPort() << " -> "
			        << conn->localAddress().toIpPort() << " is "
			        << (conn->connected() ? "UP" : "DOWN");
			  if (conn->connected())
			  {
			    conn->setTcpNoDelay(true);
			  }
			  else
			  {
			  }
			}

			void serverMessageCallback(const TcpConnectionPtr& conn,
			                           muduo::net::Buffer* buffer,
			                           muduo::Timestamp receiveTime)
			{
			  int64_t message[2];
			  while (buffer->readableBytes() >= frameLen)
			  {
			    memcpy(message, buffer->peek(), frameLen);
			    buffer->retrieve(frameLen);
			    message[1] = receiveTime.microSecondsSinceEpoch();
			    conn->send(message, sizeof message);
			  }
			}

			void runServer(uint16_t port)
			{
			  EventLoop loop;
			  TcpServer server(&loop, InetAddress(port), "ClockServer");
			  server.setConnectionCallback(serverConnectionCallback);
			  server.setMessageCallback(serverMessageCallback);
			  server.start();
			  loop.loop();
			}

			TcpConnectionPtr clientConnection;

			void clientConnectionCallback(const TcpConnectionPtr& conn)
			{
			  LOG_TRACE << conn->localAddress().toIpPort() << " -> "
			        << conn->peerAddress().toIpPort() << " is "
			        << (conn->connected() ? "UP" : "DOWN");
			  if (conn->connected())
			  {
			    clientConnection = conn;
			    conn->setTcpNoDelay(true);
			  }
			  else
			  {
			    clientConnection.reset();
			  }
			}

			void clientMessageCallback(const TcpConnectionPtr&,
			                           muduo::net::Buffer* buffer,
			                           muduo::Timestamp receiveTime)
			{
			  int64_t message[2];
			  while (buffer->readableBytes() >= frameLen)
			  {
			    memcpy(message, buffer->peek(), frameLen);
			    buffer->retrieve(frameLen);
			    int64_t send = message[0];
			    int64_t their = message[1];
			    int64_t back = receiveTime.microSecondsSinceEpoch();
			    int64_t mine = (back+send)/2;
			    LOG_INFO << "round trip " << back - send
			             << " clock error " << their - mine;
			  }
			}

			void sendMyTime()
			{
			  if (clientConnection)
			  {
			    int64_t message[2] = { 0, 0 };
			    message[0] = Timestamp::now().microSecondsSinceEpoch();
			    clientConnection->send(message, sizeof message);
			  }
			}

			void runClient(const char* ip, uint16_t port)
			{
			  EventLoop loop;
			  TcpClient client(&loop, InetAddress(ip, port), "ClockClient");
			  client.enableRetry();
			  client.setConnectionCallback(clientConnectionCallback);
			  client.setMessageCallback(clientMessageCallback);
			  client.connect();
			  loop.runEvery(0.2, sendMyTime);
			  loop.loop();
			}
			void testHash()
			{
			  boost::hash<boost::shared_ptr<int> > h;
			  boost::shared_ptr<int> x1(new int(10));
			  boost::shared_ptr<int> x2(new int(10));
			  h(x1);
			  assert(h(x1) != h(x2));
			  x1 = x2;
			  assert(h(x1) == h(x2));
			  x1.reset();
			  assert(h(x1) != h(x2));
			  x2.reset();
			  assert(h(x1) == h(x2));
			}
			void test()
			{
				// muduo::Thread t1(boost::bind(runServer, 4321));
				// muduo::Thread t2(boost::bind(runClient, "127.0.0.1",4321));
				// t1.start();
				// t2.start();
				// t1.join();
				// t2.join();	
				testHash();			
			}
		}
		namespace test_muduo_multithread_timer_shortcritical_section
		{
			
			printer::printer(muduo::net::EventLoop* loop1,muduo::net::EventLoop* loop2):m_loop1(loop1),m_loop2(loop2),m_count(0)
			{
				m_loop1->runAfter(1,boost::bind(&printer::print1,this));
				m_loop2->runAfter(1,boost::bind(&printer::print2,this));
			}
			
			void printer::print1()
			{
				int count=0;
				bool quit=false;
				{
					muduo::MutexLockGuard lo(m_mutex);
					if(m_count<10)
					{
						count=m_count;
						++m_count;	
					}
					else
					{
						quit=true;
					}
				}
				if(!quit)
				{
					LOG_INFO<<count;
					m_loop1->runAfter(1,boost::bind(&printer::print1,this));
				}
				else
				{
					m_loop1->quit();
				}
			}
			void printer::print2()
			{
				int count=0;
				bool quit=false;
				{
					muduo::MutexLockGuard lo(m_mutex);
					if(m_count<10)
					{
						count=m_count;
						++m_count;	
					}
					else
					{
						quit=true;
					}
				}
				if(!quit)
				{
					LOG_INFO<<count;
					m_loop2->runAfter(1,boost::bind(&printer::print2,this));
				}
				else
				{
					m_loop2->quit();
				}
			}
		
			void test()
			{
				boost::scoped_ptr<printer> p;
				muduo::net::EventLoop loop;
				muduo::net::EventLoopThread loop_thread;
				muduo::net::EventLoop* loop2=loop_thread.startLoop();
				p.reset(new printer(&loop,loop2));
				loop.loop();
			}
		}
		namespace test_muduo_multithread_timer
		{
			
			printer::printer(muduo::net::EventLoop* loop1,muduo::net::EventLoop* loop2):m_loop1(loop1),m_loop2(loop2),m_count(0)
			{
				m_loop1->runAfter(1,boost::bind(&printer::print1,this));
				m_loop2->runAfter(1,boost::bind(&printer::print2,this));
			}
			
			void printer::print1()
			{
				muduo::MutexLockGuard lo(m_mutex);
				if(m_count<10)
				{
					LOG_INFO<<m_count;
					++m_count;
					m_loop1->runAfter(1,boost::bind(&printer::print1,this));
				}
				else
				{
					m_loop1->quit();
				}
			}
			void printer::print2()
			{
				muduo::MutexLockGuard lo(m_mutex);
				if(m_count<10)
				{
					LOG_INFO<<m_count;
					++m_count;
					m_loop2->runAfter(1,boost::bind(&printer::print2,this));
				}
				else
				{
					m_loop2->quit();
				}
			}
		
			void test()
			{
				boost::scoped_ptr<printer> p;
				muduo::net::EventLoop loop;
				muduo::net::EventLoopThread loop_thread;
				muduo::net::EventLoop* loop2=loop_thread.startLoop();
				p.reset(new printer(&loop,loop2));
				loop.loop();
			}
		}
		namespace test_muduo_asio_timer
		{
			
			printer::printer(muduo::net::EventLoop* loop):m_loop(loop),m_count(0)
			{
				m_loop->runAfter(1,boost::bind(&printer::print,this));
			}
		
			void printer::print()
			{
				if(m_count<5)
				{
					LOG_INFO<<m_count;
					++m_count;
					m_loop->runAfter(1,boost::bind(&printer::print,this));
				}
				else
				{
					m_loop->quit();
				}
			}
		
			void test()
			{
				muduo::net::EventLoop loop;
				printer p(&loop);
				loop.loop();
			}

		}
		namespace test_exit_thread
		{	
			american_calendar ac;
			british_calendar bc;
			bool american_calendar::is_holiday(const string& )const
			{
				return true;
			}
			bool british_calendar::is_holiday(const string&)const
			{

				return true;
			}
			calendar& get_calendar()
			{
				british_calendar* b=new british_calendar();
				return *b;
			}
			
			void test()
			{
				calendar& c=get_calendar();
				exit(0);
				if(c.is_holiday("yes"))
				{
					LOG_INFO<<"is_holiday";
				}
			}
			
		}
		namespace test_dead_lock
		{
			inventory g_inventory;
			void inventory::add(request* req)
			{
				muduo::MutexLockGuard lo(m_mutex);
				m_requests.insert(req);
			}
			void inventory::remove(request* req)
			{
				muduo::MutexLockGuard lo(m_mutex);
				m_requests.erase(req);
			}
			void inventory::print_all()const
			{
				muduo::MutexLockGuard lo(m_mutex);
				sleep(1);
				for(auto& i:m_requests)
				{
					i->print();
				}
				LOG_INFO<<"all unlocked";
			}
		
			void request::process()
			{
				muduo::MutexLockGuard lo(m_mutex);
				LOG_INFO<<"process";
				g_inventory.add(this);
			}
			void request::print()const
			{
				muduo::MutexLockGuard lo(m_mutex);
				LOG_INFO<<"print";
			}
			request::~request()
			{
				muduo::MutexLockGuard lo(m_mutex);
				sleep(1);
				g_inventory.remove(this);
				LOG_INFO<<"request destructor";
			
			}
			void thread_func()
			{
				request* req=new request;
				req->process();
				delete req;
				//g_inventory.print_all();
			}
			void test()
			{
				// request r;
				// r.process();
				muduo::Thread t(thread_func);
				t.start();
				///usleep(5000*1000);
				sleep(3);
				g_inventory.print_all();
				t.join();
			}
		}



	namespace test_thread_safe_counter
	{

		int64_t counter::value()const
		{
			muduo::MutexLockGuard lock(m_mutex);
			return m_value;
		}
		int64_t counter::get_increase()
		{
			muduo::MutexLockGuard lock(m_mutex);
			int64_t ret=m_value++;
			return ret;
		}
		
		void test()
		{

		}
	}
	namespace test_observer_thread_safe
	{
		void observer::observe(observable* s)
		{
			s->register1(shared_from_this());
			m_subject=s;
		}
		
		//void observable::register1(const boost::weak_ptr<observer>& x)
		void observable::register1(const boost::shared_ptr<observer>& x)
		{
			m_observers.push_back(x);
		}
		void observable::notify()
		{
			muduo::MutexLockGuard lock(m_mutex);
			auto it=m_observers.begin();
			while(it!=m_observers.end())
			{
				//boost::shared_ptr<observer> obj(it->lock());
				boost::shared_ptr<observer> obj=*it;
				if(obj)
				{
					obj->update();
					++it;
				}
				else
				{
					LOG_INFO<<"erase observer";
					it=m_observers.erase(it);
				}
			}
		}
		
		void foo::update()
		{
			LOG_INFO<<"FOO update:"<<(size_t)this;
		}
		
		void test()
		{
			{
				observable sub;
				{
					boost::shared_ptr<foo> p(new foo());
					p->observe(&sub);
					sub.notify();
				}
				sub.notify();
			}
			LOG_INFO<<"after observable destructor";
			//sub 析构后，observer会不会调用析构函数？
			
		}
	}
	namespace test_weak_ptr
	{
		
		boost::shared_ptr<stock> stock_factory::get(const string& key)
		{
			boost::shared_ptr<stock> p;
			muduo::MutexLockGuard lock(m_mutex);
			boost::weak_ptr<stock>& wk_stock=m_stocks[key];
			p=wk_stock.lock();
			if(!p)
			{
				p.reset(new stock(key),boost::bind(&stock_factory::weak_delete_stock,boost::weak_ptr<stock_factory>(shared_from_this()),_1));
				wk_stock=p;
			}
			return p;
		}
	
		void stock_factory::weak_delete_stock(const boost::weak_ptr<stock_factory>& wk,stock* s)
		{
			LOG_INFO<<"delete stock:"<<(intptr_t)s;
			boost::shared_ptr<stock_factory> f(wk.lock());
			if(f)
			{
				f->remove_stock(s);
			}
			else
			{
				LOG_INFO<<"factory died";
			}
			delete s;
		}

		void stock_factory::remove_stock(stock* s)
		{
			if(s)
			{
				muduo::MutexLockGuard lock(m_mutex);
				m_stocks.erase(s->get_key());
			}
		}
		void testLongLifeFactory()
		{
			boost::shared_ptr<stock_factory> fa(new stock_factory);
			{
				boost::shared_ptr<stock> s1=fa->get("nyse");
				boost::shared_ptr<stock> s2=fa->get("nyse");

			}
		}
		void testShortLifeFactory()
		{
			boost::shared_ptr<stock> s;
			{
				boost::shared_ptr<stock_factory> f(new stock_factory);
				s=f->get("nyse");
				boost::shared_ptr<stock> s1=f->get("nyse");

			}
			
		}
		void test()
		{
			 testLongLifeFactory();
			 testShortLifeFactory();
		}
	}
	namespace test_using_nonrecursive_mutex
	{
		muduo::MutexLock mutex;
		//std::recursive_mutex mutex;
		std::vector<foo> foos;
		void post(const foo& f)
		{
			muduo::MutexLockGuard lock(mutex);
			//std::lock_guard<recursive_mutex> l(mutex);
			foos.push_back(f);
		}
		void traverse()
		{
			muduo::MutexLockGuard lock(mutex);
			//std::lock_guard<recursive_mutex> l(mutex);
			for(auto& i:foos)
			{
				i.doit();
			}
		}


		void test()
		{
			foo f1;
			post(f1);
			foo f2;
			post(f2);
			traverse();
			LOG_INFO<<foos.size();
		}

	}
	
}