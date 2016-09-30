#include "../webSocketServer.h"
#include "../webSocketRequest.h"
#include "../webSocketResponse.h"
#include "../modp_base64/base64.h"
#include "../crypto.hpp"
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>

using namespace muduo;
using namespace muduo::net;

extern char favicon[555];
bool benchmark = false;

void onOpen(const webSocketRequest& req, webSocketResponse* resp)
{
  // std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
  // if (!benchmark)
  // {
  //   const std::map<string, string>& headers = req.headers();
  //   for (std::map<string, string>::const_iterator it = headers.begin();
  //        it != headers.end();
  //        ++it)
  //   {
  //     std::cout << it->first << ": " << it->second << std::endl;
  //   }
  // }
  if (req.path() == "/upload")
  {
    // resp->setStatusCode(webSocketResponse::k200Ok);
    // resp->setStatusMessage("OK");
    // resp->setContentType("text/plain");
    // resp->addHeader("Server", "Muduo");
    // resp->setBody("hello, world!\n");
    ////////////////////////////////////////
    std::cout << "build response"<< std::endl;
    auto sha1=Crypto::SHA1(req.getHeader("Sec-WebSocket-Key")+req.get_magic_string());
    resp->setStatusCode(webSocketResponse::k200Ok);
    resp->setStatusMessage("HTTP/1.1 101 Web Socket Protocol Handshake\r\n");
    resp->addHeader("Upgrade", "WebSocket");
    resp->addHeader("Connection", "Upgrade");
    resp->addHeader("Sec-WebSocket-Accept", Crypto::Base64::encode(sha1));
    
  }
  else
  {
    resp->setStatusCode(webSocketResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
  }
}
void onMessage(const webSocketRequest& req, webSocketResponse* resp)
{
  //init
  //#PREPARE#{"action":"UPLOAD_FILE","transfer":"base64","data":{"file":"/SalesOrder/AYYED20160929/Koala.jpg","size":780831,"overwrite":true},"phase":"PREPARE","ts":"2016-8-29 17:53:43"}
  //return
  //{"action":"UPLOAD_FILE","errorCode": 200,"message":"Upload initialized. Wait for data","phase":"PREPARE","ts":"2016-09-29 17:55:53"}
  //{"action":"UPLOAD_FILE","errorCode":200,"message":"write slice ok","phase":"TRANSFER","bytesRead":2591,"ts":"2016-09-29 17:55:54"}
    string output_str=req.getContent();
    string test_ret;
    if (output_str.compare(0, 9, "#PREPARE#") == 0)
    {
      test_ret="{\"action\":\"UPLOAD_FILE\",\"errorCode\": 200,\"message\":\"Upload initialized. Wait for data\",\"phase\":\"PREPARE\",\"ts\":\"2016-09-29 17:55:53\"}";
      std::cout << "clientmessage:" << output_str <<":"<< __LINE__<<":" <<__FILE__ << std::endl;
    }
    else
    {
      string decode_string;
      bool x=Base64Decode(output_str, &decode_string);
      std::cout << "clientmessage:" << decode_string <<":"<< __LINE__<<":" <<__FILE__ << std::endl;
      ///////////////////////////////////////
      int received_size=output_str.length();
      if(received_size<=0)
      {
        resp->setCloseConnection(true);
      }

      test_ret="{\"action\":\"UPLOAD_FILE\",\"errorCode\":200,\"message\":\"write slice ok\",\"phase\":\"TRANSFER\",\"bytesRead\":"+boost::lexical_cast<string>(received_size)+",\"ts\":\"2016-09-29 17:55:54\"}";
    }
    resp->setBody(test_ret);
    // ptree pt;
    // string retString = "";
    // if (clientmessage.compare(0, 9, "#PREPARE#") == 0)
    // {
    //   //************************************************
    //   BOOST_LOG_SEV(server.slg, notification) << "upload client(" << (size_t)connection.get() << "):" << clientmessage;
    //   server.initsink->flush();
    //   //************************************************

    //   clientmessage.erase(0,9);
    //   cout << __LINE__ << ":" << clientmessage << endl;
    //   stringstream stream;
    //   stream << clientmessage;
    //   read_json(stream, pt);
      
    //   string action = pt.get<string>("action");
    //   string transfer = pt.get<string>("transfer");
    //   ptree pdata = pt.get_child("data");
    //   string file = pdata.get<string>("file");
    //   size_t size = pdata.get<size_t>("size");
    //   bool overwrite = pdata.get<bool>("overwrite");
}
void onError(const webSocketRequest& req, webSocketResponse* resp)
{
    
}
void onClose(const webSocketRequest& req, webSocketResponse* resp)
{
  resp->setCloseConnection(true);
}
int main(int argc, char* argv[])
{
  int numThreads = 0;
  if (argc > 1)
  {
    benchmark = true;
    Logger::setLogLevel(Logger::WARN);
    numThreads = atoi(argv[1]);
  }
  EventLoop loop;
  webSocketServer server(&loop, InetAddress(8000), "websocket");
  server.setwebSocketOpenCallback(onOpen);
  server.setwebSocketMessageCallback(onMessage);
  server.setwebSocketErrorCallback(onError);
  server.setwebSocketCloseCallback(onClose);
  server.setThreadNum(numThreads);
  server.start();
  loop.loop();
}

char favicon[555] = {
  '\x89', 'P', 'N', 'G', '\xD', '\xA', '\x1A', '\xA',
  '\x0', '\x0', '\x0', '\xD', 'I', 'H', 'D', 'R',
  '\x0', '\x0', '\x0', '\x10', '\x0', '\x0', '\x0', '\x10',
  '\x8', '\x6', '\x0', '\x0', '\x0', '\x1F', '\xF3', '\xFF',
  'a', '\x0', '\x0', '\x0', '\x19', 't', 'E', 'X',
  't', 'S', 'o', 'f', 't', 'w', 'a', 'r',
  'e', '\x0', 'A', 'd', 'o', 'b', 'e', '\x20',
  'I', 'm', 'a', 'g', 'e', 'R', 'e', 'a',
  'd', 'y', 'q', '\xC9', 'e', '\x3C', '\x0', '\x0',
  '\x1', '\xCD', 'I', 'D', 'A', 'T', 'x', '\xDA',
  '\x94', '\x93', '9', 'H', '\x3', 'A', '\x14', '\x86',
  '\xFF', '\x5D', 'b', '\xA7', '\x4', 'R', '\xC4', 'm',
  '\x22', '\x1E', '\xA0', 'F', '\x24', '\x8', '\x16', '\x16',
  'v', '\xA', '6', '\xBA', 'J', '\x9A', '\x80', '\x8',
  'A', '\xB4', 'q', '\x85', 'X', '\x89', 'G', '\xB0',
  'I', '\xA9', 'Q', '\x24', '\xCD', '\xA6', '\x8', '\xA4',
  'H', 'c', '\x91', 'B', '\xB', '\xAF', 'V', '\xC1',
  'F', '\xB4', '\x15', '\xCF', '\x22', 'X', '\x98', '\xB',
  'T', 'H', '\x8A', 'd', '\x93', '\x8D', '\xFB', 'F',
  'g', '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f', 'v',
  'f', '\xDF', '\x7C', '\xEF', '\xE7', 'g', 'F', '\xA8',
  '\xD5', 'j', 'H', '\x24', '\x12', '\x2A', '\x0', '\x5',
  '\xBF', 'G', '\xD4', '\xEF', '\xF7', '\x2F', '6', '\xEC',
  '\x12', '\x20', '\x1E', '\x8F', '\xD7', '\xAA', '\xD5', '\xEA',
  '\xAF', 'I', '5', 'F', '\xAA', 'T', '\x5F', '\x9F',
  '\x22', 'A', '\x2A', '\x95', '\xA', '\x83', '\xE5', 'r',
  '9', 'd', '\xB3', 'Y', '\x96', '\x99', 'L', '\x6',
  '\xE9', 't', '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',
  '\xA7', '\xC4', 'b', '1', '\xB5', '\x5E', '\x0', '\x3',
  'h', '\x9A', '\xC6', '\x16', '\x82', '\x20', 'X', 'R',
  '\x14', 'E', '6', 'S', '\x94', '\xCB', 'e', 'x',
  '\xBD', '\x5E', '\xAA', 'U', 'T', '\x23', 'L', '\xC0',
  '\xE0', '\xE2', '\xC1', '\x8F', '\x0', '\x9E', '\xBC', '\x9',
  'A', '\x7C', '\x3E', '\x1F', '\x83', 'D', '\x22', '\x11',
  '\xD5', 'T', '\x40', '\x3F', '8', '\x80', 'w', '\xE5',
  '3', '\x7', '\xB8', '\x5C', '\x2E', 'H', '\x92', '\x4',
  '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g', '\x98',
  '\xE9', '6', '\x1A', '\xA6', 'g', '\x15', '\x4', '\xE3',
  '\xD7', '\xC8', '\xBD', '\x15', '\xE1', 'i', '\xB7', 'C',
  '\xAB', '\xEA', 'x', '\x2F', 'j', 'X', '\x92', '\xBB',
  '\x18', '\x20', '\x9F', '\xCF', '3', '\xC3', '\xB8', '\xE9',
  'N', '\xA7', '\xD3', 'l', 'J', '\x0', 'i', '6',
  '\x7C', '\x8E', '\xE1', '\xFE', 'V', '\x84', '\xE7', '\x3C',
  '\x9F', 'r', '\x2B', '\x3A', 'B', '\x7B', '7', 'f',
  'w', '\xAE', '\x8E', '\xE', '\xF3', '\xBD', 'R', '\xA9',
  'd', '\x2', 'B', '\xAF', '\x85', '2', 'f', 'F',
  '\xBA', '\xC', '\xD9', '\x9F', '\x1D', '\x9A', 'l', '\x22',
  '\xE6', '\xC7', '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15',
  '\x90', '\x7', '\x93', '\xA2', '\x28', '\xA0', 'S', 'j',
  '\xB1', '\xB8', '\xDF', '\x29', '5', 'C', '\xE', '\x3F',
  'X', '\xFC', '\x98', '\xDA', 'y', 'j', 'P', '\x40',
  '\x0', '\x87', '\xAE', '\x1B', '\x17', 'B', '\xB4', '\x3A',
  '\x3F', '\xBE', 'y', '\xC7', '\xA', '\x26', '\xB6', '\xEE',
  '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
  '\xA', '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X', '\x0',
  '\x27', '\xEB', 'n', 'V', 'p', '\xBC', '\xD6', '\xCB',
  '\xD6', 'G', '\xAB', '\x3D', 'l', '\x7D', '\xB8', '\xD2',
  '\xDD', '\xA0', '\x60', '\x83', '\xBA', '\xEF', '\x5F', '\xA4',
  '\xEA', '\xCC', '\x2', 'N', '\xAE', '\x5E', 'p', '\x1A',
  '\xEC', '\xB3', '\x40', '9', '\xAC', '\xFE', '\xF2', '\x91',
  '\x89', 'g', '\x91', '\x85', '\x21', '\xA8', '\x87', '\xB7',
  'X', '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N', 'N',
  'b', 't', '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
  '\xEC', '\x86', '\x2', 'H', '\x26', '\x93', '\xD0', 'u',
  '\x1D', '\x7F', '\x9', '2', '\x95', '\xBF', '\x1F', '\xDB',
  '\xD7', 'c', '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF',
  '\x22', 'J', '\xC3', '\x87', '\x0', '\x3', '\x0', 'K',
  '\xBB', '\xF8', '\xD6', '\x2A', 'v', '\x98', 'I', '\x0',
  '\x0', '\x0', '\x0', 'I', 'E', 'N', 'D', '\xAE',
  'B', '\x60', '\x82',
};
