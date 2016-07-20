#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThreadPool.h>
#include <muduo/base/Logging.h>

#include <map>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <sys/socket.h>  // SO_REUSEPORT

//using namespace muduo;
using namespace muduo::net;
namespace short_url
{
void onRequest(const HttpRequest& req, HttpResponse* resp)
{
  LOG_INFO << "Headers " << req.methodString() << " " << req.path();
  if (!benchmark)
  {
    const std::map<std::string, std::string>& headers = req.headers();
    for (std::map<std::string, std::string>::const_iterator it = headers.begin();
        it != headers.end();
        ++it)
    {
      LOG_DEBUG << it->first << ": " << it->second;
    }
  }

  // TODO: support PUT and DELETE to create new redirections on-the-fly.

  std::map<std::string, std::string>::const_iterator it = redirections.find(req.path());
  if (it != redirections.end())
  {
    resp->setStatusCode(HttpResponse::k301MovedPermanently);
    resp->setStatusMessage("Moved Permanently");
    resp->addHeader("Location", it->second);
    // resp->setCloseConnection(true);
  }
  else if (req.path() == "/")
  {
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");
    resp->setContentType("text/html");
    std::string now = Timestamp::now().toFormattedString();
    std::map<std::string, std::string>::const_iterator i = redirections.begin();
    std::string text;
    for (; i != redirections.end(); ++i)
    {
      text.append("<ul>" + i->first + " =&gt; " + i->second + "</ul>");
    }

    resp->setBody("<html><head><title>My tiny short url service</title></head>"
        "<body><h1>Known redirections</h1>"
        + text +
        "Now is " + now +
        "</body></html>");
  }
  else if (req.path() == "/favicon.ico")
  {
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");
    resp->setContentType("image/png");
    resp->setBody(std::string(favicon, sizeof favicon));
  }
  else
  {
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
  }
}

int test()
{
  redirections["/1"] = "http://chenshuo.com";
  redirections["/2"] = "http://blog.csdn.net/Solstice";

  int numThreads = 10;
  

#ifdef SO_REUSEPORT
  LOG_WARN << "SO_REUSEPORT";
  EventLoop loop;
  EventLoopThreadPool threadPool(&loop, "shorturl");
  if (numThreads > 1)
  {
    threadPool.setThreadNum(numThreads);
  }
  else
  {
    numThreads = 1;
  }
  threadPool.start();

  boost::ptr_vector<HttpServer> servers;
  for (int i = 0; i < numThreads; ++i)
  {
    servers.push_back(new HttpServer(threadPool.getNextLoop(),
                                     InetAddress(8000),
                                     "shorturl",
                                     TcpServer::kReusePort));
    servers.back().setHttpCallback(onRequest);
    servers.back().getLoop()->runInLoop(
        boost::bind(&HttpServer::start, &servers.back()));
  }
  loop.loop();
#else
  LOG_WARN << "Normal";
  EventLoop loop;
  HttpServer server(&loop, InetAddress(8000), "shorturl");
  server.setHttpCallback(onRequest);
  server.setThreadNum(numThreads);
  server.start();
  loop.loop();
#endif
}
}