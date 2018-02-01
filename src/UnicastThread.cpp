#include "UnicastThread.h"
#include "TcpClient.h"
#include "TcpServer.h"

Socket* pTcpSock = NULL;

UnicastThread::UnicastThread()
{
}

UnicastThread::~UnicastThread()
{
}

void UnicastThread::run()
{
	G_mode game_mode = getGameMode();
	
	switch(game_mode)
	{
		case MODE_CREATE:
		{
			TcpServer* pInsTcp = new TcpServer();
			pTcpSock = (Socket*)pInsTcp;
			pInsTcp->init("192.168.99.128", 8817);
			pInsTcp->acceptConn();
			setAdvance();
			while(GAME_OVER != getGameState())
			{
				msleep(50);
			}
			pInsTcp->closeConn();
			if(NULL != pInsTcp)
				delete pInsTcp;
			break;
		}
		case MODE_JOIN:
		{
			TcpClient* pInsTcp = new TcpClient();
			pTcpSock = (Socket*)pInsTcp;
			pInsTcp->init();
			while(false == pInsTcp->conn("192.168.99.128", 8817))
			{
				sleep(3);
			}
			setAdvance();
			while(GAME_OVER != getGameState())
			{
				msleep(50);
			}
			pInsTcp->closeConn();
			if(NULL != pInsTcp)
				delete pInsTcp;
			break;
		}
		default:
			break;
	}
	
//	Udp_Client InsUdp = new UdpClient();
	
}