#include <ncurses.h>
#include <ctype.h>
#include "KeyThread.h"
#include "Socket.h"
#include "Mutex.h"

static u8 _LocBuf[MAXDATASIZE];
static int menu_order = 0;

int getItemNum()
{
	return menu_order;
}

extern u8 getItemLen();

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
	pLocMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pLocMux->unlock();
		return false;
	}
	memcpy(_LocBuf + offset, buf, len);
	pLocMux->unlock();
	return true;
}



void KeyThread::run()
{
	static int iX_local = COLS/2, iY_local = LINES/2;
	int iX_local_org = COLS/2, iY_local_org = LINES/2;
	int key_value;
	int sum_item = getItemLen();
	G_state game_state = getGameState();
	mvprintw(0, (COLS-strlen("---------------------1--------------------"))/2, "---------------------1--------------------");
	while(1)
	{
		key_value = getch();
		mvprintw(0, (COLS-strlen("---------------------2--------------------"))/2, "---------------------2--------------------");
		mvprintw(1, (COLS-strlen("key_value = 1"))/2, "key_value = %d", key_value);
		switch(game_state)
		{
			case GAME_MAINMENU:
			{
				switch (key_value)
				{
					case KEY_DOWN:
					{
						menu_order++;
						menu_order = menu_order % sum_item;
						
						break;
					}
					case KEY_UP:
					{
						menu_order--;
						menu_order = menu_order % sum_item;
					}
					default:
						break;
				}
				
				mvprintw(2, (COLS-strlen("menu_order = 1"))/2, "menu_order = %d", menu_order);
				break;
			}
				
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
			default:
				break;
		}
		sleep(50);
	}
}
