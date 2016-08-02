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
#include "procmon.hpp"
using namespace muduo;
using namespace muduo::net;

// TODO:
// - what if process exits?
//

// Represent parsed /proc/pid/stat

void StatData::parse(const char* startAtState, int kbPerPage)
{
  // istringstream is probably not the most efficient way to parse it,
  // see muduo-protorpc/examples/collect/ProcFs.cc for alternatives.
  std::istringstream iss(startAtState);

  //            0    1    2    3     4    5       6   7 8 9  11  13   15
  // 3770 (cat) R 3718 3770 3718 34818 3770 4202496 214 0 0 0 0 0 0 0 20
  // 16  18     19      20 21                   22      23      24              25
  //  0 1 0 298215 5750784 81 18446744073709551615 4194304 4242836 140736345340592
  //              26
  // 140736066274232 140575670169216 0 0 0 0 0 0 0 17 0 0 0 0 0 0

  iss >> state;
  iss >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags;
  iss >> minflt >> cminflt >> majflt >> cmajflt;
  iss >> utime >> stime >> cutime >> cstime;
  iss >> priority >> nice >> num_threads >> itrealvalue >> starttime;
  long vsize, rss;
  iss >> vsize >> rss >> rsslim;
  vsizeKb = vsize / 1024;
  rssKb = rss * kbPerPage;
}


Procmon::Procmon(EventLoop* loop, pid_t pid, uint16_t port, const char* procname)
  : kClockTicksPerSecond_(muduo::ProcessInfo::clockTicksPerSecond()),
    kbPerPage_(muduo::ProcessInfo::pageSize() / 1024),
    kBootTime_(getBootTime()),
    pid_(pid),
    server_(loop, InetAddress(port), getName()),
    procname_(ProcessInfo::procname(readProcFile("stat")).as_string()),
    hostname_(ProcessInfo::hostname()),
    cmdline_(getCmdLine()),
    ticks_(0),
    cpu_usage_(600 / kPeriod_),  // 10 minutes
    cpu_chart_(640, 100, 600, kPeriod_),
    ram_chart_(640, 100, 7200, 30)
{
  bzero(&lastStatData_, sizeof lastStatData_);
  server_.setHttpCallback(boost::bind(&Procmon::onRequest, this, _1, _2));
}

void Procmon::start()
{
  tick();
  server_.getLoop()->runEvery(kPeriod_, boost::bind(&Procmon::tick, this));
  server_.start();
}

string Procmon::getName() const
{
  char name[256];
  snprintf(name, sizeof name, "procmon-%d", pid_);
  return name;
}

void Procmon::onRequest(const HttpRequest& req, HttpResponse* resp)
{
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/plain");
  resp->addHeader("Server", "Muduo-Procmon");

  /*
  if (!processExists(pid_))
  {
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
    return;
  }
  */

  if (req.path() == "/")
  {
    resp->setContentType("text/html");
    fillOverview(req.query());
    resp->setBody(response_.retrieveAllAsString());
  }
  else if (req.path() == "/cmdline")
  {
    resp->setBody(cmdline_);
  }
  else if (req.path() == "/cpu.png")
  {
    std::vector<double> cpu_usage;
    for (size_t i = 0; i < cpu_usage_.size(); ++i)
      cpu_usage.push_back(cpu_usage_[i].cpuUsage(kPeriod_, kClockTicksPerSecond_));
    string png = cpu_chart_.plotCpu(cpu_usage);
    resp->setContentType("image/png");
    resp->setBody(png);
  }
  // FIXME: replace with a map
  else if (req.path() == "/environ")
  {
    resp->setBody(getEnviron());
  }
  else if (req.path() == "/io")
  {
    resp->setBody(readProcFile("io"));
  }
  else if (req.path() == "/limits")
  {
    resp->setBody(readProcFile("limits"));
  }
  else if (req.path() == "/maps")
  {
    resp->setBody(readProcFile("maps"));
  }
  // numa_maps
  else if (req.path() == "/smaps")
  {
    resp->setBody(readProcFile("smaps"));
  }
  else if (req.path() == "/status")
  {
    resp->setBody(readProcFile("status"));
  }
  else if (req.path() == "/threads")
  {
    fillThreads();
    resp->setBody("xxx"+response_.retrieveAllAsString());
  }
  else
  {
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
  }
}

void Procmon::fillOverview(const string& query)
{
  response_.retrieveAll();
  Timestamp now = Timestamp::now();
  appendResponse("<html><head><title>%s on %s</title>\n",
                 procname_.c_str(), hostname_.c_str());
  fillRefresh(query);
  appendResponse("</head><body>\n");

  string stat = readProcFile("stat");
  if (stat.empty())
  {
    appendResponse("<h1>PID %d doesn't exist.</h1></body></html>", pid_);
    return;
  }
  int pid = atoi(stat.c_str());
  assert(pid == pid_);
  StringPiece procname = ProcessInfo::procname(stat);
  appendResponse("<h1>%s on %s</h1>\n",
                 procname.as_string().c_str(), hostname_.c_str());
  response_.append("<p>Refresh <a href=\"?refresh=1\">1s</a> ");
  response_.append("<a href=\"?refresh=2\">2s</a> ");
  response_.append("<a href=\"?refresh=5\">5s</a> ");
  response_.append("<a href=\"?refresh=15\">15s</a> ");
  response_.append("<a href=\"?refresh=60\">60s</a>\n");
  response_.append("<p><a href=\"/cmdline\">Command line</a>\n");
  response_.append("<a href=\"/environ\">Environment variables</a>\n");
  response_.append("<a href=\"/threads\">Threads</a>\n");

  appendResponse("<p>Page generated at %s (UTC)", now.toFormattedString().c_str());

  response_.append("<p><table>");
  StatData statData;  // how about use lastStatData_ ?
  bzero(&statData, sizeof statData);
  statData.parse(procname.end()+1, kbPerPage_);  // end is ')'

  appendTableRow("PID", pid);
  Timestamp started(getStartTime(statData.starttime));  // FIXME: cache it;
  appendTableRow("Started at", started.toFormattedString(false /*showMicroseconds*/) + " (UTC)");
  appendTableRowFloat("Uptime (s)", timeDifference(now, started));  // FIXME: format as days+H:M:S
  appendTableRow("Executable", readLink("exe"));
  appendTableRow("Current dir", readLink("cwd"));

  appendTableRow("State", getState(statData.state));
  appendTableRowFloat("User time (s)", getSeconds(statData.utime));
  appendTableRowFloat("System time (s)", getSeconds(statData.stime));

  appendTableRow("VmSize (KiB)", statData.vsizeKb);
  appendTableRow("VmRSS (KiB)", statData.rssKb);
  appendTableRow("Threads", statData.num_threads);
  appendTableRow("CPU usage", "<img src=\"/cpu.png\" height=\"100\" witdh=\"640\">");

  appendTableRow("Priority", statData.priority);
  appendTableRow("Nice", statData.nice);

  appendTableRow("Minor page faults", statData.minflt);
  appendTableRow("Major page faults", statData.majflt);
  // TODO: user

  response_.append("</table>");
  response_.append("</body></html>");
}

void Procmon::fillRefresh(const string& query)
{
  size_t p = query.find("refresh=");
  if (p != string::npos)
  {
    int seconds = atoi(query.c_str()+p+8);
    if (seconds > 0)
    {
      appendResponse("<meta http-equiv=\"refresh\" content=\"%d\">\n", seconds);
    }
  }
}
StringPiece next(StringPiece data)
{
  const char* sp = static_cast<const char*>(::memchr(data.data(), ' ', data.size()));
  if (sp)
  {
    data.remove_prefix(static_cast<int>(sp+1-data.begin()));
    return data;
  }
  return "";
}
ProcessInfo::CpuTime Procmon::getCpuTime(StringPiece data)
{
  ProcessInfo::CpuTime t;

  for (int i = 0; i < 10; ++i)
  {
    data = next(data);
  }
  long utime = strtol(data.data(), NULL, 10);
  data = next(data);
  long stime = strtol(data.data(), NULL, 10);
  const double hz = static_cast<double>(ProcessInfo::clockTicksPerSecond());
  t.userSeconds = static_cast<double>(utime) / hz;
  t.systemSeconds = static_cast<double>(stime) / hz;
  return t;
}
void Procmon::fillThreads()
{
  std::vector<pid_t> threads = ProcessInfo::threads();
  string result = "  TID NAME             S    User Time  System Time\n";
  result.reserve(threads.size() * 64);
  string stat;
  for (size_t i = 0; i < threads.size(); ++i)
  {
    char buf[256];
    int tid = threads[i];
    snprintf(buf, sizeof buf, "/proc/%d/task/%d/stat", ProcessInfo::pid(), tid);
    if (FileUtil::readFile(buf, 65536, &stat) == 0)
    {
      StringPiece name = ProcessInfo::procname(stat);
      const char* rp = name.end();
      assert(*rp == ')');
      const char* state = rp + 2;
      *const_cast<char*>(rp) = '\0';  // don't do this at home
      StringPiece data(stat);
      data.remove_prefix(static_cast<int>(state - data.data() + 2));
      ProcessInfo::CpuTime t = getCpuTime(data);
      snprintf(buf, sizeof buf, "%5d %-16s %c %12.3f %12.3f\n",
               tid, name.data(), *state, t.userSeconds, t.systemSeconds);
      result += buf;
    }
  }
  //return result;
  response_.append(result);
  //response_.retrieveAll();
  // FIXME: implement this
}

string Procmon::readProcFile(const char* basename)
{
  char filename[256];
  snprintf(filename, sizeof filename, "/proc/%d/%s", pid_, basename);
  string content;
  FileUtil::readFile(filename, 1024*1024, &content);
  return content;
}

string Procmon::readLink(const char* basename)
{
  char filename[256];
  snprintf(filename, sizeof filename, "/proc/%d/%s", pid_, basename);
  char link[1024];
  ssize_t len = ::readlink(filename, link, sizeof link);
  string result;
  if (len > 0)
  {
    result.assign(link, len);
  }
  return result;
}


void Procmon::tick()
{
  string stat = readProcFile("stat");  // FIXME: catch file descriptor
  if (stat.empty())
    return;
  StringPiece procname = ProcessInfo::procname(stat);
  StatData statData;
  bzero(&statData, sizeof statData);
  statData.parse(procname.end()+1, kbPerPage_);  // end is ')'
  if (ticks_ > 0)
  {
    CpuTime time;
    time.userTime_ = std::max(0, static_cast<int>(statData.utime - lastStatData_.utime));
    time.sysTime_ = std::max(0, static_cast<int>(statData.stime - lastStatData_.stime));
    cpu_usage_.push_back(time);
  }

  lastStatData_ = statData;
  ++ticks_;
}

//
// static member functions
//

const char* Procmon::getState(char state)
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

long Procmon::getLong(const string& status, const char* key)
{
  long result = 0;
  size_t pos = status.find(key);
  if (pos != string::npos)
  {
    result = ::atol(status.c_str() + pos + strlen(key));
  }
  return result;
}

long Procmon::getBootTime()
{
  string stat;
  FileUtil::readFile("/proc/stat", 65536, &stat);
  return getLong(stat, "btime ");
}

  
// define outline for __attribute__
int Procmon::appendResponse(const char* fmt, ...)
{
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int ret = vsnprintf(buf, sizeof buf, fmt, args);
  va_end(args);
  response_.append(buf);
  return ret;
}

bool processExists(pid_t pid)
{
  char filename[256];
  snprintf(filename, sizeof filename, "/proc/%d/stat", pid);
  return ::access(filename, R_OK) == 0;
}
