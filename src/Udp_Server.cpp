#include "udp_server.h"

UdpServer::UdpServer()
{
}

UdpServer::~UdpServer()
{
}

bool UdpServer::init(const char* localIp, u16 localPort)
{
	_client_sockfd = 0;
	_localPort = localPort;
	strcpy(_localIp,localIp);
	
	_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return -1;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(localPort);
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(_serverAddr.sin_zero), 8);
	
	return true;
}

bool UdpServer::setSocketBlock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) & ~O_NONBLOCK);
	fcntl(_sockfd, F_SETFD, FD_CLOEXEC);
	return true;
}

bool UdpServer::setSocketNonblock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) | O_NONBLOCK);
	return true;
}

bool UdpServer::acceptConn(u16 localPort)
{
	u32 addrLen = sizeof(_clientAddr);
	bzero(&_clientAddr,addrLen);

    _clientAddr.sin_family = AF_INET;  
    _clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    _clientAddr.sin_port = htons(localPort);  
	
	const int opt = 1;  
    if(-1 == setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)))
    {  
        close(_sockfd);
		printf("error:%s %d",__FILE__, __LINE__);
		return false; 
    }
	
	if(-1 == bind(_sockfd,(struct sockaddr *)&_serverAddr,sizeof(_serverAddr)))
	{
		close(_sockfd);
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	return true;
}

bool UdpServer::readData(u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	if(-1 == recv(_sockfd, buf, len, 0))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	return true;
}

bool UdpServer::writeData(const u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	if(-1 == send(_sockfd, buf, len, 0))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	return true;
}
