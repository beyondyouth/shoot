#if 1

#include <stdio.h>
#include "MonitorThread.h"

int main()
{
	MonitorThread InsMonitor;
	InsMonitor.start();
	InsMonitor.wait();
//	char data[6] = "abcde";
//	char test[3] = {0};
//	memcpy(test, data, 3);
//	printf("test is %s\n", test);
	return 0;
}


#else

/*
#include "UdpServer.h"
	
	
int main()
{
	u8 buf[256] = {0};
	UdpServer* pInsUdp = NULL;
	pInsUdp = new UdpServer();
	pInsUdp->init("192.168.99.128", 8817);
	pInsUdp->acceptConn(8817);
	
	for(int i = 0; i < 20; i++)
	{
		pInsUdp->readData(buf, 256);
		if(0 != buf[0])
			printf("RecvData:%s\n", buf);
		sleep(2);
	}
	pInsUdp->closeConn();
	if(NULL != pInsUdp)
		delete pInsUdp;
	return 0;
}

*/

#include "UdpClient.h"
int main()
{
	u8 buf[256] = {"hello"};
	UdpClient* pInsUdp = NULL;
	pInsUdp = new UdpClient();
	pInsUdp->init(8818);
	
	for(int i = 0; i < 20; i++)
	{
		pInsUdp->writeData(buf, 256);
		if(0 != buf[0])
			printf("sendData:%s\n", buf);
		sleep(2);
	}
	pInsUdp->disConn();
	if(NULL != pInsUdp)
		delete pInsUdp;
	return 0;
}


#endif

