#include "RecvThread.h"

static u8 _recvbuf[MAXDATASIZE];
static u32 _buflen = MAXDATASIZE;

extern void setLinkState(L_state s);

RecvThread::RecvThread()
{
}

bool RecvThread::init(Socket* pSock)
{
	_Sock = pSock;
}

void RecvThread::run()
{
	u8 tempbuf[MAXDATASIZE];
	bzero(tempbuf, MAXDATASIZE);
	while(LINK_SUCCESS == getLinkState() && GAME_OVER != getGameState())
	{
		
		if(false == _Sock->readData(tempbuf, _buflen))
		{
			printf("error:%s %d",__FILE__, __LINE__);
			setLinkState(LINK_ABORT);
		}
		if(0 != tempbuf[0])
		{
			memcpy(_recvbuf, tempbuf, MAXDATASIZE);
			bzero(tempbuf, MAXDATASIZE);
		}
		msleep(50);
	}
}

void readData(u8* buf, u32 len)
{
	if(NULL != _recvbuf)
	{
		memcpy(buf, _recvbuf, len);
		bzero(_recvbuf, MAXDATASIZE);
	}
}

