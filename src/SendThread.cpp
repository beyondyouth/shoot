#include "SendThread.h"
#include "Mutex.h"
#include "ShowThread.h"

static u8 _sendActBuf[MAXDATASIZE] = {0};
static u8 _sendCmdBuf[MAXDATASIZE] = {0};

static Mutex* pActMux = new Mutex();
static Mutex* pCmdMux = new Mutex();

extern Socket* pTcpSock;
extern void setLinkState(L_state s);

SendThread::SendThread()
{
	_pSock = pTcpSock;
	_buflen = MAXDATASIZE;
}

void SendThread::run()
{
	while(GAME_OVER != getGameState())
	{	
		if(0 != _sendCmdBuf[0])
		{
			if(false == _pSock->writeData(_sendCmdBuf, _buflen))
			{
				printf("error:%s %d",__FILE__, __LINE__);
			}
			bzero(_sendCmdBuf, MAXDATASIZE);
		}
		if(0 != _sendActBuf[0])
		{
			if(false == _pSock->writeData(_sendActBuf, _buflen))
			{
				printf("error:%s %d",__FILE__, __LINE__);
			}
			bzero(_sendActBuf, MAXDATASIZE);
		}
		msleep(50);
	}
}

bool writeSendAct(u8* buf, u32 len, u32 offset = 0)
{
	pActMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pActMux->unlock();
		return false;
	}
	
	memcpy(_sendActBuf + offset, buf, len);
	pActMux->unlock();
	return true;
}

bool writeSendCmd(u8* buf, u32 len, u32 offset = 0)
{
	pCmdMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pCmdMux->unlock();
		return false;
	}
	
	memcpy(_sendCmdBuf + offset, buf, len);
	pCmdMux->unlock();
	return true;	

}

bool readSendAct(u8* buf, u32 len, u32 offset = 0)
{
	pActMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pActMux->unlock();
		return false;
	}
	
	memcpy(buf, _sendActBuf + offset, len);
	pActMux->unlock();
	return true;
}

bool readSendCmd(u8* buf, u32 len, u32 offset = 0)
{
	pCmdMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pCmdMux->unlock();
		return false;
	}
	
	memcpy(buf, _sendCmdBuf + offset, len);
	pCmdMux->unlock();
	return true;
}