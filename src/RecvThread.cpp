#include "RecvThread.h"
#include "Mutex.h"
#include "ShowThread.h"

static u8 _recvBuf[MAXDATASIZE] = {0};
static Mutex* pRecvMux = new Mutex();

extern Socket* pTcpSock;
//extern void setLinkState(L_state s);

bool readRecvBuf(u8* buf, u32 len, u32 offset)
{
	pRecvMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pRecvMux->unlock();
		return false;
	}
	memcpy(buf, _recvBuf + offset, len);
	pRecvMux->unlock();
	return true;
}

bool writeRecvBuf(u8* buf, u32 len, u32 offset)
{
	pRecvMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pRecvMux->unlock();
		return false;
	}
	memcpy(_recvBuf + offset, buf, len);
	pRecvMux->unlock();
	return true;
}

RecvThread::RecvThread()
{
	_pSock = pTcpSock;
	_buflen = MAXDATASIZE;
}

void RecvThread::run()
{
	u8 tempBuf[MAXDATASIZE] = {0};
	while(GAME_EXIT != getGameState())
	{
		if(false == _pSock->readData(tempBuf, _buflen))
		{
			printf("error:%s %d",__FILE__, __LINE__);
//			setLinkState(LINK_ABORT);
		}
		if(0 != tempBuf[0])
		{
			writeRecvBuf(tempBuf, MAXDATASIZE);
			bzero(tempBuf, MAXDATASIZE);
		}
		else
		{
//			setSignal(SIGN_EXIT);
		}
		msleep(50);
	}
}

