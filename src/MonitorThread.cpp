#include "MonitorThread.h"
#include "ShowThread.h"
#include "KeyThread.h"
#include "ScanThread.h"
#include "UnicastThread.h"
#include "SendThread.h"
#include "RecvThread.h"

bool advance_state = false;

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

void setAdvance()
{
	advance_state = true;
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
	
	while(GAME_EXIT != game_state)
	{
		if(GAME_START == game_state && true == advance_state)
		{
			game_state = GAME_MAINMENU;
			advance_state = false;
			/*更新界面线程启动*/
			pInsShow = new ShowThread();
			pInsShow->start();
			/*获取按键线程启动*/
			pInsKey = new KeyThread();
			pInsKey->start();				
		}
		if(GAME_MAINMENU == game_state && true == advance_state)
		{
			game_state = GAME_SCANING;
			advance_state = false;
			/*扫描线程启动*/
			pInsScan = new ScanThread();
			pInsScan->start();
		}
		if(GAME_SCANING == game_state && true == advance_state)
		{
			game_state = GAME_LINKING;
			advance_state = false;
			/*tcp线程启动*/
			pInsUnicast = new UnicastThread();
			pInsUnicast->start();
		}
		if(GAME_LINKING == game_state && true == advance_state)
		{
			game_state = GAME_READY;
			advance_state = false;
			/*发送线程启动*/
			pInsSend = new SendThread();
			pInsSend->start();
			/*接收线程启动*/
			pInsRecv = new RecvThread();
			pInsRecv->start();
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
	}
	if(NULL != pInsShow)
		delete pInsShow;
	if(NULL != pInsKey)
		delete pInsKey;
	if(NULL != pInsScan)
		delete pInsScan;
	
}

