#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include "KeyThread.h"
#include "SendThread.h"
#include "Mutex.h"

static u8 _LocBuf[MAXDATASIZE];

static int menu_order = -1;
int getMenuOrder()
{
	return menu_order;
}

extern u8 getItemLen();

static G_signal key_sign = SIGN_NO;
G_signal getKeySign()
{
	return key_sign;
}

static Mutex* pLocMux = new Mutex();

static G_mode game_mode = MODE_UNKNOW;
G_mode getGameMode()
{
	return game_mode;
}

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

bool KeyThread::init()
{
	system(STTY_US TTY_PATH);
	return true;
}

int KeyThread::get_char()
{
    fd_set rfds;
    struct timeval tv;
    int ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0){
        ch = getch(); 
    }
    return ch;
}

void KeyThread::run()
{
	init();
	static int iX_local = COLS/2, iY_local = LINES/2;
	int iX_local_org = COLS/2, iY_local_org = LINES/2;
	int sum_item = getItemLen();

	while(GAME_EXIT != getGameState())
	{
		key_value = get_char();
		if(key_value == 3)
		{
			key_sign = SIGN_EXIT;
			setAdvance();
            //system(STTY_DEF TTY_PATH);
            break;
        }
		switch(getGameState())
		{
			case GAME_MAINMENU:
			{
				//mvprintw(1, (COLS-strlen("key value is 12"))/2, "key value is %2d", key_value);
				switch (key_value)
				{
					case KEY_DOWN:
					{
						if(menu_order + 1 < sum_item)
							menu_order++;
						break;
					}
					case KEY_UP:
					{
						if(menu_order - 1 >= 0)
							menu_order--;
						break;
					}
					case EV_ENTER:
					{
						switch(menu_order)
						{
							case 0:
							{
								game_mode = MODE_CREATE;
								break;
							}
							case 1:
							{
								game_mode = MODE_JOIN;
								break;
							}
							case 2:
							{
								key_sign = SIGN_EXIT;
								break;
							}
							default:
								break;
						}
						setAdvance();
					}
					default:
						break;
				}
				//mvprintw(2, (COLS-strlen("menu order is 12"))/2, "menu order is %2d", menu_order);
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
					sprintf((char*)_LocBuf, "a%03d%03d", iX_local, iY_local);
					iX_local_org = iX_local;
					iY_local_org = iY_local;
				}
				mvprintw(1, 120, "locbuf:%s", _LocBuf);
				//writeLocData((u8*)_LocBuf, 6);
				writeData((u8*)_LocBuf, 7);
				
				
				break;
			}
			default:
				break;
		}
		msleep(50);
	}
}
