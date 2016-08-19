#include <boost/program_options.hpp>
#include "../log.hpp"
#include "../fastcgi/fastcgi_resource.h"
#include "thailand_month_report.hpp"
using std::string;
using std::cout;
using std::endl;
void start_inspector_thread();

int main(int argc, char* argv[])
{
  try
  {
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();

    start_report();
    muduo::Timestamp end = muduo::Timestamp::now();
    printf("%f\n", timeDifference(end, start));
    sleep(10);
  }
  catch (std::exception& e)
  {
    //cout << diagnostic_information(e) << endl;
    cout << e.what() << endl;
  }
  catch (...)
  {
    cout << "unknown error" << endl;
  }
  return 0;
}