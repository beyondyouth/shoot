#ifndef SHOOT_THREAD_H__
#define SHOOT_THREAD_H__

#include "thread.h"
#include "tcp_server.h"
#include "tcp_client.h"

#define SERVER 1
#define CLIENT 2

class Shoot : public Thread
{
public:
	Shoot(u8 type);
	~Shoot();
	int create_room(void);
	int join_room(void);
	
protected:
	virtual void run();
	
private:
	u8 _type;
};

#endif/*SHOOT_H__*/