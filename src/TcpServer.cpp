#include "TcpServer.h"

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
}

bool TcpServer::init(const char* localIp, u16 localPort)
{
	_client_sockfd = 0;
	_localPort = localPort;
	strcpy(_localIp,localIp);
	
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return -1;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(localPort);
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(_serverAddr.sin_zero), 8);
	
	if(-1 == bind(_sockfd, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)))
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

	return true;
}

bool TcpServer::setSocketBlock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) & ~O_NONBLOCK);
	fcntl(_sockfd, F_SETFD, FD_CLOEXEC);
	return true;
}

bool TcpServer::setSocketNonblock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) | O_NONBLOCK);
	return true;
}

bool TcpServer::acceptConn()
{
	u32 addrLen = sizeof(_clientAddr);
	bzero(&_clientAddr, addrLen);
	_client_sockfd = accept(_sockfd, (struct sockaddr *)&_clientAddr, (socklen_t*)&addrLen);
	if(0 == _client_sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	return true;
}

bool TcpServer::readData(u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	if(-1 == recv(_client_sockfd, buf, len, 0))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	return true;
}

bool TcpServer::writeData(const u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	if(-1 == send(_client_sockfd, buf, len, 0))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
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
