#include "KeyThread.h"

static u8 _LocBuf[MAXDATASIZE];

int getItemNum()
{
	return 0;
}

static Mutex* pLocMux = new Mutex();

//extern void setLinkState(L_state s);

bool readLocData(u8* buf, u32 len, u32 offset = 0)
{
	pLocMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pLocMux->unlock();
		return false;
	}
	memcpy(buf, _LocBuf + offset, len);
	pLocMux->unlock();
	return true;
}

static bool writeLocData(u8* buf, u32 len, u32 offset = 0)
{
	pActMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pActMux->unlock();
		return false;
	}
	memcpy(_LocBuf + offset, buf, len);
	pActMux->unlock();
	return true;
}



void KeyThread::run()
{
	int iX_local_org = COLS/2, iY_local_org = LINES/2;
	
	while(GAME_EXIT == getGameState())
	{
		key_value = getch();
		switch(game_state)
		{
			case GAME_MAINMENU:
			{
				switch (key_value)
				{
					case KEY_DOWN:
					{
						break;
					}
					case KEY_UP:
					{
						break;
					}
				}
			}
				break;
			case GAME_FIGHT:
			{
				switch (key_value)
				{
					case KEY_DOWN:
						if(iY_local < LINES - 1)iY_local++;
						break;
					case KEY_UP:
						if(iY_local > 1)iY_local--;
						break;
					case KEY_LEFT:
						if(iX_local > 1)iX_local--;
						break;
					case KEY_RIGHT:
						if(iX_local < COLS - 1)iX_local++;
						break;
					default:
						break;
				}
				/*if _LocBuf changed*/
				if(iY_local_org != iY_local || iX_local_org != iX_local)
				{
					sprintf((char*)_LocBuf, "%03d%03d", iX_local, iY_local);
					iX_local_org = iX_local;
					iY_local_org = iY_local;
				}
				
				writeLocData((u8*)_LocBuf, 6);
				//writeData((u8*)_LocBuf, 6);
				
				break;
			}
		}
		sleep(50);
	}
}
