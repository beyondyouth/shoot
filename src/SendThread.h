#ifndef SEND_THREAD_H__
#define SEND_THREAD_H__

#include "Thread.h"
#include "Socket.h"

class SendThread : public Thread
{
public:
	SendThread();

protected:
	virtual void run();
	
private:
	Socket* _pSock;
	u32 _buflen;
};

bool writeSendBuf(u8* buf, u32 len, u32 offset = 0);
bool readSendBuf(u8* buf, u32 len, u32 offset = 0);

#endif/*SEND_THREAD_H__*/