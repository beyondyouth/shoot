#ifndef KEY_THREAD_H__
#define KEY_THREAD_H__

#include "Thread.h"

class KeyThread : public Thread
{
	protected:
	virtual void run();
};

#endif