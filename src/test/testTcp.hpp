#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 40960
namespace testTcp
{
class client
{
public:
	client()
	{
		memset(m_sendBuffer,0,sizeof(m_sendBuffer));
	}
	void connects(const char* addr,int port)
	{
		m_connfd=socket(AF_INET,SOCK_STREAM,0);
		if(m_connfd<0)
		{
			printf("client create socket error:%s(errno:%d)\n",strerror(errno),errno );
			return;
		}
		memset(&m_servaddr,0,sizeof(m_servaddr));
		m_servaddr.sin_family=AF_INET;
		m_servaddr.sin_port=htons(port);
		if(inet_pton(AF_INET,addr,&m_servaddr.sin_addr)<=0)
		{
			printf("client inet_pton error for %s\n", addr);
			return;
		}
		if(connect(m_connfd,(sockaddr*)&m_servaddr,sizeof(m_servaddr))<0)
		{
			printf("client connect error:%s(errno:%d)\n",strerror(errno),errno );
			return;
		}
		sends();
	}
	void sends()
	{
		ssize_t writeLen;
		int count=0;
		while(1)
		{
			++count;
			if(count==5)
			{
				return;
			}
			writeLen=write(m_connfd,m_sendBuffer,sizeof(m_sendBuffer));
			if(writeLen<0)
			{
				printf("client write failed\n");
				close(m_connfd);
				return;
			}
			else
			{
				printf("client write success,writeLen:%ld\n",writeLen );
			}
		}
	}
	~client()
	{
		close(m_connfd);
	}
private:
	int m_connfd;
	char m_sendBuffer[MAXLINE];
	sockaddr_in m_servaddr;
};
class server
{
public:
	server()
	{
		
	}
	void listens(int port)
	{
		m_listenfd=socket(AF_INET,SOCK_STREAM,0);
		if(m_listenfd<0)
		{
			printf("server listen socket error:%s(errno:%d)\n",strerror(errno),errno );
			return;
		}
		memset(&m_servaddr,0,sizeof(m_servaddr));
		m_servaddr.sin_family=AF_INET;
		m_servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		m_servaddr.sin_port=htons(port);
		if(bind(m_listenfd,(sockaddr*)&m_servaddr,sizeof(m_servaddr))==-1)
		{
			printf("server bind socket error: %s(errno:%d)\n", strerror(errno),errno);
			return;
		}
		else
		{
			printf("server bind success\n");
		}
		if(listen(m_listenfd,10)==-1)
		{
			printf("server listen socket error:%s(errno:%d)\n",strerror(errno),errno );
			return;
		}
		else
		{
			printf("server listening...\n");
		}
	}
	void accepts()
	{
		m_acceptfd=accept(m_listenfd,(struct sockaddr*)NULL,NULL);
		if(m_acceptfd==-1)
		{
			printf("server accept socket error:%s(errno:%d)\n",strerror(errno),errno );
		}
		else
		{
			printf("server accept success\n");
			int rcvbuf_len;
			socklen_t len=sizeof(rcvbuf_len);
			if(getsockopt(m_acceptfd,SOL_SOCKET,SO_RCVBUF,(void*)&rcvbuf_len,&len)<0)
			{
				printf("server getsockopt error\n");
			}
			printf("server recv buf len:%d\n",rcvbuf_len );
			ssize_t total_len=0;
			while(1)
			{
				sleep(1);
				ssize_t read_len=read(m_acceptfd,m_recvBuffer,sizeof(m_recvBuffer));
				printf("server read len %ld\n",read_len );
				if(read_len<0)
				{
					printf("server read error\n");
					return;
				}
				else if(read_len==0)
				{
					printf("server read finish:len=%ld\n",total_len );
					close(m_acceptfd);
					return;
				}
				else
				{
					total_len+=read_len;
				}
			}
		}
	}
	
	~server()
	{
		//close(m_connfd);
	}
private:
	int m_listenfd;
	int m_acceptfd;
	char m_recvBuffer[MAXLINE];
	sockaddr_in m_servaddr;
};
void test_out()
{
	server s;
	s.listens(6666);
	s.accepts();
	// sleep(1);
	// client c;
	// c.connects("127.0.0.1",6666);
	// c.sends();
}	
}

