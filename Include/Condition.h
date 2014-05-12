/*************************************************************************
	> File Name: Condition.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时18分41秒
 ************************************************************************/

#ifndef CONDITION_H_
#define CONDITION_H_

#include <pthread.h>
#include <stdexcept>

#include "MutexLock.h"
#include "Log.h"

class Condition {
public:
	Condition(MutexLock &lock):_lock(lock)
	{
		if(pthread_cond_init(&_cond, NULL))
		{
			LogFatal("Init pthread condition");
			throw std::runtime_error("Condition");
		}
	}

	void wait()
	{
		pthread_cond_wait(&_cond, &_lock._mutex);
	}

	void notify_all()
	{
		pthread_cond_broadcast(&_cond);
	}

	~Condition()
	{
		pthread_cond_destroy(&_cond);
	}
private:
	MutexLock &_lock;
	pthread_cond_t _cond;

	Condition(const Condition&);	//禁止复制与拷贝
	Condition& operator=(const Condition&);
};

#endif
