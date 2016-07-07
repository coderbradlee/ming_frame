#include "Curl.h"
#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <stdio.h>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <stdio.h>
#include <sstream>
using namespace muduo::net;

EventLoop* g_loop = NULL;
std::string temp;
void onData(const char* data, int len)
{
  printf("len %d\n", len);
  temp.append(data,len);
}

void done(curl::Request* c, int code)
{
  printf("done %p %s %d\n", c, c->getEffectiveUrl(), code);
  std::cout<<temp<<":"<<__FILE__<<":"<<__LINE__<<std::endl;
}

int main(int argc, char* argv[])
{
  EventLoop loop;
  g_loop = &loop;
  loop.runAfter(30.0, boost::bind(&EventLoop::quit, &loop));
  curl::Curl::initialize(curl::Curl::kCURLssl);
  curl::Curl curl(&loop);

  //curl::RequestPtr req = curl.getUrl("http://apilayer.net/api/live?access_key=beed451506493436d5a5ec0966b5e72a");
  curl::RequestPtr req = curl.getUrl("hhh");
  req->setDataCallback(onData);
  req->setDoneCallback(done);

  loop.loop();
}
