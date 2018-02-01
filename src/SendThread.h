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
};

void writeData(u8* buf, u32 len);

#endif/*SEND_THREAD_H__*/