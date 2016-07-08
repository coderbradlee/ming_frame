#include "fastcgi_resource.h"

using namespace muduo::net;

request_parser_base::request_parser_base(const string& query_string,const string& content):m_content(content)
{
  std::vector<std::string> param_pair;
  boost::split(param_pair,query_string , boost::is_any_of("&"));
  for(auto& p:param_pair)
  {
     std::vector<std::string> one_pair;
     boost::split(one_pair,p , boost::is_any_of("="));
     m_query_string.insert(std::make_pair(one_pair[0],one_pair[1]));
  }
}

request_parser_get::request_parser_get(const string& query_string,const string& content):request_parser_base(query_string,content){}
string request_parser_get::result()
{
    LOG_INFO << m_query_string["source"];
    return "0";
}







void parser_param(
  const muduo::string& uri,
  const muduo::string& request_method,
  const muduo::string& query_string,
  const muduo::string& content,
  const TcpConnectionPtr& conn)
{
    
    //str.compare(4, 4, "soft")
    //uri.compare(0,get_config->m_url.length(),get_config->m_url)
    size_t len=(get_config->m_url).length();
    string url=get_config->m_url;
    string result="0";
    if(request_method=="GET"&&uri.compare(0,len,url) == 0)
    {
        boost::shared_ptr<request_parser_base> pa(new request_parser_get(query_string));
        result=pa->get_result();
    } 
    Buffer response;
    response.append("Context-Type: text/plain\r\n\r\n");
    if (uri.size() == kCells + kPath.size() && uri.find(kPath) == 0)
    {
      response.append(solveSudoku(uri.substr(kPath.size())));
    }
    else
    {
      // FIXME: set http status code 400
      response.append(result);
    }

    FastCgiCodec::respond(&response);
    conn->send(&response);
}

void onRequest(const TcpConnectionPtr& conn,
               FastCgiCodec::ParamMap& params,
               Buffer* in)
{
  muduo::string uri = params["REQUEST_URI"];
  LOG_INFO << conn->name() << ": " << uri;
  muduo::string query_string = params["QUERY_STRING"];
  LOG_INFO << "query_string: " << query_string;
  // for (FastCgiCodec::ParamMap::const_iterator it = params.begin();
  //      it != params.end(); ++it)
  // {
  //   //LOG_DEBUG << it->first << " = " << it->second;
  // }
  if (in->readableBytes() > 0)
   {
      LOG_DEBUG << "stdin " << in->retrieveAllAsString();
   } 
   parser_param(uri,params["REQUEST_METHOD"],query_string,in->retrieveAllAsString(),conn);
  
}

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    typedef boost::shared_ptr<FastCgiCodec> CodecPtr;
    CodecPtr codec(new FastCgiCodec(onRequest));
    conn->setContext(codec);
    conn->setMessageCallback(
        boost::bind(&FastCgiCodec::onMessage, codec, _1, _2, _3));
    conn->setTcpNoDelay(true);
  }
}

void start_fastcgi()
{
  int port = get_config->m_port;
  int threads = get_config->m_threads;
  LOG_INFO <<port<<":"<<threads;
  InetAddress addr(static_cast<uint16_t>(port));
  LOG_INFO << "FastCGI listens on " << addr.toIpPort()
           << " threads " << threads;
#ifdef MING_DEBUG
  std::cout<< "FastCGI listens on " << addr.toIpPort()
           << " threads " << threads<<std::endl;
#endif
  muduo::net::EventLoop loop;
  boost::shared_ptr<TcpServer> server(new TcpServer(&loop, addr, "FastCGI"));
  server->setConnectionCallback(onConnection);
  server->setThreadNum(threads);
  server->start();
  loop.loop();
}
