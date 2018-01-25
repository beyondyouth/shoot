#include "shootThread.h"
#include "sendThread.h"
#include "recvThread.h"
#include <string.h>
Shoot::Shoot(u8 type)
{
	_type = type;
}

Shoot::~Shoot()
{
}

void Shoot::run()
{
	char sendbuf[MAXDATASIZE]={0};
	char recvbuf[MAXDATASIZE]={0};
	if(SERVER == _type)
	{
		TcpServer InsServer;
		InsServer.init("192.168.99.129", 8817);
		InsServer.setSocketBlock();
		printf("accepting------------\n");
		InsServer.acceptConn();
		
		printf("connect success\n");
		
		RecvThread InsRecv((Socket*)&InsServer);
		InsRecv.start();
//		SendThread InsSend((Socket*)&InsServer);
//		InsSend.start();
		
//		u8 i = 0;
		while(1)
		{
//			sprintf(sendbuf, "hello ,I'm tcp server %d", i);
//			i++;
//			writebuf((u8*)sendbuf, 20);
//			printf("send data:%s\n", sendbuf);
			readbuf((u8*)recvbuf, 20);
			if(0 != recvbuf[0])
				printf("recv data:%s\n", recvbuf);
			sleep(5);
		}
		
		InsRecv.wait();
//		InsSend.wait();
	}
	else if(CLIENT == _type)
	{
		TcpClient InsClient;
		InsClient.init();
		InsClient.setSocketBlock();
		printf("connecting-----------\n");
		InsClient.conn("192.168.99.129", 8817);
		
		printf("connect success\n");
		
//		RecvThread InsRecv((Socket*)&InsClient);
//		InsRecv.start();
		SendThread InsSend((Socket*)&InsClient);
		InsSend.start();
		
		u8 i = 0;
		while(1)
		{
			sprintf(sendbuf, "hello ,I'm tcp client %d", i);
			i++;
			writebuf((u8*)sendbuf, 20);
			printf("send data:%s\n", sendbuf);
//			readbuf((u8*)recvbuf, 20);
//			if(0 != recvbuf[0])
//				printf("recv data:%s\n", recvbuf);
			sleep(5);
		}
		
//		InsRecv.wait();
		InsSend.wait();
	}
}
