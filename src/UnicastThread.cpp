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
/*	G_mode game_mode = getGameMode();
	
	switch(game_mode)
	{
		case MODE_CREATE:
		{
			TcpServer* pInsTcp = new TcpServer();
			pTcpSock = (Socket*)pInsTcp;
			pInsTcp->init("127.0.0.1", 8817);
			link_state = LINK_ACCEPT;
			pInsTcp->acceptConn();
			pInsTcp->setSocketNonblock();
			link_state = LINK_SUCCESS;
			while(GAME_EXIT != getGameState())
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
			while(false == pInsTcp->conn("127.0.0.1", 8817))
			{
				sleep(3);
			}
			pInsTcp->setSocketNonblock();
			link_state = LINK_SUCCESS;
			while(GAME_EXIT != getGameState())
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
*/	
//	Udp_Client InsUdp = new UdpClient();
	
}
