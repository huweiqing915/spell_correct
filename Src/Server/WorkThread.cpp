/*************************************************************************
	> File Name: WorkThread.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时24分58秒
 ************************************************************************/

#include "WorkThread.h"
#include "Task.h"
#include "ThreadPool.h"
#include <iostream>

void WorkThread::register_thread_pool(ThreadPool *p)
{
	_p_thread_pool = p;
}

void WorkThread::run()
{
	while(true)
	{
		Task task;
		if(!_p_thread_pool->get_task(task))
		{
			std::cout << "get task error" << std::endl;
			break;
		}
		task.excute_task();
		sleep(1);
	}
}
