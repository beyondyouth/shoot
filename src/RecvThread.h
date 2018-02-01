#ifndef RECV_THREAD_H__
#define RECV_THREAD_H__

#include "Thread.h"
#include "Socket.h"

class RecvThread : public Thread
{
public:
	RecvThread();
	
protected:
	virtual void run();
	
private:
	Socket* _pSock;
	u32 _buflen;
};

bool readActData(u8* buf, u32 len);

bool readCmdData(u8* buf, u32 len);

#endif/*RECV_THREAD_H__*/











