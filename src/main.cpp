#if 1

#include <stdio.h>

#include "shootThread.h"
#include "mapThread.h"

int main(int argc, char* argv[])
{
	MapThread InsMap;
	InsMap.init();//curses初始化，进入curses界面
	InsMap.start();//开始界面刷新线程，可用于调式
	InsMap.home();//主界面
	InsMap.lobby();//大厅
	InsMap.fight();//游戏界面
	return 0;
}


#else

#include <ctype.h>
#include <ncurses.h>

WINDOW* create_newwin(int height,int width,int starty,int startx);
void destroy_win(WINDOW* local_win);
int main(int argc,char* argv[])
{
	WINDOW* my_win;
	int startx,starty,width,height;
	int ch;
	initscr();
	cbreak();/*行缓冲禁止，传递所有控制信息*/
	keypad(stdscr,TRUE);/*程序需要使用F1功能键*/
	height=3;
	width=10;
	starty=(LINES-height)/2;/*计算窗口中心位置的行数*/
	startx=(COLS-width)/2;/*计算窗口中心位置的列数*/
	printw("PressF1toexit");
	refresh();
	my_win=create_newwin(height,width,starty,startx);

	while((ch=getch())!=KEY_F(1))
	{
		switch(ch)
		{
			case KEY_LEFT:
				destroy_win(my_win);
				my_win=create_newwin(height,width,starty,--startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win=create_newwin(height,width,starty,++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win=create_newwin(height,width,--starty,startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win=create_newwin(height,width,++starty,startx);
				break;
		}
		mvwprintw(my_win, 1, 3, "hello");
		wrefresh(my_win);
	}
	endwin();/*结束curses模式*/
	return 0;
}

WINDOW* create_newwin(int height,int width,int starty,int startx)
{
	WINDOW* local_win;
	local_win = newwin(height,width,starty,startx);
	box(local_win, 0, 0);/*0,0是字符默认的行列起始位置*/
	wrefresh(local_win);/*刷新窗口缓冲，显示box*/
	return local_win;
}

void destroy_win(WINDOW* local_win)
{
	wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}



#endif