#include "log.hpp"
#include "fastcgi_resource.h"
int main()
{
  try
  {
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();
    start_fastcgi();




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