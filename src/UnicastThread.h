#ifndef UNICAST_THREAD_H__
#define UNICAST_THREAD_H__

#include "Thread.h"

class UnicastThread : public Thread
{
public:
	UnicastThread();
	~UnicastThread();
protected:
	virtual void run();
};

#endif/*UNICAST_THREAD_H__*/
