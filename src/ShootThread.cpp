#include "ShootThread.h"
#include "SendThread.h"
#include "RecvThread.h"
#include <string.h>

static L_state link_state = LINK_FAILED;
L_state getLinkState()
{
	return link_state;
}

void setLinkState(L_state s)
{
	//link_state = s;
}

ShootThread::ShootThread()
{
	//_type = getGameMode();
}

ShootThread::~ShootThread()
{
}

void ShootThread::run()
{
/*	if(MODE_CREATE == _type)
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
	else if(MODE_JOIN == _type)
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
*/
}
