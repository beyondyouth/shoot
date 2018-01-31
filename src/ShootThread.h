#ifndef SHOOT_THREAD_H__
#define SHOOT_THREAD_H__

#include "Thread.h"
#include "TcpServer.h"
#include "TcpClient.h"

#define SERVER 1
#define CLIENT 2


class ShootThread : public Thread
{
public:
	ShootThread();
	~ShootThread();
	int init(u8 type);
	static int create_room(void);
	static int join_room(void);

	static ShootThread* getInstance(void);
	
protected:
	virtual void run();

private:
	u8 _type;
};

#endif/*SHOOT_THREAD_H__*/