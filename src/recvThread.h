#ifndef RECV_THREAD_H__
#define RECV_THREAD_H__

#include "thread.h"
#include "socket.h"

class RecvThread : public Thread
{
public:
	RecvThread(Socket* pSock);
	
protected:
	virtual void run();
	
private:
	Socket* _Sock;
};

void readData(u8* buf, u32 len);

#endif/*RECV_THREAD_H__*/











