#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include "KeyThread.h"
#include "SendThread.h"
#include "Mutex.h"

extern Node* head;
static u8 _localBuf[MAXDATASIZE] = {0};
static Mutex* pLocalMux = new Mutex();

bool readLocalBuf(u8* buf, u32 len, u32 offset)
{
	pLocalMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pLocalMux->unlock();
		return false;
	}
	memcpy(buf, _localBuf + offset, len);
	pLocalMux->unlock();
	return true;
}

bool writeLocalBuf(u8* buf, u32 len, u32 offset)
{
	pLocalMux->lock();
	if(offset + len > MAXDATASIZE)
	{
		pLocalMux->unlock();
		return false;
	}
	memcpy(_localBuf + offset, buf, len);
	pLocalMux->unlock();
	return true;
}

static Node* pKeyNode = NULL;
Node* getKeyNode()
{
	return pKeyNode;
}

static G_signal sign = SIGN_NO;
G_signal getSignal()
{
	return sign;
}

void setSignal(G_signal S)
{
	sign = S;
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
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
	{
        ch = getch();
    }
    return ch;
}

void KeyThread::run()
{
	init();
	static int iX_local = COLS/2, iY_local = LINES/2;

	while(GAME_EXIT != getGameState())
	{
		key_value = get_char();
		if(key_value == 3)
		{
			setSignal(SIGN_EXIT);
            //system(STTY_DEF TTY_PATH);
            break;
        }
		if(NULL == pKeyNode)
			pKeyNode = head;
		switch(getGameState())
		{
			case GAME_SELECT:
			{
				//mvprintw(1, (COLS-strlen("key value is 12"))/2, "key value is %2d", key_value);
				switch (key_value)
				{
					case KEY_DOWN:
					{
						if(NULL == pKeyNode)
							break;
						if(NULL == pKeyNode->next)
							break;
						pKeyNode = pKeyNode->next;
						break;
					}
					case KEY_UP:
					{
						if(NULL == pKeyNode)
							break;
						if(NULL == pKeyNode->prev)
							break;
						pKeyNode = pKeyNode->prev;
						break;
					}
					case EV_ENTER:
					{
						/*进入link阶段*/
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
				pLocalMux->lock();
				sprintf((char*)_localBuf, "%03d%03d", iX_local, iY_local);
				pLocalMux->unlock();

				writeSendBuf((u8*)_localBuf, 6);			
				break;
			}
			default:
				break;
		}
		msleep(50);
	}
}
