#include "log.hpp"

int main()
{
  try
  {
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();
    LOG_DEBUG<<"debug";
    LOG_INFO<<"info";
    LOG_ERROR<<"error";




    muduo::Timestamp end = muduo::Timestamp::now();
    printf("%f\n", timeDifference(end, start)*1000000);
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