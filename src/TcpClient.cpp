#include "TcpClient.h"

TcpClient::TcpClient()
{
}

TcpClient::~TcpClient()
{
}

bool TcpClient::init()
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

	bzero(&_clientAddr,sizeof(_clientAddr));
	_clientAddr.sin_family = AF_INET;
	_clientAddr.sin_port = htons(localPort);
	_clientAddr.sin_addr.s_addr = inet_addr(localIp);

	return true;
}

bool TcpClient::setSocketBlock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) & ~O_NONBLOCK);
	fcntl(_sockfd, F_SETFD, FD_CLOEXEC);
	return true;
}

bool TcpClient::setSocketNonblock()
{
	fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL) | O_NONBLOCK);
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
		printf("Connect: %s failed!\n",inet_ntoa(_serverAddr.sin_addr));
		//disConn();
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

bool TcpClient::closeConn()
{
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	_sockfd = -1;
	return true;
}

bool TcpClient::readData(u8 *buf,u32 len)
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

bool TcpClient::writeData(const u8 *buf,u32 len)
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
