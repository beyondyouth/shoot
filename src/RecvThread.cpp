#include "RecvThread.h"
#include "Mutex.h"

#include "ShowThread.h"

static u8 _recvActBuf[MAXDATASIZE];
static u8 _recvCmdBuf[MAXDATASIZE];

static Mutex* pActMux = new Mutex();
static Mutex* pCmdMux = new Mutex();

extern Socket* pTcpSock;
//extern void setLinkState(L_state s);

bool readActData(u8* buf, u32 len, u32 offset = 0)
{
	pActMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pActMux->unlock();
		return false;
	}
	memcpy(buf, _recvActBuf + offset, len);
	pActMux->unlock();
	return true;
}

bool readCmdData(u8* buf, u32 len, u32 offset = 0)
{
	pCmdMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pCmdMux->unlock();
		return false;
	}
	memcpy(buf, _recvCmdBuf + offset, len);
	pCmdMux->unlock();
	return true;
}

static bool writeActData(u8* buf, u32 len, u32 offset = 0)
{
	pActMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pActMux->unlock();
		return false;
	}
	memcpy(_recvActBuf + offset, buf, len);
	pActMux->unlock();
	return true;
}

static bool writeCmdData(u8* buf, u32 len, u32 offset = 0)
{
	pCmdMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pCmdMux->unlock();
		return false;
	}
	memcpy(_recvCmdBuf + offset, buf, len);
	pCmdMux->unlock();
	return true;
}

RecvThread::RecvThread()
{
	_pSock = pTcpSock;
	_buflen = MAXDATASIZE;
	setAdvance();
}

void RecvThread::run()
{
	u8 tempbuf[MAXDATASIZE];
	bzero(tempbuf, MAXDATASIZE);
	while(GAME_OVER != getGameState())
	{
		if(false == _pSock->readData(tempbuf, _buflen))
		{
			printf("error:%s %d",__FILE__, __LINE__);
//			setLinkState(LINK_ABORT);
		}
		switch(tempbuf[0])
		{
			case 'a':
			{
				writeActData(tempbuf + 1, MAXDATASIZE - 1);
				bzero(tempbuf, MAXDATASIZE);
				break;
			}
			case 'c':
			{
				writeCmdData(tempbuf + 1, MAXDATASIZE - 1);
				bzero(tempbuf, MAXDATASIZE);
				break;
			}
		}
		
		msleep(50);
	}
}

