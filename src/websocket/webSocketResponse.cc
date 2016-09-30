// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "webSocketResponse.h"
#include <muduo/net/Buffer.h>

#include <stdio.h>
#include <iostream>
using namespace muduo;
using namespace muduo::net;
void appendWebsocketHeaderToBuffer(Buffer* output) const
{
  size_t length=body_.length();
  //response.put(129);
  output->append(129);
  //unmasked (first length byte<128)
  if(length>=126) 
  {
      int num_bytes;
      if(length>0xffff) 
      {
          num_bytes=8;
          //response.put(127);
          output->append(127);
      }
      else 
      {
          num_bytes=2;
          output->append(126);
      }
      
      for(int c=num_bytes-1;c>=0;c--) 
      {
          output->append((length>>(8*c))%256);
      }
  }
  else
      output->append(length);
  output->append(body_);
  //response << stream.rdbuf();
}
void webSocketResponse::appendToBuffer(Buffer* output) const
{
  char buf[32];
  snprintf(buf, sizeof buf, "HTTP/1.1 %d ", statusCode_);
  //output->append(buf);
  output->append("HTTP/1.1 101 Web Socket Protocol Handshake\r\n");
  //output->append(statusMessage_);
  //output->append("\r\n");

  if (closeConnection_)
  {
    output->append("Connection: close\r\n");
  }
  else
  {
    // snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
    // output->append(buf);
    // output->append("Connection: Keep-Alive\r\n");
  }

  for (std::map<string, string>::const_iterator it = headers_.begin();
       it != headers_.end();
       ++it)
  {
    output->append(it->first);
    output->append(": ");
    output->append(it->second);
    output->append("\r\n");
    //printf("%s:%s\n", it->first,it->second);
    std::cout<<it->first<<":"<<it->second<<std::endl;
  }

  output->append("\r\n");
  output->append(body_);
}
