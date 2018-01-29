#ifndef MONITOR_THREAD_H__
#define MONITOR_THREAD_H__

#include "Thread.h"

class MonitorThread : public Thread
{
public:
	MonitorThread();
	~MonitorThread();
	friend void setAdvance();
protected:
	virtual void run();
private:
	
};

#endif