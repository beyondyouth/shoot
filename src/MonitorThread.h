#ifndef MONITOR_THREAD_H__
#define MONITOR_THREAD_H__

#include "thread.h"

class MonitorThread : public Thread
{
public:
	MonitorThread();
	~MonitorThread();
	friend setAdvance();
protected:
	virtual void run();
private:
	bool advance_state;
};

#endif