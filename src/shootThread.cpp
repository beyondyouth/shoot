#include "shootThread.h"
#include "sendThread.h"
#include "recvThread.h"
#include <string.h>

static L_state link_state = LINK_FAILED;
L_state getLinkState()
{
	return link_state;
}

u8 getLink_state()
{
	return link_state;
}

ShootThread* ShootThread::p = NULL;

ShootThread* ShootThread::getInstance()
{
	if(p == NULL)
		p = new ShootThread;
    return p;
}

ShootThread::ShootThread()
{
	_type = getGameMode();
}

ShootThread::~ShootThread()
{
	delete p;
}

void ShootThread::run()
{
	if(MODE_SERVER == _type)
	{
		TcpServer InsServer;
		if(false == InsServer.init("192.168.99.129", 8817))//192.168.99.129
			return;
		if(false == InsServer.setSocketBlock())
			return;
		link_state = LINK_ACCEPT;
		InsServer.acceptConn();
		link_state = LINK_SUCCESS;
		
		RecvThread InsRecv((Socket*)&InsServer);
		InsRecv.start();
		SendThread InsSend((Socket*)&InsServer);
		InsSend.start();
		
		InsRecv.wait();
		InsSend.wait();
	}
	else if(MODE_CLIENT == _type)
	{
		TcpClient InsClient;
		if(false == InsClient.init())
			return;
		if(false == InsClient.setSocketBlock())
		link_state = LINK_CONNECT;
		while(false == InsClient.conn("192.168.99.129", 8817))//192.168.99.129
		{
			sleep(3);
		}
		
		link_state = LINK_SUCCESS;
		RecvThread InsRecv((Socket*)&InsClient);
		InsRecv.start();
		SendThread InsSend((Socket*)&InsClient);
		InsSend.start();
	
		InsRecv.wait();
		InsSend.wait();
	}
}
