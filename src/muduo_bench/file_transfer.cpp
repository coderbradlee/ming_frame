#include <muduo/net/TcpServer.h>

#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>

#include <utility>

#include <mcheck.h>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;
void on_water_mark(const TcpConnectionPtr& conn,size_t len)
{
  LOG_INFO<<"water mark "<<len;
}
const int kBufSize=64*1024;
const char* g_file=nullptr;
typedef boost::shared_ptr<FILE> file_ptr;
void on_connection(const TcpConnectionPtr& conn)
{
  if(conn->connected())
  {
    conn->setHighWaterMarkCallback(on_water_mark,kBufSize+1);
    FILE* fp=::fopen(g_file,"rb");
    if(fp)
    {
      file_ptr ctx(fp,::fclose);
      conn->setContext(ctx);
      char buf[kBufSize];
      size_t nread=::fread(buf,1,sizeof buf,fp);
      conn->send(buf,static_cast<int>(nread));
    }
    else
    {
      conn->shutdown();
      LOG_INFO<<"shutdown";
    }
  }
}
void on_write_complete(const TcpConnectionPtr& conn)
{
  LOG_INFO<<"on_write_complete";
  const file_ptr& fp=boost::any_cast<const file_ptr&>(conn->getContext());
  char buf[kBufSize];
  size_t nread=::fread(buf,1,sizeof buf,get_pointer(fp));
  if(nread>0)
  {
    conn->send(buf,static_cast<int>(nread));
  }
  else
  {
    conn->shutdown();
    LOG_INFO<<"done";
  }
}
int main(int argc, char* argv[])
{
  if(argc>1)
  {
    g_file=argv[1];
    EventLoop loop;
    InetAddress listenAddr(2021);
    TcpServer server(&loop,listenAddr,"fileserver");
    server.setConnectionCallback(on_connection);
    server.setWriteCompleteCallback(on_write_complete);
    server.start();
    loop.loop();
  }
}
