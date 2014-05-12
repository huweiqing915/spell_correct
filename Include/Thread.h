/*************************************************************************
	> File Name: Thread.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时24分24秒
 ************************************************************************/
/*
 *  该类为抽象基类，不能用来创建对象，只能用来继承
 */
#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <stdexcept>
#include "Cache.h"

class Thread {
public:
	Thread();
	virtual ~Thread();

	void start();	//启动线程
protected:
	Cache _cache;	//属于每个线程自己的cache
private:
	pthread_t _pid;
	pthread_attr_t _attr;
	bool _is_thread_started;

	static void* thread_func(void *);  //设成静态的，为了消除this指针
	virtual void run() = 0;	 //纯虚函数
};

#endif
