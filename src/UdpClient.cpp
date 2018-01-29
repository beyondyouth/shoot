#include "UdpClient.h"

UdpClient::UdpClient()
{
}

UdpClient::~UdpClient()
{
}

bool UdpClient::init()
{
	strcpy(_localIp,"");
	_localPort = 0;
	
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	return true;
}

bool UdpClient::init(const char* localIp, u16 localPort)
{

	if(NULL == localIp)
	{
		return false;
	}

	strcpy(_localIp,localIp);
	_localPort = localPort;

	_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}	

	bzero(&_clientAddr,sizeof(_clientAddr));
	_clientAddr.sin_family = AF_INET;
	_clientAddr.sin_port = htons(localPort);
	_clientAddr.sin_addr.s_addr = inet_addr(localIp);

	return true;
}

bool UdpClient::setSocketBlock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) & ~O_NONBLOCK);
	fcntl(_sockfd, F_SETFD, FD_CLOEXEC);
	return true;
}

bool UdpClient::setSocketNonblock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) | O_NONBLOCK);
	return true;
}

bool UdpClient::conn(u16 servPort)
{
	if( -1 == _sockfd )
	{
		_bConnected = false;
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	
	const int opt = 1;
	if(-1 == setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)))
	{
		_bConnected = false;
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(servPort);
	_serverAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	bzero(&(_serverAddr.sin_zero), 8);

	_bConnected = true;
	return true;
}

bool UdpClient::disConn()
{
	printf("Sockfd = %d,connecte status= %d, now disconnect socket....\n",_sockfd,_bConnected);
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	_sockfd = -1;
	_bConnected = false;
	return true;
}

bool UdpClient::readData(u8 *buf,u32 len)
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

bool UdpClient::writeData(const u8 *buf,u32 len)
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
