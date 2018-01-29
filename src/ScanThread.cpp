#include "ScanThread.h"

void ScanThread::run()
{
//	UdpClient InsUdp;
//	InsUdp.init();
//	InsUdp.send();
	while(GAME_EXIT != getGameState())
	{
//		InsUdp.recv();
//		if(recvData != NULL)
//		{
			//sendto 
//		}
		msleep(50);
	}
}