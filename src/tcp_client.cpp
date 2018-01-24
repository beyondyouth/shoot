#include "tcp_client.h"

TcpClient::TcpClient()
{
}

TcpClient::~TcpClient()
{
}

bool TcpClient::init(const char* localIp, u16 localPort)
{

	if(NULL == localIp)
	{
		return false;
	}

	strcpy(_localIp,localIp);
	_localPort = localPort;

	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}	

	bzero(&_localAddr,sizeof(_localAddr));
	_localAddr.sin_family = AF_INET;
	_localAddr.sin_port = htons(localPort);
	_localAddr.sin_addr.s_addr = inet_addr(localIp);

	return true;
}

bool TcpClient::conn(const char* servIp, u16 servPort)
{
	if( -1 == _sockfd )
	{
		_bConnected = false;
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(servPort);
	_serverAddr.sin_addr.s_addr = inet_addr(servIp);
	bzero(&(_serverAddr.sin_zero), 8);

	if(-1 == connect(_sockfd, (struct sockaddr*)&_serverAddr, sizeof(struct sockaddr)))
	{
		printf("Connect: %s failed!",inet_ntoa(_serverAddr.sin_addr));
		disConn();
		return false;
	}

	_bConnected = true;
	return true;
}

bool TcpClient::disConn()
{
	printf("Sockfd = %d,connecte status= %d, now disconnect socket....\n",_sockfd,_bConnected);
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	_sockfd = -1;
	_bConnected = false;
	return true;
}

bool TcpClient::readData(u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	recv(_sockfd, buf, len, 0);
	return true;
}

bool TcpClient::writeData(const u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	send(_sockfd, buf, len, 0);
	return true;
}