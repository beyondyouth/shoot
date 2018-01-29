#include "RecvThread.h"

static u8 _recvActBuf[MAXDATASIZE];
static u8 _recvCmdBuf[MAXDATASIZE];
static u32 _buflen = MAXDATASIZE;

remoteData

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
		switch(tempbuf[0])
		{
			case 'a':
			{
				memcpy(_recvActBuf, tempbuf + 1, MAXDATASIZE - 1);
				bzero(tempbuf, MAXDATASIZE);
				break;
			}
			case 'c':
			{
				memcpy(_recvCmdBuf, tempbuf + 1, MAXDATASIZE - 1);
				bzero(tempbuf, MAXDATASIZE);
				break;
			}
		}
		
		msleep(50);
	}
}

void readActData(u8* buf, u32 len)
{
	if(NULL != _recvActBuf)
	{
		memcpy(buf, _recvActBuf, len);
		bzero(_recvActBuf, MAXDATASIZE);
	}
}

void readCmdData(u8* buf, u32 len)
{
	if(NULL != _recvCmdBuf)
	{
		memcpy(buf, _recvCmdBuf, len);
		bzero(_recvCmdBuf, MAXDATASIZE);
	}
}
