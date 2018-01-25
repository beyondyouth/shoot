#if 0

#include <stdio.h>
#include "shootThread.h"


#define GAME_READY 1
#define GAME_START 2
#define GAME_OVER 0

static unsigned char game_status = 0;


int analyze(int iCmd, char* sCmd[]);
int create_room();
int join_room();
int get_keyboard();
void responding();

int main(int argc, char* argv[])
{
	analyze(argc, argv);
	while(game_status == GAME_OVER)
	{
		get_keyboard();
		responding();
	}
	return 0;
}

int get_keyboard()
{
	
}

void responding()
{
}

int create_room()
{
	Shoot InsShoot(SERVER);
	InsShoot.start();
	InsShoot.wait();
	return 0;
}

int join_room()
{
	Shoot InsShoot(CLIENT);
	InsShoot.start();
	InsShoot.wait();
	return 0;
}

int analyze(int iCmd, char* sCmd[])
{
	if(iCmd < 2)
		return -1;
	if(!strcmp(sCmd[1], "create"))
	{
		/*create socket server thread*/
		create_room();
	}
	else if(!strcmp(sCmd[1], "join"))
	{
		/*create socket client thread*/
		join_room();
	}
	return 0;
}

#else

#include <curses.h>
#include <ncurses.h>
#include <ctype.h>
int main()
{
	int ch;
	int i;
	int x, y;

	initscr();
	raw();
	keypad(stdscr, TRUE);

	mvprintw(0, 35, "%s", "F3 to exit");
	i = 0;
	x = 12 +  i / 40;
	y = 20 +  i % 40;
	mvprintw(23, 38, "%02d,%02d", x + 1 , y + 1);
	while ((ch = mvgetch(x, y)) != ERR) {
			if (isprint(ch)) {
					attron(A_BOLD);
					mvprintw(x - 6, y, "%c", ch);
					attroff(A_BOLD);
			}
			if(ch == KEY_F(3))
					break;
			i = (i + 1) % 240;
			x = 12 + i / 40;
			y = 20 + i % 40;
			mvprintw(23, 38, "%02d,%02d", x + 1, y + 1);
	}
	refresh();
	endwin();

	return 0;
}


#endif