// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef WEBSOCKET_CONTEXT_H
#define WEBSOCKET_CONTEXT_H

#include <muduo/base/copyable.h>
#include <iostream>
#include "webSocketRequest.h"

namespace muduo
{
namespace net
{

class Buffer;

class webSocketContext : public muduo::copyable
{
 public:
  enum webSocketRequestParseState
  {
    kExpectRequestLine,
    kExpectHeaders,
    kExpectBody,
    kGotAll,
  };

  webSocketContext()
    : state_(kExpectRequestLine)
  {
  }

  // default copy-ctor, dtor and assignment are fine

  // return false if any error
  bool parseRequest(Buffer* buf, Timestamp receiveTime);

  bool gotAll() const
  { return state_ == kGotAll; }

  void reset()
  {
    state_ = kExpectRequestLine;
    webSocketRequest dummy;
    request_.swap(dummy);
  }

  const webSocketRequest& request() const
  { return request_; }

  webSocketRequest& request()
  { return request_; }

 private:
  bool processRequestLine(const char* begin, const char* end);

  webSocketRequestParseState state_;
  webSocketRequest request_;
};

}
}

#endif  // MUDUO_NET_HTTP_HTTPCONTEXT_H
