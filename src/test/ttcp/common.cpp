#include "common.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <netdb.h>
#include <stdio.h>
namespace po=boost::program_options;
bool parseCommandLine(int argc,char* argv[],Options* opt)
{
	po::options_description desc("allowed options");
	desc.add_options()
	("help,h","Help")
	("port,p",po::value<uint16_t>(&opt->port)->default_value(5001),"tcp port")
	("length,l",po::value<int>(&opt->length)->default_value(65536),"buffer length")
	("number,n",po::value<int>(&opt->number)->default_value(8192),"number of buffers")
	("trans,t",po::value<std::string>(&opt->host),"transmit")
	("receive,r","receive")
	("nodelay,d","set TCP_NODEALY");
	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);
	po::notify(vm);
	opt->transmit=vm.count("trans");
	opt->receive=vm.count("receive");
	opt->nodelay=vm.count("nodelay");
	if(vm.count("help"))
	{
		std::cout<<desc<<std::endl;
		return false;
	}
	if(opt->transmit==opt->receive)
	{
		std::cout<<"either -t or -r must be specified."<<std::endl;
	}
	printf("port=%d\n",opt->port );
	if(opt->transmit)
	{
		printf("buffer length=%d\n",opt->length );
		printf("number of buffers=%d\n",opt->number );
	}
	else
	{
		printf("%s\n", "accepting...\n");
	}
	return true;
}
#pragma GCC diagnostic ignored "-Wold-style-cast"
struct sockaddr_in resolveOrDie(const char* host,uint16_t port)
{
	struct hostent* he=::gethostname(host);
	if(!he)
	{
		perror("gethostname");
		exit(1);
	}
	assert(he->h_addrtype==AF_INET&&he->h_length==sizeof(uint32_t));
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr=*reinterpret_cast<struct in_addr*>(he->h_addr);
	return addr;
}