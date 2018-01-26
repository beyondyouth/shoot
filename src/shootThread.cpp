#include "shootThread.h"
#include "sendThread.h"
#include "recvThread.h"
#include <string.h>

u8 link_state = LINK_FAILED;

u8 getLink_state()
{
	return link_state;
}

ShootThead* ShootThead::p = new ShootThead;

ShootThead* ShootThead::getInstance()
{
    return p;
}

ShootThead::ShootThead()
{
}

ShootThead::~ShootThead()
{
	delete p;
}

int ShootThead::init(u8 type)
{
	_type = type;
	return 0;
}

void ShootThead::run()
{
//	char sendbuf[MAXDATASIZE]={0};
//	char recvbuf[MAXDATASIZE]={0};
	if(SERVER == _type)
	{
		TcpServer InsServer;
		if(false == InsServer.init("10.0.2.15", 8817))
			return;
		if(false == InsServer.setSocketBlock())
			return;
//		printf("accepting------------\n");
		link_state = LINK_ACCEPT;
		InsServer.acceptConn();
		link_state = LINK_SUCCESS;
//		printf("connect success\n");
		
		RecvThread InsRecv((Socket*)&InsServer);
		InsRecv.start();
		SendThread InsSend((Socket*)&InsServer);
		InsSend.start();
/*		
		u8 i = 0;
		while(1)
		{
			sprintf(sendbuf, "hello ,I'm tcp server %d", i);
			i++;
			writeData((u8*)sendbuf, 30);
			printf("send data:%s\n", sendbuf);
			readData((u8*)recvbuf, 30);
			if(0 != recvbuf[0])
				printf("recv data:%s\n", recvbuf);
			sleep(5);
		}
*/		
		InsRecv.wait();
		InsSend.wait();
	}
	else if(CLIENT == _type)
	{
		TcpClient InsClient;
		if(false == InsClient.init())
			return;
		if(false == InsClient.setSocketBlock())
//		printf("connecting-----------\n");
		link_state = LINK_CONNECT;
		while(false == InsClient.conn("10.0.2.15", 8817))
		{
			sleep(3);
		}
		
//		printf("connect success\n");
		link_state = LINK_SUCCESS;
		RecvThread InsRecv((Socket*)&InsClient);
		InsRecv.start();
		SendThread InsSend((Socket*)&InsClient);
		InsSend.start();
/*		
		u8 i = 0;
		while(1)
		{
			sprintf(sendbuf, "hello ,I'm tcp client %d", i);
			i++;
			writeData((u8*)sendbuf, 30);
			printf("send data:%s\n", sendbuf);
			readData((u8*)recvbuf, 30);
			if(0 != recvbuf[0])
				printf("recv data:%s\n", recvbuf);
			sleep(5);
		}
*/		
		InsRecv.wait();
		InsSend.wait();
	}
}

int ShootThead::create_room()
{
	ShootThead* pInsShoot;
	pInsShoot = ShootThead::getInstance();
	pInsShoot->init(SERVER);
	pInsShoot->start();
	//pInsShoot->wait();
	return 0;
}

int ShootThead::join_room()
{
	ShootThead* pInsShoot;
	pInsShoot = ShootThead::getInstance();
	pInsShoot->init(CLIENT);
	pInsShoot->start();
	//pInsShoot->wait();
	return 0;
}