/*************************************************************************
	> File Name: Thread.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时24分24秒
 ************************************************************************/

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {
public:
	Thread();
	virtual ~Thread();

	void start();
private:
	pthread_t _pid;
	pthread_attr_t _attr;
	bool _is_thread_started;
	static void* thread_func(void *);
	virtual void run() = 0;
};

#endif
