#ifndef UDP_CLIENT_H__
#define UDP_CLIENT_H__

#include "Socket.h"

class UdpClient : public Socket
{
public:
	UdpClient(void);
	virtual ~UdpClient(void);
public:
	virtual bool readData(u8 *buf,u32 len);
	virtual bool writeData(const u8 *buf,u32 len);
	virtual bool setSocketBlock(void);
	virtual bool setSocketNonblock(void);
	bool init(u16 servPort);
	bool disConn(void);
private:

};

#endif/*UDP_CLIENT_H__*/