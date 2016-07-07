#include "log.hpp"

int main()
{
  try
  {
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();
    muduo::ThreadPool pool("pool");
    pool.start(5);
    for(int i=0;i<5;++i)
      pool.run([](){LOG_INFO<<"info";sleep(1);});
    LOG_DEBUG<<"DEBUG";




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