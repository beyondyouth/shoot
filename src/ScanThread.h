#ifndef SCAN_THREAD_H__
#define SCAN_THREAD_H__

#include "Thread.h"

class ScanThread : public Thread
{
public:
	ScanThread();
	~ScanThread();
protected:
	virtual void run(void);
private:

};

#endif/*SCAN_THREAD_H__*/
