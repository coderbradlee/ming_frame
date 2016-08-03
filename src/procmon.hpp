#ifndef PROCMON_HPP
#define PROCMON_HPP

#include "plot.h"
#include <muduo/base/Mutex.h>
#include <muduo/base/Thread.h>
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
#include <boost/ptr_container/ptr_vector.hpp>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
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

  static const char* getState(char state);
  static long getLong(const muduo::string& status, const char* key);

  static long getBootTime();
  muduo::ProcessInfo::CpuTime getCpuTime(muduo::StringPiece data);
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
int appendResponse(const char* fmt, ...);

bool processExists(pid_t pid);
muduo::StringPiece next(muduo::StringPiece data);
class test_procmon
{
  public:
    test_procmon():g_cycles(0),
    g_percent(82),
    g_busy(false),
    g_cond(g_mutex)
    {
      start();
    }
    void start()
    {
      findCycles();
      boost::ptr_vector<muduo::Thread> threads;
      for (int i = 0; i < 2; ++i)
      {
        threads.push_back(new muduo::Thread(boost::bind(&test_procmon::threadFunc,this)));
        threads.back().start();
      }
          fixed();
        
          //cosine();
        
          //sawtooth();

      g_done.getAndSet(1);
      {
      muduo::MutexLockGuard guard(g_mutex);
      g_busy = true;
      g_cond.notifyAll();
      }
      for (int i = 0; i < 2; ++i)
      {
        threads[i].join();
      }
    }
private:
  double busy(int cycles)
  {
    double result = 0;
    for (int i = 0; i < cycles; ++i)
    {
      result += sqrt(i) * sqrt(i+1);
    }
    return result;
  }

  double getSeconds(int cycles)
  {
    muduo::Timestamp start = muduo::Timestamp::now();
    busy(cycles);
    return timeDifference(muduo::Timestamp::now(), start);
  }

  void findCycles()
  {
    g_cycles = 1000;
    while (getSeconds(g_cycles) < 0.001)
      g_cycles = g_cycles + g_cycles / 4;  // * 1.25
    printf("cycles %d\n", g_cycles);
  }

  void threadFunc()
  {
    while (g_done.get() == 0)
    {
      {
      muduo::MutexLockGuard guard(g_mutex);
      while (!g_busy)
        g_cond.wait();
      }
      busy(g_cycles);
    }
    printf("thread exit\n");
  }

  // this is open-loop control
  void load(int percent)
  {
    percent = std::max(0, percent);
    percent = std::min(100, percent);

    // Bresenham's line algorithm
    int err = 2*percent - 100;
    int count = 0;

    for (int i = 0; i < 100; ++i)
    {
      bool busy = false;
      if (err > 0)
      {
        busy = true;
        err += 2*(percent - 100);
        ++count;
        // printf("%2d, ", i);
      }
      else
      {
        err += 2*percent;
      }

      {
      muduo::MutexLockGuard guard(g_mutex);
      g_busy = busy;
      g_cond.notifyAll();
      }

      muduo::CurrentThread::sleepUsec(10*1000); // 10 ms
    }
    assert(count == percent);
  }

  void fixed()
  {
    while (true)
    {
      load(g_percent);
    }
  }

  void cosine()
  {
    while (true)
      for (int i = 0; i < 200; ++i)
      {
        int percent = static_cast<int>((1.0 + cos(i * 3.14159 / 100)) / 2 * g_percent + 0.5);
        load(percent);
      }
  }

  void sawtooth()
  {
    while (true)
      for (int i = 0; i <= 100; ++i)
      {
        int percent = static_cast<int>(i / 100.0 * g_percent);
        load(percent);
      }
  }
  private:
  int g_cycles = 0;
  int g_percent = 82;
  muduo::AtomicInt32 g_done;
  bool g_busy = false;
  muduo::MutexLock g_mutex;
  muduo::Condition g_cond;
};
#endif
