#include <stdlib.h>
#include "mapThread.h"
#include "shootThread.h"
#include "sendThread.h"
#include "recvThread.h"

static u8 game_state = GAME_OVER;
u8 getGame_state()
{
	return game_state;
}
static char* item[] = 
{
	(char*)"create room",
	(char*)"join room",
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
	game_state = GAME_READY;
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

void MapThread::main_menu()
{
	int ch = 0, i = -1;
	if(GAME_READY != game_state)
		return;
	
	for(int i = 0; i < sum_item; i++)
	{
		mvprintw((LINES - sum_item)/2 + i, (COLS-strlen(item[i]))/2, "%s", item[i]);
	}
	
	while(GAME_READY == game_state)
	{
		ch = getch();
		if(KEY_F(1) == ch)
			break;
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
					ShootThead::create_room();
					game_state = GAME_LINK;
				}
				else if(!strcmp("join room", item[i]))
				{
					ShootThead::join_room();
					game_state = GAME_LINK;
				}
				break;
			default:
				break;
		}
	}
	if(KEY_F(1) == ch)
	{
		refresh();
		endwin();
		return;
	}
}

WINDOW* game_win = NULL;

void MapThread::game_panel()
{
//	WINDOW* game_win;
	int startx, starty, width, height;
	height = LINES - 2;
	width = COLS;
	starty = (LINES-height)/2;/*计算窗口中心位置的行数*/
	startx = (COLS-width)/2;/*计算窗口中心位置的列数*/
//	printw("Press F1 to exit");
	refresh();
	game_win = create_newwin(height,width,starty,startx);
}

bool MapThread::respond()
{
	int ch = 0, x = COLS/2, y = LINES/2;
	if(GAME_START != game_state)
		return false;
	while(1)
	{
		sprintf((char*)localData, "%03d%03d", x, y);
		//mvprintw(0, 30, " %03d,%03d ", x, y);
		ch = getch();
		if(KEY_F(1) == ch)
			break;
		switch (ch)
		{
			case KEY_DOWN:
				if(x < COLS - 1)x++;
				break;
			case KEY_UP:
				if(x > 1)x--;
				break;
			case KEY_LEFT:
				if(y > 1)y--;
				break;
			case KEY_RIGHT:
				if(y < LINES - 1)y++;
				break;
			default:
				break;
		}
//		mvprintw(0, 50, "%d", ch);
	}
	refresh();
	endwin();
	return true;
}

void MapThread::run()
{
	int iX_local = COLS/2, iY_local = LINES/2;
	int iX_remote = COLS/2, iY_remote = LINES/2;
	
	char sX_local[3] = {0}, sY_local[3] = {0};
	char sX_remote[3] = {0}, sY_remote[3] = {0};
	while(GAME_OVER != game_state)
	{
		if(LINK_SUCCESS == getLink_state())
			game_state = GAME_START;
		/*Map update*/
//		memcpy((char*)localData, "hello ", 6);
		mvprintw(0, 10, "localData:%s", localData);
		writeData((u8*)localData, 6);

		readData((u8*)remoteData, 6);
		mvprintw(0, 80, "remoteData:%s", remoteData);
		
		mvprintw(0, 40, "lin_state:%d", getLink_state());
		
		if(NULL != game_win)
		{
//			mvwprintw(game_win, x_local, y_local, " ");
//			mvwprintw(game_win, x_remote, y_remote, " ");
			memcpy(sX_local, localData, 3);
			memcpy(sY_local, localData + 3, 3);
			
			iX_local = atoi(sX_local);
			iY_local = atoi(sY_local);		
			
			memcpy(sX_remote, remoteData, 3);
			memcpy(sY_remote, remoteData + 3, 3);
			
			iX_remote = atoi(sX_remote);
			iY_remote = atoi(sY_remote);
			
			mvwprintw(game_win, iX_local, iY_local, "l");
			mvwprintw(game_win, iX_remote, iY_remote, "r");
			
			wrefresh(game_win);
		}
		
		msleep(10);
		refresh();
	}
}