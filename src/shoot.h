#ifndef SHOOT_H__
#define SHOOT_H__

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
	
protected:
	virtual void run();
	
private:
	u8 _type;
};

#endif/*SHOOT_H__*/