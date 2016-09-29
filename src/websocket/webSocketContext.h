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
    : state_(kExpectRequestLine),messageState_(kOpen)
  {
  }

  // default copy-ctor, dtor and assignment are fine

  // return false if any error
  bool parseOpen(Buffer* buf, Timestamp receiveTime);
  //bool parseOpen(Timestamp receiveTime);
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
  void setMessageState(messageState ms)
  {
    messageState_=ms;
  }
  messageState getMessageState()const
  {
    return messageState_;
  }
 private:
  bool processOpenLine(const char* begin, const char* end);
  //bool processRequestLine(const char* begin, const char* end);

  webSocketRequestParseState state_;
  webSocketRequest request_;
  enum messageState
  {
    kOpen,
    kMessage,
    kError,
    kClose,
  } messageState_;
};

}
}

#endif  // MUDUO_NET_HTTP_HTTPCONTEXT_H
