#include <boost/program_options.hpp>
#include "log.hpp"
#include "fastcgi/fastcgi_resource.h"
using std::string;
using std::cout;
using std::endl;
extern boost::shared_ptr<iconfig> get_config;
int start_inspector_thread();
namespace po = boost::program_options; 
bool parseCommandLine(int argc, char* argv[])
{
    cout << "12" << endl;
    po::options_description general("general options"); 
    general.add_options()  
        ("help,h", "produce help message")
        ("config", po::value<string>()->default_value("config.ini"),  
        "set config file");  

    po::variables_map vm;  
    po::store(po::parse_command_line(argc, argv,general), vm);   
    po::notify(vm); 
    if (vm.count("help"))  
    {  
        cout << general << endl;  
        return false;  
    }  
  
    if (vm.count("config"))  
    {  
        string conf_name = vm["config"].as<string>();  
        LOG_INFO<<conf_name;
        //ifstream ifs_config(conf_name.c_str());  
        //boost::shared_ptr<iconfig> get_config= iconfig::get_instance(conf_name);
        //get_config= iconfig::get_instance(conf_name);
        // if (! ifs_config)  
        // {  
        //     cerr << "could not open the configure file" << endl;  
        //     return false;  
        // }  
  
        // stringstream ss_config;  
        // ss_config << ifs_config.rdbuf();  
  
        // global::strings_t args;  
        // global::separate_tokens(ss_config.str(), args, " \r\n");  
        // po::store(po::command_line_parser(args).options(all).run(), vm);  
    }  
     return true;
  
}
int main(int argc, char* argv[])
{
  try
  {
    if (parseCommandLine(argc, argv))
    {

    }
    init_log();
    muduo::Timestamp start = muduo::Timestamp::now();

    //start_fastcgi();

    test1::test1();
    //short_url::test();
    start_inspector_thread();
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