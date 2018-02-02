#include "UnicastThread.h"
#include "TcpClient.h"
#include "TcpServer.h"

static L_state link_state = LINK_FAILED;
L_state getLinkState()
{
	return link_state;
}

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
			pInsTcp->init("10.10.98.239", 8817);
			link_state = LINK_ACCEPT;
			pInsTcp->acceptConn();
			link_state = LINK_SUCCESS;
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
			link_state = LINK_CONNECT;
			while(false == pInsTcp->conn("10.10.98.239", 8817))
			{
				sleep(3);
			}
			link_state = LINK_SUCCESS;
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