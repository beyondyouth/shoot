#include "Thread.h"

class UnicastThread : public Thread
{
public:
	UnicastThread();
	~UnicastThread();
protected:
	virtual void run();
};