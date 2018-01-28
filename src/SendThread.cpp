#include "sendThread.h"

static u8* _sendbuf = NULL;
static u32 _buflen = MAXDATASIZE;

extern void setLinkState(L_state s);

SendThread::SendThread(Socket* pSock)
{
	_Sock = pSock;
}

void SendThread::run()
{
	while(LINK_SUCCESS == getLinkState() && GAME_OVER != getGameState())
	{
		if(0 != _sendbuf[0])
		{
			if(false == _Sock->writeData(_sendbuf, _buflen))
			{
				printf("error:%s %d",__FILE__, __LINE__);
				setLinkState(LINK_ABORT);
			}
			bzero(_sendbuf, MAXDATASIZE);
		}
		msleep(50);
	}
}

void writeData(u8* buf, u32 len)
{
	_sendbuf = buf;
	_buflen = len;
}