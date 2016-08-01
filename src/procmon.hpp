#ifndef PROCMON_HPP
#define PROCMON_HPP

#include "plot.h"

#include <muduo/base/FileUtil.h>
#include <muduo/base/ProcessInfo.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/http/HttpServer.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <sstream>
#include <stdarg.h>
#include <stdio.h>

// TODO:
// - what if process exits?
//

// Represent parsed /proc/pid/stat
struct StatData
{
  void parse(const char* startAtState, int kbPerPage);
  
  // int pid;
  char state;
  int ppid;
  int pgrp;
  int session;
  int tty_nr;
  int tpgid;
  int flags;

  long minflt;
  long cminflt;
  long majflt;
  long cmajflt;

  long utime;
  long stime;
  long cutime;
  long cstime;

  long priority;
  long nice;
  long num_threads;
  long itrealvalue;
  long starttime;

  long vsizeKb;
  long rssKb;
  long rsslim;
};

BOOST_STATIC_ASSERT(boost::is_pod<StatData>::value);

class Procmon : boost::noncopyable
{
 public:
  Procmon(muduo::net::EventLoop* loop, pid_t pid, uint16_t port, const char* procname);

  void start();

 private:

  muduo::string getName() const;

  void onRequest(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* resp);

  void fillOverview(const muduo::string& query);

  void fillRefresh(const muduo::string& query);

  void fillThreads();

  muduo::string readProcFile(const char* basename);

  muduo::string readLink(const char* basename);

  int appendResponse(const char* fmt, ...) __attribute__ ((format (printf, 2, 3)));

  void appendTableRow(const char* name, long value)
  {
    appendResponse("<tr><td>%s</td><td>%ld</td></tr>\n", name, value);
  }

  void appendTableRowFloat(const char* name, double value)
  {
    appendResponse("<tr><td>%s</td><td>%.2f</td></tr>\n", name, value);
  }

  void appendTableRow(const char* name, muduo::StringArg value)
  {
    appendResponse("<tr><td>%s</td><td>%s</td></tr>\n", name, value.c_str());
  }

  muduo::string getCmdLine()
  {
    return boost::replace_all_copy(readProcFile("cmdline"), muduo::string(1, '\0'), "\n\t");
  }

  muduo::string getEnviron()
  {
    return boost::replace_all_copy(readProcFile("environ"), muduo::string(1, '\0'), "\n");
  }

  muduo::Timestamp getStartTime(long starttime)
  {
    return muduo::Timestamp(muduo::Timestamp::kMicroSecondsPerSecond * kBootTime_
                     + muduo::Timestamp::kMicroSecondsPerSecond * starttime / kClockTicksPerSecond_);
  }

  double getSeconds(long ticks)
  {
    return static_cast<double>(ticks) / kClockTicksPerSecond_;
  }

  void tick();
   
  //
  // static member functions
  //

  static const char* getState(char state)
  {
    // One character from the string "RSDZTW" where R is running, S is sleeping in
    // an interruptible wait, D is waiting in uninterruptible disk sleep, Z is zombie,
    // T is traced or stopped (on a signal), and W is paging.
    switch (state)
    {
      case 'R':
        return "Running";
      case 'S':
        return "Sleeping";
      case 'D':
        return "Disk sleep";
      case 'Z':
        return "Zombie";
      default:
        return "Unknown";
    }
  }

  static long getLong(const muduo::string& status, const char* key);

  static long getBootTime();
  struct CpuTime
  {
    int userTime_;
    int sysTime_;
    double cpuUsage(double kPeriod, double kClockTicksPerSecond) const
    {
      return (userTime_ + sysTime_) / (kClockTicksPerSecond * kPeriod);
    }
  };

  const static int kPeriod_ = 2.0;
  const int kClockTicksPerSecond_;
  const int kbPerPage_;
  const long kBootTime_;  // in Unix-time
  const pid_t pid_;
  muduo::net::HttpServer server_;
  const muduo::string procname_;
  const muduo::string hostname_;
  const muduo::string cmdline_;
  int ticks_;
  StatData lastStatData_;
  boost::circular_buffer<CpuTime> cpu_usage_;
  Plot cpu_chart_;
  Plot ram_chart_;
  // scratch variables
  muduo::net::Buffer response_;
};

// define outline for __attribute__
int Procmon::appendResponse(const char* fmt, ...);

bool processExists(pid_t pid);
#endif
