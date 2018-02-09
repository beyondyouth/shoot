#ifndef SHOW_THREAD_H__
#define SHOW_THREAD_H__

#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include "Thread.h"


class ShowThread : public Thread
{

public:
	bool init();
	void home();
	void lobby();
	void fight();
	void exit();
	
protected:
	virtual void run();
	WINDOW* create_newwin(int height,int width,int starty,int startx);
	void destroy_win(WINDOW* local_win);
	bool respond(WINDOW* local_win);
	
private:
	WINDOW* childWin;
};

#endif/*SHOW_THREAD_H__*/