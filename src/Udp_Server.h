#ifndef UDP_SERVER_H__
#define UDP_SERVER_H__

#include "socket.h"

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
	
	bool acceptConn(u16 localPort);

};


#endif/*UDP_SERVER_H__*/