#include <boost/program_options.hpp>
#include "log.hpp"
#include "fastcgi/fastcgi_resource.h"
using std::string;
using std::cout;
using std::endl;
boost::shared_ptr<iconfig> get_config;
int start_inspector_thread();
namespace po = boost::program_options; 
bool parseCommandLine(int argc, char* argv[])
{
  po::options_description general("general options");  
    general.add_options()  
        ("help,h", "produce help message");
  
    std::string config_file;  
    po::options_description config("config options");  
    config.add_options()  
        ("config", po::value<string>(&config_file)->default_value("config.ini"),  
        "set config file");  
  
    po::options_description all("All options");  
    all.add(general).add(config);  
  
    po::variables_map vm;  
    po::store(po::command_line_parser(argc, argv,all), vm);   
  
    if (vm.count("help"))  
    {  
        cout << general << endl;  
        cout << config << endl;  
        return false;  
    }  
  
    if (vm.count("config"))  
    {  
        string conf_name = vm["config"].as<string>();  
        LOG_INFO<<conf_name;
        //ifstream ifs_config(conf_name.c_str());  
        //boost::shared_ptr<iconfig> get_config= iconfig::get_instance(conf_name);
        get_config= iconfig::get_instance(conf_name);
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
    po::notify(vm);  
  
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