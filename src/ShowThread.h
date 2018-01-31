#ifndef MAP_THREAD_H__
#define MAP_THREAD_H__

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
	u8 localData[6];
	u8 remoteData[6];
	WINDOW* childWin;
};

void debug(char* buffer);

#endif/*MAP_THREAD_H__*/