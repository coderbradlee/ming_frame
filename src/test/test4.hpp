#include "../log.hpp"
#include "../include.hpp"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/Connector.h>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <muduo/base/LogStream.h>
#include <execinfo.h>
namespace test4_namespace
{
	using std::string;
	typedef struct linknode
	{
		int value;
		linknode* next;
		linknode(int val):value(val),next(nullptr){}
	}node;
	void print(node* phead)
	{
		node* p=phead->next;
		while(p!=nullptr)
		{
			std::cout<<p->value<<"-->";
			p=p->next;
		}	
		std::cout<<"end"<<std::endl;
	}
	void destroy(node* phead)
	{
		node* p;
		while(phead!=nullptr)
		{
			std::cout<<"destroy:"<<phead->value<<std::endl;
			p=phead->next;
			delete phead;
			phead=p;
		}
	}
	void reverse(node* phead,int start,int end)
	{
		node* prev;
		for(int i=0;i<start-1;++i)
		{	
			prev=phead->next;
			phead=prev;
		}
		node* pstart=prev;
		prev=prev->next;
		node* pcur=prev->next;
		for(int i=start;i<end;++i)
		{	
			node* temp=pstart->next;
			pstart->next=pcur;
			prev->next=pcur->next;
			pcur->next=temp;
			pcur=prev->next;
		}
	}
	void test()
	{
		node* phead=new node(0);
		node* pindex=phead;
		for(int i=0;i<10;++i)
		{
			node* p=new node(rand()%100);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		reverse(phead,3,5);
		print(phead);
		destroy(phead);
	}
	void deleteDuplicate2(node* phead)
	{
		node* prev=phead;
		node* p=phead->next->next;
		phead=phead->next;
		
		while(p)
		{
			if(p->value==phead->value)
			{
				int temp=p->value;
				while(p->value==temp)
				{
					phead->next=p->next;
					delete p;
					p=phead->next;
				}
				prev->next=p;
				std::cout<<"delete:"<<phead->value<<std::endl;
				delete phead;
				phead=p;
				p=p->next;
				std::cout<<"::"<<prev->value<<std::endl;
				std::cout<<"::"<<phead->value<<std::endl;
				std::cout<<"::"<<p->value<<std::endl;
			}
			else
			{
				p=p->next;
				phead=phead->next;
				prev=prev->next;
			}
		}
	}
	void partition(node* phead,int value)
	{
		node* left=phead;
		node* right=new node(0);
		node* leftindex=phead;
		node* rightindex=right;
		while(phead&&phead->next)
		{
			if(phead->next->value<value)
			{
				leftindex->next=phead->next;
				phead=phead->next;
				leftindex=leftindex->next;
				leftindex->next=nullptr;
				std::cout<<":"<<leftindex->value<<std::endl;
			}
			else
			{
				rightindex->next=phead->next;
				phead=phead->next;
				rightindex=rightindex->next;
				rightindex->next=nullptr;
				std::cout<<"::"<<rightindex->value<<std::endl;
			}
		}
		leftindex->next=right->next;

	}
	void test2()
	{
		node* phead=new node(0);
		int digit[]={1,2,3,4,4,4,5,6};
		node* pindex=phead;
		for(int i=0;i<8;++i)
		{
			node* p=new node(digit[i]);
			pindex->next=p;
			pindex=pindex->next;
		}
		print(phead);
		//deleteDuplicate(phead);
		//deleteDuplicate2(phead);
		partition(phead,4);
		print(phead);
		destroy(phead);
	}
	void test_out()
	{
		test2();
	}
}