#include "KeyThread.h"

static int key_value = 0;
int iX_local = COLS/2, iY_local = COLS/2;
char sX_local[3] = {0}, sY_local[3] = {0};

int getKeyValue()
{
	int temp = key_value;
	key_value = 0;
	return temp;
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
				/*if localData changed*/
				if(iY_local_org != iY_local || iX_local_org != iX_local)
				{
					sprintf((char*)localData, "%03d%03d", iX_local, iY_local);
					iX_local_org = iX_local;
					iY_local_org = iY_local;
				}
				writeData((u8*)localData, 6);
				break;
			}
		}
		sleep(50);
	}
}
