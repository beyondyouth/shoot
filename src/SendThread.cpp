#include "SendThread.h"
#include "Mutex.h"
#include "ShowThread.h"

static u8 _sendBuf[MAXDATASIZE] = {0};
static Mutex* pSendMux = new Mutex();

extern Socket* pTcpSock;

bool writeSendBuf(u8* buf, u32 len, u32 offset)
{
	pSendMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pSendMux->unlock();
		return false;
	}
	
	memcpy(_sendBuf + offset, buf, len);
	pSendMux->unlock();
	return true;
}


bool readSendBuf(u8* buf, u32 len, u32 offset)
{
	pSendMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pSendMux->unlock();
		return false;
	}
	
	memcpy(buf, _sendBuf + offset, len);
	pSendMux->unlock();
	return true;
}

SendThread::SendThread()
{
	_pSock = pTcpSock;
	_buflen = MAXDATASIZE;
}

void SendThread::run()
{
	u8 tempBuf[MAXDATASIZE] = {0};
	while(GAME_EXIT != getGameState())
	{
		if(0 != _sendBuf[0])
		{
			readSendBuf(tempBuf, MAXDATASIZE);
			if(false == _pSock->writeData(tempBuf, _buflen))
			{
				printf("error:%s %d",__FILE__, __LINE__);
			}
			bzero(tempBuf, MAXDATASIZE);
		}
		msleep(50);
	}
}

