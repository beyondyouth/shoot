#include "SendThread.h"

#include "ShowThread.h"

static u8* _sendbuf = NULL;
static u32 _buflen = MAXDATASIZE;

extern Socket* pTcpSock;
extern void setLinkState(L_state s);

SendThread::SendThread()
{
	_pSock = pTcpSock;
	setAdvance();
}

void SendThread::run()
{
	while(GAME_OVER != getGameState())
	{	
		if(NULL != _sendbuf)
		{
			if(false == _pSock->writeData(_sendbuf, _buflen))
			{
				printf("error:%s %d",__FILE__, __LINE__);
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