#include <stdlib.h>
#include "ShowThread.h"
#include "ShootThread.h"
#include "KeyThread.h"
#include "RecvThread.h"

extern Node* head;
extern Node* getKeyNode();

int iX_remote = COLS/2, iY_remote = LINES/2;
char sX_remote[4] = {0};
char sY_remote[4] = {0};

int iX_local = COLS/2, iY_local = COLS/2;
char sX_local[4] = {0};
char sY_local[4] = {0};

bool ShowThread::init()
{
	initscr();
	cbreak();/*行缓冲禁止，传递所有控制信息*/
	keypad(stdscr, TRUE);/*程序需要使用F1功能键*/
	curs_set(0);/*隐藏光标*/
	childWin = NULL;
	return true;
}

WINDOW* ShowThread::create_newwin(int height,int width,int starty,int startx)
{
	WINDOW* local_win;
	local_win = newwin(height,width,starty,startx);
	box(local_win, 0, 0);/*0,0是字符默认的行列起始位置*/
	wrefresh(local_win);/*刷新窗口缓冲，显示box*/
	return local_win;
}

void ShowThread::destroy_win(WINDOW* local_win)
{
	wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

void ShowThread::home()
{
	int i = 0;
	if(NULL == head)
	{
		return;
	}
	Node* p = head;
	for(; p->next != NULL; p = p->next)
	{
		mvprintw((LINES - getlen())/2 + i, (COLS-strlen(p->data))/2, "%s", p->data);/*显示ip列表*/
		i++;
	}
	mvprintw((LINES - getlen())/2 + i, (COLS-strlen(p->data))/2, "%s", p->data);
}


void ShowThread::lobby()
{
}

void ShowThread::fight()
{
	int startx, starty, width, height;
	height = LINES - 2;
	width = COLS;
	starty = (LINES-height)/2 + 1;/*计算窗口中心位置的行数*/
	startx = (COLS-width)/2;/*计算窗口中心位置的列数*/
//	printw("Press F1 to exit");
	refresh();
	childWin = create_newwin(height,width,starty,startx);
}

void ShowThread::exit()
{
	refresh();
	endwin();
}

void ShowThread::run()
{
//	static int iX_remote_org = COLS/2, iY_remote_org = LINES/2;
//	static int iX_local_org = COLS/2, iY_local_org = LINES/2;
	init();
	home();
	while(GAME_EXIT != getGameState())
	{
		switch(getGameState())
		{
			case GAME_SELECT:
			{
				int i = 0;
				if(NULL == head)
				{
					break;
				}
				/*sp:选中的节点*/
				Node* sp = getKeyNode();
				Node* p = head;
				for(; p->next != NULL; p = p->next)
				{
					if(p == sp)
						attron(A_BOLD);
					mvprintw((LINES - getlen())/2 + i, (COLS-strlen(p->data))/2, "%s", p->data);/*显示ip列表*/
					i++;
					attroff(A_BOLD);
				}
				i++;
				if(p == sp)
					attron(A_BOLD);
				mvprintw((LINES - getlen())/2 + i, (COLS-strlen(p->data))/2, "%s", p->data);
				attroff(A_BOLD);
				break;
			}
			case GAME_FIGHT:
			{
				fight();
				if(false == readRecvBuf((u8*)sX_remote, 3, 0))
					break;
				if(false == readRecvBuf((u8*)sY_remote, 3, 3))
					break;
				mvprintw(1, COLS-21, "X:%s Y:%s", sX_remote, sY_remote);
				iX_remote = atoi(sX_remote);
				iY_remote = atoi(sY_remote);
				mvwprintw(childWin, iY_remote, iX_remote, "r");
				
				readLocalBuf((u8*)sX_local, 3, 0);
				readLocalBuf((u8*)sY_local, 3, 3);
				mvprintw(1, 10, "X:%s Y:%s", sX_local, sY_local);
				iX_local = atoi(sX_local);
				iY_local = atoi(sY_local);
				mvwprintw(childWin, iY_local, iX_local, "l");

				wrefresh(childWin);
				break;
			}
			default:
				break;
			
		}
		refresh();
		msleep(50);
	}
	exit();
}


	
