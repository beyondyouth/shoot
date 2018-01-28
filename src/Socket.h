#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "common.h"

#define MAXDATASIZE 256

class Socket
{
public:
//	Socket(void);
//	virtual ~Socket(void);
public:
	virtual bool init(const char* localIp, u16 localPort) = 0;

	virtual bool readData(u8 *buf, u32 bufLen) = 0;
	virtual bool writeData(const u8 *buf, u32 dataLen) = 0;
	virtual bool setSocketBlock() = 0;
	virtual bool setSocketNonblock() = 0;
//	virtual void closes();
protected:			
	int _sockfd;

	char _localIp[32];
	u16 _localPort;
	
	struct sockaddr_in _clientAddr;
	struct sockaddr_in _serverAddr;
};

#endif/*SOCKET_H_*/