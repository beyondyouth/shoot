#include "tcp_server.h"

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
}

bool TcpServer::init(const char* localIp, u16 localPort)
{
	_localPort = localPort;
	strcpy(_localIp,localIp);
	
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return -1;
	}

	_localAddr.sin_family = AF_INET;
	_localAddr.sin_port = htons(localPort);
	_localAddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(_serverAddr.sin_zero), 8);
	
	if(-1 == bind(_sockfd,(struct sockaddr *)&_localAddr,sizeof(_localAddr)))
	{
		close(_sockfd);
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

		/*允许有十个客户端连接*/
	if(-1 == listen(_sockfd,10))
	{
		close(_sockfd);
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	acceptConn();
	return true;
}

bool TcpServer::acceptConn()
{
	struct sockaddr_in clientSockAddr;
	u32 addrLen = sizeof(clientSockAddr);
	bzero(&clientSockAddr,addrLen);
	accept(_sockfd,(struct sockaddr *)&clientSockAddr,(socklen_t*)&addrLen);
	return true;
}

bool TcpServer::readData(u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	recv(_sockfd, buf, len, 0);
	return true;
}

bool TcpServer::writeData(const u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	send(_sockfd, buf, len, 0);
	return true;
}

bool TcpServer::writeAll(const u8 *buf,u32 dataLen)
{
	return true;
}

bool TcpServer::closeConn()
{
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	_sockfd = -1;
	return true;
}
