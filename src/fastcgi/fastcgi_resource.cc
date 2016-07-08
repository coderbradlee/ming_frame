#include "fastcgi_resource.h"

using namespace muduo::net;
void parser_param(
  const muduo::string& uri,
  const muduo::string& query_string,
  const muduo::string& content,
  const TcpConnectionPtr& conn)
{
    std::vector<std::string> params_value_pair;
    boost::split(params_value_pair,query_string , boost::is_any_of("&="));
    for(const auto& p:params_value_pair)
    {
      LOG_INFO << p;
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
      response.append("request ok");
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
   parser_param(uri,query_string,in->retrieveAllAsString(),conn);
  
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
