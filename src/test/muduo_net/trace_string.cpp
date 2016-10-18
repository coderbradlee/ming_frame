#include <iostream>
#include <inttypes.h>
#include <stdio.h>
#define __STDC_FORMAT_MACROS

EventLoop* g_loop = NULL;

int main(int argc, char* argv[])
{
  std::string s("xx");
  int64_t  x=100;
  printf("%" PRId64 "\n",x);
  printf("%06" PRId64 "\n",x );
}
