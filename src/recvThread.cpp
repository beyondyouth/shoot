#include "recvThread.h"

static u8 _recvbuf[MAXDATASIZE];
static u32 _buflen = MAXDATASIZE;

RecvThread::RecvThread(Socket* pSock)
{
	_Sock = pSock;
}

void RecvThread::run()
{
	u8 tempbuf[MAXDATASIZE];
	bzero(tempbuf, MAXDATASIZE);
	while(1)
	{
		
		_Sock->readData(tempbuf, _buflen);
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

