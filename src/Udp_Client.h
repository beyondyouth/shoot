#ifndef UDP_CLIENT_H__
#define UDP_CLIENT_H__

#include "socket.h"

class UdpClient : public Socket
{
public:
	UdpClient(void);
	virtual ~UdpClient(void);
public:
	virtual bool init(const char* localIp,u16 localPort);
	virtual bool readData(u8 *buf,u32 len);
	virtual bool writeData(const u8 *buf,u32 len);
	virtual bool setSocketBlock(void);
	virtual bool setSocketNonblock(void);
	bool init(void);
	bool conn(u16 servPort);
	bool disConn(void);
private:
	bool _bConnected;
};

#endif/*UDP_CLIENT_H__*/