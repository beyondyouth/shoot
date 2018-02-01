#ifndef KEY_THREAD_H__
#define KEY_THREAD_H__

#include "Thread.h"

#define TTY_PATH "/dev/tty"
#define STTY_US "stty raw -echo -F "
#define STTY_DEF "stty -raw echo -F "

#define EV_ENTER 10

class KeyThread : public Thread
{
public:
	bool init();
	int get_char();
protected:
	virtual void run();
private:
	G_state game_state;
	int key_value;
};

#endif