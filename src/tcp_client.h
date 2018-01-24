#ifndef TCP_CLIENT_H__
#define TCP_CLIENT_H__

#include "socket.h"

class TcpClient : public Socket
{
public:
	TcpClient(void);
	virtual ~TcpClient(void);
public:
	virtual bool init(const char* localIp,u16 localPort);
	virtual bool readData(u8 *buf,u32 len);
	virtual bool writeData(const u8 *buf,u32 len);
	bool conn(const char* servIp, u16 servPort);
	bool disConn();
private:
	bool _bConnected;
};

#endif/*TCP_CLIENT_H__*/