#include "log.hpp"

int main()
{
  try
  {
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();


    LOG_INFO << "Hello 0123456789";







    muduo::Timestamp end = muduo::Timestamp::now();
    printf("%f\n", timeDifference(end, start)*1000000/kBatch);
    struct timespec ts = { 0, 500*1000*1000 };
    nanosleep(&ts, NULL);
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