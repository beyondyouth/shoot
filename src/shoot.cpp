#include "shoot.h"
#include <string.h>
Shoot::Shoot(u8 type)
{
	_type = type;
}

Shoot::~Shoot()
{
}

void Shoot::run()
{
	char buf[MAXDATASIZE]={0};
	if(SERVER == _type)
	{
		TcpServer InsServer;
		InsServer.init("10.10.98.239", 8817);
		while(1)
		{
			InsServer.readData((u8*)(buf + 10), MAXDATASIZE - 10);
			strncpy(buf, "get data :", 10);
			InsServer.writeData((u8*)buf, MAXDATASIZE);
			bzero(buf, MAXDATASIZE);
		}
	}
	else if(CLIENT == _type)
	{
		TcpClient InsClient;
		InsClient.init("10.10.98.239", 8817);
		InsClient.conn("10.10.98.239", 8817);
	}
}
