#include "ScanThread.h"
#include "UdpClient.h"
#include "UdpServer.h"

Node* head = NULL;

ScanThread::ScanThread()
{
}

ScanThread::~ScanThread()
{
}

void push(Node* n)
{
	int i = 0;
	if(NULL == head)
	{
		head = n;
		head->next = NULL;
		head->prev = NULL;
		return;
	}
	/*在最后添加新的ip节点*/
	Node* p = head;
	for(; p->next != NULL; p = p->next);
	p->next = n;
	n->prev = p;
	n->next = NULL;
}

void erase(Node* n)
{
	if(NULL == head)
	{
		return;
	}
	if(n == head)
	{
		delete n;
	}
	/*删除n指向的Node节点*/
	for(Node* p = head; p->next != NULL; p = p->next)
	{
		if(p->next == n)
		{
			p->next = n->next;
			(n->next)->prev = p;
			if(NULL != n)
				delete n;
		}
	}
}

Node* find(char* d)
{
	if(NULL == head)
	{
		return NULL;
	}
	/*寻找数据匹配的节点地址*/
	Node* p = head;
	for(; p->next != NULL; p = p->next)
	{
		if(!strcmp(p->data, d))
		{
			return p;
		}
	}
	if(!strcmp(p->data, d))
	{
		return p;
	}
	return NULL;
}

void output()
{
	int i = 0;
	if(NULL == head)
	{
		return;
	}
	Node* p = head;
	for(; p->next != NULL; p = p->next)
	{
		printf("ip%d:%s addr:%d\r\n", i, p->data, p);
		i++;
	}
	printf("ip%d:%s addr:%d\r\n", i, p->data, p);
}

int getlen()
{
	int i = 0;
	if(NULL == head)
	{
		return i;
	}
	Node* p = head;
	for(; p->next != NULL; p = p->next)
	{
		i++;
	}
	i++;
	return i;
}

void ScanThread::run()
{
	char recv[256] = {0};
	/*上线发送一次广播*/
	UdpClient* pInsUdpc = new UdpClient();
	pInsUdpc->init(8818);
	pInsUdpc->writeData((u8*)"sign up ", 8);
	pInsUdpc->disConn();
	if(NULL != pInsUdpc)
		delete pInsUdpc;

	/*开启udp server模式*/
	UdpServer* pInsUdps = new UdpServer();
	pInsUdps->init(8818);
	while(GAME_EXIT > getGameState())
	{
		pInsUdps->readData((u8*)recv, 8);
		/*一旦接受到广播数据包延时0.5s后就回一个udp包*/
		if(!strcmp(recv, "responce"))
		{
			/*获取对方ip*/
			Node* n = new Node;
			strcpy(n->data, inet_ntoa(pInsUdps->getClientAddr().sin_addr));
			if(NULL == find(n->data))
			{
				push(n);
			}
			else
			{
				if(NULL != n)
					delete n;
			}
			//output();
		}
		if(!strcmp(recv, "sign up "))
		{
			/*获取对方ip*/
			Node* n = new Node;		
			strcpy(n->data, inet_ntoa(pInsUdps->getClientAddr().sin_addr));
			/*回应responce*/
			UdpClient pInsUdpc2;
			pInsUdpc2.sendto2(n->data, 8818, (u8*)"responce", 8);
			if(NULL == find(n->data))
			{
				push(n);
			}
			else
			{
				if(NULL != n)
					delete n;
			}
			//output();
		}
		if(!strcmp(recv, "sign out"))
		{
			/*获取对方ip*/
			Node* n = new Node;		
			strcpy(n->data, inet_ntoa(pInsUdps->getClientAddr().sin_addr));
			if(NULL == find(n->data))
			{
				if(NULL != n)
					delete n;
			}
			else
			{
				erase(n);
			}
			//output();
		}
		/*清空接收缓存*/
		bzero(recv, 256);	
		msleep(50);
	}
	pInsUdps->closeConn();
	if(NULL != pInsUdps)
		delete pInsUdps;

	/*下线发一次广播*/
	pInsUdpc = new UdpClient();
	pInsUdpc->init(8818);
	pInsUdpc->writeData((u8*)"sign out", 8);
	pInsUdpc->disConn();
	if(NULL != pInsUdpc)
		delete pInsUdpc;
}