#include <stdio.h>
#include <errno.h>
#include "Mutex.h"

#define MUTEX_SUCCESS 0

Mutex::Mutex()
{
	if (MUTEX_SUCCESS == pthread_mutex_init(&_mutexId, NULL))
	{
		return ;
	}
	printf(" Mutex Init Fail, errno = %d ",errno);
	return;
}

int Mutex::lock()
{
	if (MUTEX_SUCCESS == pthread_mutex_lock(&_mutexId))
	{
		return STATUS_OK;
	}
	printf(" Mutex Lock Fail, errno = %d ",errno);
	return STATUS_ERROR;
}

int Mutex::trylock()
{
	if (MUTEX_SUCCESS == pthread_mutex_trylock(&_mutexId))
	{
		return STATUS_OK;
	}
	printf(" Mutex Trylock Fail, errno = %d ",errno);
	return STATUS_ERROR;
}

int Mutex::unlock()
{
	if (MUTEX_SUCCESS == pthread_mutex_unlock(&_mutexId))
	{
		return STATUS_OK;
	}
	printf(" Mutex Unlock Fail, errno = %d ",errno);
	return STATUS_ERROR;
}

pthread_mutex_t Mutex::getId()
{
	return _mutexId;
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutexId);
}

MutexLocker::MutexLocker(Mutex* mutex) : _mutex(NULL)
{
	if (!mutex)
	{
		printf(" Mutexlocker Creat Fail, errno = %d ",errno);
		return;
	}
	_mutex = mutex;
	_mutex->lock();
}

MutexLocker::~MutexLocker()
{
	if (!_mutex)
	{
		return;
	}
	_mutex->unlock();
}
