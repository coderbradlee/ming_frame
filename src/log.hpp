#ifndef LOG_HPP
#define LOG_HPP

#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>

#include <stdio.h>
#include <sys/resource.h>
#include "config.hpp"
//int kRollSize = 50*1000*1000;
size_t kRollSize=boost::lexical_cast<int>(get_config->m_log_size)*1000*1000;
muduo::AsyncLogging* g_asyncLog = NULL;

void asyncOutput(const char* msg, int len)
{
  g_asyncLog->append(msg, len);
}

// void bench(bool longLog)
// {
//   muduo::Logger::setOutput(asyncOutput);

//   int cnt = 0;
//   const int kBatch = 1000000;
//   muduo::string empty = " ";
//   muduo::string longStr(3000, 'X');
//   longStr += " ";

//   for (int t = 0; t < 1; ++t)
//   {
//     muduo::Timestamp start = muduo::Timestamp::now();
//     for (int i = 0; i < kBatch; ++i)
//     {
//       LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz "
//                << (longLog ? longStr : empty)
//                << cnt;
//       ++cnt;
//     }
//     muduo::Timestamp end = muduo::Timestamp::now();
//     printf("%f\n", timeDifference(end, start)*1000000/kBatch);
//     struct timespec ts = { 0, 500*1000*1000 };
//     nanosleep(&ts, NULL);
//   }
// }

void init_log()
{
    size_t kOneGB = 1000*1024*1024;
    rlimit rl = { 2*kOneGB, 2*kOneGB };
    setrlimit(RLIMIT_AS, &rl);
 
  muduo::Logger::setOutput(asyncOutput);
  muduo::string name=get_config->m_log_name;
  muduo::AsyncLogging log(name, kRollSize);
  log.start();
  g_asyncLog = &log;

}
#endif