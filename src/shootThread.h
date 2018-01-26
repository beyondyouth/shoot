#ifndef SHOOT_THREAD_H__
#define SHOOT_THREAD_H__

#include "thread.h"
#include "tcp_server.h"
#include "tcp_client.h"

#define SERVER 1
#define CLIENT 2

#define LINK_ACCEPT 1
#define LINK_CONNECT 2
#define LINK_SUCCESS 3
#define LINK_FAILED 0

class ShootThead : public Thread
{
public:
	~ShootThead();
	int init(u8 type);
	static int create_room(void);
	static int join_room(void);

	static ShootThead* getInstance(void);
	
protected:
	virtual void run();
	
private:
	u8 _type;
	static ShootThead* p;
	ShootThead();
};

u8 getLink_state();

#endif/*SHOOT_THREAD_H__*/