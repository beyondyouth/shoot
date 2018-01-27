#include "sendThread.h"

static u8* _sendbuf = NULL;
static u32 _buflen = MAXDATASIZE;

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
			_Sock->writeData(_sendbuf, _buflen);
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