#include <stdlib.h>
#include "mapThread.h"
#include "shootThread.h"
#include "sendThread.h"
#include "recvThread.h"


static Mode game_mode = MODE_UNKNOW;

Mode getGameMode()
{
	return game_mode;
}

static char* item[] = 
{
	(char*)"create room",
	(char*)"join room",
	(char*)"exit"
};

static int sum_item = sizeof(item)/sizeof(item[0]);

bool MapThread::init()
{
	initscr();
	cbreak();/*行缓冲禁止，传递所有控制信息*/
	keypad(stdscr, TRUE);/*程序需要使用F1功能键*/
	curs_set(0);/*隐藏光标*/
	bzero(localData, 6);
	bzero(remoteData, 6);
	game_state = GAME_MENU;
	return true;
}

WINDOW* MapThread::create_newwin(int height,int width,int starty,int startx)
{
	WINDOW* local_win;
	local_win = newwin(height,width,starty,startx);
	box(local_win, 0, 0);/*0,0是字符默认的行列起始位置*/
	wrefresh(local_win);/*刷新窗口缓冲，显示box*/
	return local_win;
}

void MapThread::destroy_win(WINDOW* local_win)
{
	wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

void MapThread::home()
{
	int ch = 0, i = -1;
	if(GAME_MENU != game_state)
		return;
	
	for(int i = 0; i < sum_item; i++)
	{
		mvprintw((LINES - sum_item)/2 + i, (COLS-strlen(item[i]))/2, "%s", item[i]);
	}
	
	while(GAME_MENU == game_state)
	{
		ch = getch();
		if(KEY_F(1) == ch)
		{
			game_state = GAME_OVER;
		}
		switch (ch)
		{
			case KEY_DOWN:
				i++;
				if(i == sum_item)i = 0;
				for(int j = 0; j < sum_item; j++)
				{
					if(j == i)
					{
						attron(A_BOLD);
					}
					mvprintw((LINES - sum_item)/2 + j, (COLS-strlen(item[j]))/2, "%s", item[j]);
					attroff(A_BOLD);
				}		
				break;
			case KEY_UP:
				i--;
				if(i == -1)i = sum_item - 1;
				for(int j = 0; j < sum_item; j++)
				{
					if(j == i)
					{
						attron(A_BOLD);
					}
					mvprintw((LINES - sum_item)/2 + j, (COLS-strlen(item[j]))/2, "%s", item[j]);
					attroff(A_BOLD);
				}	
				break;
			case KEY_F(2):
				if(!strcmp("create room", item[i]))
				{
					game_mode = MODE_SERVER;
					game_state = GAME_WAIT;
				}
				else if(!strcmp("join room", item[i]))
				{
					game_mode = MODE_CLIENT;
					game_state = GAME_WAIT;
				}
				else if(!strcmp("exit", item[i]))
				{
					game_state = GAME_OVER;
				}
				break;
			default:
				break;
		}
	}
	if(GAME_WAIT == game_state)
	{
		ShootThread* pInsShoot;
		pInsShoot = ShootThread::getInstance();
		pInsShoot->start();
		return;
	}
}

void MapThread::lobby()
{
	int ch = 0;
	char str[] = "waiting...";
	mvprintw(LINES - 1, (COLS-strlen(str))/2, "%s", str);
	if(GAME_WAIT != game_state)
		return;
	while(GAME_WAIT == game_state)
	{
		ch = getch();
		if(KEY_F(1) == ch)
		{
			game_state = GAME_OVER;
		}
	}
	if(GAME_READY == game_state)
		game_state = GAME_FIGHT;
}

void MapThread::fight()
{
	if(GAME_FIGHT != game_state)
		return;
	WINDOW* game_win;
	int startx, starty, width, height;
	height = LINES - 2;
	width = COLS;
	starty = (LINES-height)/2 + 1;/*计算窗口中心位置的行数*/
	startx = (COLS-width)/2;/*计算窗口中心位置的列数*/
//	printw("Press F1 to exit");
	refresh();
	game_win = create_newwin(height,width,starty,startx);
	
	respond(game_win);
}

void MapThread::exit()
{
	refresh();
	endwin();
}

WINDOW* my_win = NULL;

bool MapThread::respond(WINDOW* local_win)
{
	int ch = 0, c = COLS/2, l = LINES/2;
	int iX_local = COLS/2, iY_local = COLS/2;
	static int iX_local_org = COLS/2, iY_local_org = LINES/2;
	char sX_local[3] = {0}, sY_local[3] = {0};
	if(GAME_FIGHT != game_state)
		return false;
	my_win = local_win;
	while(GAME_FIGHT == game_state)
	{
		sprintf((char*)localData, "%03d%03d", c, l);
//		mvprintw(0, 10, "localData:%s", localData);
		memcpy(sX_local, localData, 3);
		memcpy(sY_local, localData + 3, 3);
			
		iX_local = atoi(sX_local);
		iY_local = atoi(sY_local);
		
		if(iY_local_org != iY_local || iX_local_org != iX_local)
		{
			mvwprintw(my_win, iY_local_org, iX_local_org, " ");
			mvwprintw(my_win, iY_local, iX_local, "l");
		}
		
		iX_local_org = iX_local;
		iY_local_org = iY_local;
			
		//mvprintw(0, 30, " %03d,%03d ", x, y);
		ch = getch();
		if(KEY_F(1) == ch)
		{
			game_state = GAME_OVER;
			break;
		}
		switch (ch)
		{
			case KEY_DOWN:
				if(l < LINES - 1)l++;
				break;
			case KEY_UP:
				if(l > 1)l--;
				break;
			case KEY_LEFT:
				if(c > 1)c--;
				break;
			case KEY_RIGHT:
				if(c < COLS - 1)c++;
				break;
			default:
				break;
		}
//		mvprintw(0, 50, "%d", ch);
	}
	return true;
}

void MapThread::run()
{
	int iX_remote = COLS/2, iY_remote = LINES/2;
	static int iX_remote_org = COLS/2, iY_remote_org = LINES/2;
	static int count = 0;
	char sX_remote[3] = {0}, sY_remote[3] = {0};
	char str[20] = "null";
	while(GAME_OVER != game_state)
	{
		if(LINK_SUCCESS == getLinkState() && GAME_WAIT == getGameState())
		{
			game_state = GAME_READY;
		}
	
		if(LINK_ABORT == getLinkState())
		{
			game_state = GAME_OVER;
		}
		
		if(GAME_READY == getGameState())
		{
			count++;
			if(count > 40)
				count = 0;
			if(count < 20)
				mvprintw(LINES - 1, (COLS-strlen("please press any key"))/2, "%s", "please press any key");
			else
				mvprintw(LINES - 1, (COLS-strlen("                    "))/2, "%s", "                    ");	
		}
		/*Map update*/
		writeData((u8*)localData, 6);
		readData((u8*)remoteData, 6);
		
		sprintf(str, "link_state:%d", getLinkState());
		mvprintw(0, (COLS - strlen(str))/2, "%s", str);
		
		if(NULL != my_win && 0 != remoteData[0])
		{
			memcpy(sX_remote, remoteData, 3);
			memcpy(sY_remote, remoteData + 3, 3);
			
			iX_remote = atoi(sX_remote);
			iY_remote = atoi(sY_remote);
			
			
			if(iY_remote_org != iY_remote || iX_remote_org != iX_remote)
			{
				mvwprintw(my_win, iY_remote_org, iX_remote_org, " ");
				mvwprintw(my_win, iY_remote, iX_remote, "r");
				
				iX_remote_org = iX_remote;
				iY_remote_org = iY_remote;
			}
		}
		wrefresh(my_win);
		
		msleep(50);
		refresh();
	}
}