#ifndef MAP_THREAD_H__
#define MAP_THREAD_H__

#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include "thread.h"

#define GAME_READY 1
#define GAME_START 2
#define GAME_OVER 0

class MapThread : public Thread
{

public:
	bool init();
	WINDOW* create_newwin(int height,int width,int starty,int startx);
	void destroy_win(WINDOW* local_win);
	void main_menu();
	void game_panel();
	bool respond();
protected:
	virtual void run();
	
};

#endif/*MAP_THREAD_H__*/