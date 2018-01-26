#include "mapThread.h"

static unsigned char game_state = GAME_OVER;
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
//	starty = (LINES-height)/2;/*计算窗口中心位置的行数*/
//	startx = (COLS-width)/2;/*计算窗口中心位置的列数*/
	game_state = GAME_READY;
	
	for(int i = 0; i < sum_item; i++)
	{
		mvprintw((LINES - sum_item)/2 + i, (COLS-strlen(item[i]))/2, "%s", item[i]);
	}
	
	while(1)
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
			case KEY_ENTER:
				//socket thread start
				game_state = GAME_START;
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

void MapThread::game_panel()
{
	WINDOW* my_win;
	int startx, starty, width, height;
	height = LINES - 2;
	width = COLS;
	starty = (LINES-height)/2;/*计算窗口中心位置的行数*/
	startx = (COLS-width)/2;/*计算窗口中心位置的列数*/
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height,width,starty,startx);
}

bool MapThread::respond()
{
	int ch = 0, x = 1, y = 1;
	if(GAME_START != game_state)
		return false;
	while(1)
	{
		mvprintw(0, 30, " %03d,%03d ", x, y);
		ch = getch();
		if(KEY_F(1) == ch)
			break;
		switch (ch)
		{
			case KEY_DOWN:
				x++;
				break;
			case KEY_UP:
				x--;
				break;
			case KEY_LEFT:
				y--;
				break;
			case KEY_RIGHT:
				y++;
				break;
			default:
				break;
		}
		mvprintw(0, 50, "%d", ch);
	}
	refresh();
	endwin();
	return true;
}

void MapThread::run()
{
	while(GAME_START == game_state)
	{
		//show_update();
	}
}