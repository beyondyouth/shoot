#ifndef SEND_THREAD_H__
#define SEND_THREAD_H__

#include "thread.h"
#include "socket.h"

class SendThread : public Thread
{
public:
	SendThread(Socket* pSock);
	
protected:
	virtual void run();
	
private:
	Socket* _Sock;
};

void writebuf(u8* buf, u32 len);

#endif/*SEND_THREAD_H__*/