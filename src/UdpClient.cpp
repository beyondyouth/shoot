#include "UdpClient.h"

UdpClient::UdpClient()
{
}

UdpClient::~UdpClient()
{
}

bool UdpClient::init(u16 servPort)
{
	strcpy(_localIp,"");
	_localPort = 0;
	
	_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == _sockfd)
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	
	const int opt = 1;
	if(-1 == setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(servPort);
	_serverAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	bzero(&(_serverAddr.sin_zero), 8);

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


bool UdpClient::disConn()
{
	//printf("Sockfd = %d,connecte status= %d, now disconnect socket....\n",_sockfd,_bConnected);
	shutdown(_sockfd, SHUT_RDWR);
	close(_sockfd);
	_sockfd = -1;

	return true;
}

bool UdpClient::readData(u8 *buf,u32 len)
{
	if(len > MAXDATASIZE)
		len = MAXDATASIZE;
	int nlen = sizeof(_serverAddr);
	if(-1 == recvfrom(_sockfd, buf, len, 0, (sockaddr*)&_serverAddr, (socklen_t*)&nlen))
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
	int nlen = sizeof(_serverAddr);
	if(-1 == sendto(_sockfd, buf, len, 0, (sockaddr*)&_serverAddr, nlen))
	{
		printf("error:%s %d",__FILE__, __LINE__);
		return false;
	}
	return true;
}
