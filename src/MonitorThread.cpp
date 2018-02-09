#include "MonitorThread.h"
#include "ShowThread.h"
#include "KeyThread.h"
#include "ScanThread.h"
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

void MonitorThread::run()
{
	game_state = GAME_START;
	ShowThread* pInsShow = NULL;
	KeyThread* pInsKey = NULL;
	ScanThread* pInsScan = NULL;
	UnicastThread* pInsUnicast = NULL;
	SendThread* pInsSend = NULL;
	RecvThread* pInsRecv = NULL;
	while(game_state < GAME_EXIT)
	{
		if(SIGN_EXIT == getSignal())
		{
			game_state = GAME_EXIT;
		}
		if(GAME_START == game_state)
		{
			game_state = GAME_SELECT;
			/*更新界面线程启动*/
//			pInsShow = new ShowThread();
//			pInsShow->start();
			/*获取按键线程启动*/
			pInsKey = new KeyThread();
			pInsKey->start();
			/*扫描线程启动*/
			pInsScan = new ScanThread();
			pInsScan->start();
		}
#if 0
		if(GAME_SELECT == game_state && MODE_UNKNOW != getGameMode())
		{
			game_state = GAME_LINKING;
			/*tcp线程启动*/
			pInsUnicast = new UnicastThread();
			pInsUnicast->start();
		}	
		if(GAME_LINK == game_state && LINK_SUCCESS == getLinkState())
		{
			game_state = GAME_READY;
			/*发送线程启动*/
			pInsSend = new SendThread();
			pInsSend->start();
			/*接收线程启动*/
			pInsRecv = new RecvThread();
			pInsRecv->start();
		}		
		if(GAME_READY == game_state)
		{
			game_state = GAME_FIGHT;
		}
		
		if(GAME_FIGHT == game_state && true == advance_state)
		{
			game_state = GAME_OVER;
			advance_state = false;
			/**/
			if(NULL != pInsSend)
				delete pInsSend;
			if(NULL != pInsRecv)
				delete pInsRecv;
			if(NULL != pInsUnicast)
				delete pInsUnicast;

		}
		if(GAME_OVER == game_state && true == advance_state)
		{
			game_state = GAME_EXIT;
			advance_state = false;
		}

		msleep(50);
		mvprintw(0, (COLS-strlen("game state is 12"))/2, "game state is %2d", game_state);
#endif
	}
	if(NULL != pInsSend)
		delete pInsSend;
	if(NULL != pInsRecv)
		delete pInsRecv;
	if(NULL != pInsUnicast)
		delete pInsUnicast;
	
	
	if(NULL != pInsShow)
		delete pInsShow;
	if(NULL != pInsKey)
		delete pInsKey;
	if(NULL != pInsScan)
		delete pInsScan;
	
}

