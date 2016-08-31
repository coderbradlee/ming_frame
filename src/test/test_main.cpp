#include <boost/program_options.hpp>
#include "../log.hpp"

#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/inspect/Inspector.h>

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/noncopyable.hpp>
#include "../procmon.hpp"
#include "test2.hpp"
//#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    init_log();
    LOG_INFO << argv[0] << " [number of IO threads] [number of worker threads] [-n]";
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  
    test2_namespace::test_out();
    sleep(10);
   
}

