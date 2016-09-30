#include <muduo/net/Buffer.h>
#include "webSocketContext.h"

using namespace muduo;
using namespace muduo::net;

bool webSocketContext::processOpenLine(const char* begin, const char* end)
{
  bool succeed = false;
  const char* start = begin;
  const char* space = std::find(start, end, ' ');
  if (space != end && request_.setMethod(start, space))
  {
    start = space+1;
    space = std::find(start, end, ' ');
    if (space != end)
    {
      const char* question = std::find(start, space, '?');
      if (question != space)
      {
        request_.setPath(start, question);
        request_.setQuery(question, space);
      }
      else
      {
        request_.setPath(start, space);
      }
      start = space+1;
      succeed = end-start == 8 && std::equal(start, end-1, "HTTP/1.");
      if (succeed)
      {
        if (*(end-1) == '1')
        {
          request_.setVersion(webSocketRequest::kHttp11);
        }
        else if (*(end-1) == '0')
        {
          request_.setVersion(webSocketRequest::kHttp10);
        }
        else
        {
          succeed = false;
        }
      }
    }
  }
  return succeed;
}

// return false if any error
bool webSocketContext::parseOpen(Buffer* buf, Timestamp receiveTime)
{
  bool ok = true;
  bool hasMore = true;
  while (hasMore)
  {
    if (state_ == kExpectRequestLine)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        ok = processOpenLine(buf->peek(), crlf);
        if (ok)
        {
          request_.setReceiveTime(receiveTime);
          buf->retrieveUntil(crlf + 2);
          state_ = kExpectHeaders;
        }
        else
        {
          hasMore = false;
        }
      }
      else
      {
        hasMore = false;
      }
    }
    else if (state_ == kExpectHeaders)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        const char* colon = std::find(buf->peek(), crlf, ':');
        if (colon != crlf)
        {
          request_.addHeader(buf->peek(), colon, crlf);
        }
        else
        {
          // empty line, end of header
          // FIXME:
          state_ = kGotAll;
          hasMore = false;
        }
        buf->retrieveUntil(crlf + 2);
      }
      else
      {
        hasMore = false;
      }
    }
    else if (state_ == kExpectBody)
    {
      // FIXME:
    }
  }
  //buf->retrieveAllAsString();
  std::cout <<buf->retrieveAllAsString()<<":"<< __LINE__<<":" <<__FILE__ << std::endl;
  return ok;
}
bool webSocketContext::parseMessage(Buffer* buf, Timestamp receiveTime)
{
  unsigned char fin_rsv_opcode=readInt8();
  unsigned char first_bytes=readInt8();
  if(first_bytes<128) 
  {
    const std::string reason="message from client not masked";
    return false;
  }
  size_t length=(first_bytes&127);
  if(length==126) 
  {
    size_t content_length=readInt8()<<8+readInt8();
    std::cout <<content_length<<":"<< __LINE__<<":" <<__FILE__ << std::endl;
  }
  std::cout <<buf->peek()<<":"<< __LINE__<<":" <<__FILE__ << std::endl;
  return true;
}