#ifndef TCP_SERVER_H__
#define TCP_SERVER_H__

#include "Socket.h"

class TcpServer : public Socket
{
public:
	TcpServer(void);
	virtual ~TcpServer(void);
public:
	virtual bool init(const char* localIp, u16 localPort);
	virtual bool readData(u8 *buf, u32 len);
	virtual bool writeData(const u8 *buf, u32 len);
	virtual bool setSocketBlock();
	virtual bool setSocketNonblock();
	bool writeAll(const u8 *buf, u32 len);
	bool acceptConn();
	bool closeConn();
private:
	int _client_sockfd;
};

#endif/*TCP_SERVER_H__*/