/*************************************************************************
	> File Name: Thread.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时30分18秒
 ************************************************************************/

#include "Thread.h"
#include "Log.h"

#include <stdexcept>

Thread::Thread():_pid(0), _is_thread_started(false)
{
	pthread_attr_init(&_attr);
}

void Thread::start()
{
	if(_is_thread_started)
	{
		return ;
	}
	_is_thread_started = true;

	//设置pthread_create的第二个属性，使得线程不需要join
	if(pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED))	
	{
		LogFatal("pthread_attr_setdetachstate error!");	
		throw std::runtime_error("pthread_attr_setdetachstate");
	}

	if(pthread_create(&_pid, &_attr, thread_func, this))
	{
		LogFatal("pthread creat error!");
		throw std::runtime_error("pthread create");
	}

	_cache.get_disk_cache();	//每个线程开始的时候都读取cache文件

}

void* Thread::thread_func(void *arg)
{
	Thread* p = (Thread*)arg;
	p->run();
	return NULL;
}

/* for test
void Thread::run()
{
	std::cout << "run" << std::endl;
}
*/

Thread::~Thread()
{
	pthread_attr_destroy(&_attr);
}
