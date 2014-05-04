/*************************************************************************
	> File Name: MutexLock.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时15分00秒
 ************************************************************************/

#ifndef MUTEX_LOCK_H_
#define MUTEX_LOCK_H_

#include <pthread.h>

class MutexLock {
public:
	friend class Condition;
	MutexLock()
	{
		pthread_mutex_init(&_mutex, NULL);
	}
	void lock()
	{
		pthread_mutex_lock(&_mutex);
	}

	void unlock()
	{
		pthread_mutex_unlock(&_mutex);
	}

	~MutexLock()
	{
		pthread_mutex_destroy(&_mutex);
	}
private:
	pthread_mutex_t _mutex;
};

#endif
