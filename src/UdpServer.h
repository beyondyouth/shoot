#ifndef UDP_SERVER_H__
#define UDP_SERVER_H__

#include "Socket.h"

class UdpServer : public Socket
{
public:
	UdpServer();
	~UdpServer();
public:
	virtual bool init(const char* localIp, u16 localPort);
	virtual bool readData(u8 *buf, u32 len);
	virtual bool writeData(const u8 *buf, u32 len);
	virtual bool setSocketBlock();
	virtual bool setSocketNonblock();
	bool closeConn();
	
	bool acceptConn(u16 localPort);
private:
	int _client_sockfd;
};


#endif/*UDP_SERVER_H__*/