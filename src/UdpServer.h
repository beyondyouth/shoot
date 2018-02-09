#ifndef UDP_SERVER_H__
#define UDP_SERVER_H__

#include "Socket.h"

class UdpServer : public Socket
{
public:
	UdpServer(void);
	virtual ~UdpServer(void);
public:
	virtual bool init(const char* localIp, u16 localPort);
	virtual bool readData(u8 *buf, u32 len);
	virtual bool writeData(const u8 *buf, u32 len);
	virtual bool setSocketBlock();
	virtual bool setSocketNonblock();
	bool init(u16 localPort);
	bool closeConn();
	
	bool acceptConn(u16 localPort);
	sockaddr_in getClientAddr(void);
private:
	struct sockaddr_in _serverAddr;
	struct sockaddr_in _clientAddr;
};


#endif/*UDP_SERVER_H__*/