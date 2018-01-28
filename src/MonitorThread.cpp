#include "MonitorThread.h"
#include "ShowThread.h"
#include "KeyThread.h"
#include "BroadcastThread.h"
#include "UnicastThread.h"
#include "SendThread.h"
#include "RecvThread.h"


static G_state game_state = GAME_EXIT;


G_state getGameState()
{
	return game_state;
}

MonitorThread::MonitorThread()
{
}

MonitorThread::~MonitorThread()
{
}

void MonitorThread::setAdvance()
{
	advance_state = true;
}

void MonitorThread::run()
{
	game_state = GAME_START;
	while(GAME_EXIT != game_state)
	{
		if(GAME_START == game_state && true == advance_state)
		{
			game_state = GAME_MAINMENU;
			advance_state = false;
			/*更新界面线程启动*/
			ShowThread InsShow = new ShowThread();
			InsShow.start();
			/*获取按键线程启动*/
			KeyThread InsKey = new KeyThread();
			InsKey.start();				
		}
		if(GAME_MAINMENU == game_state && true == advance_state)
		{
			game_state = GAME_SCANING;
			advance_state = false;
			/*广播线程启动*/
			BroadcastThread InsBroadcast = new BroadcastThread();
			InsBroadcast.start();
		}
		if(GAME_SCANING == game_state && true == advance_state)
		{
			game_state = GAME_LINKING;
			advance_state = false;
			/*广播线程终止*/
			if(NULL != InsBroadcast)
				delete InsBroadcast;
			/*单播线程启动*/
			UnicastThread InsUnicast = new UnicastThread();
			InsUnicast.start();
		}
		if(GAME_LINKING == game_state && true == advance_state)
		{
			game_state = GAME_READY;
			advance_state = false;
			/*发送线程启动*/
			SendThread InsSend = new SendThread();
			InsSend.start();
			/*接收线程启动*/
			RecvThread InsRecv = new RecvThread();
			InsRecv.start();
		}
		if(GAME_READY == game_state && true == advance_state)
		{
			game_state = GAME_FIGHT;
			advance_state = false;
		}
		if(GAME_FIGHT == game_state && true == advance_state)
		{
			game_state = GAME_OVER;
			advance_state = false;
			/**/
			if(NULL != InsSend)
				delete InsSend;
			if(NULL != InsRecv)
				delete InsRecv;
			if(NULL != InsUnicast)
				delete InsUnicast;

		}
		if(GAME_OVER == game_state && true == advance_state)
		{
			game_state = GAME_EXIT;
			advance_state = false;
		}
		msleep(50);
	}
	if(NULL != InsShow)
		delete InsShow;
	if(NULL != InsKey)
		delete InsKey;
	
}

