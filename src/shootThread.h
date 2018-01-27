#ifndef SHOOT_THREAD_H__
#define SHOOT_THREAD_H__

#include "thread.h"
#include "tcp_server.h"
#include "tcp_client.h"

#define SERVER 1
#define CLIENT 2


class ShootThread : public Thread
{
public:
	~ShootThread();
	int init(u8 type);
	static int create_room(void);
	static int join_room(void);

	static ShootThread* getInstance(void);
	
protected:
	virtual void run();
	
private:
	u8 _type;
	static ShootThread* p;
	ShootThread();
};

#endif/*SHOOT_THREAD_H__*/