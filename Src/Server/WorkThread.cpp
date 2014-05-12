/*************************************************************************
	> File Name: WorkThread.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时24分58秒
 ************************************************************************/

#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"

void WorkThread::register_thread_pool(ThreadPool *p)
{
	_p_thread_pool = p;
}

void WorkThread::run()
{
	while(true)
	{
		Task task;
		/*
		 * 如果获取任务时，返回值为false，那么说明线程池已经关闭，所以
		 * 此时线程需要退出死循环
		 */
		if(!_p_thread_pool->get_task(task))
		{
			LogError("Get task error, thread pool is closed!");
			break;
		}
		/*
		 *  用线程自己的cache来查找
		 *  传cache，传index，得考虑更好的传递的方法，不能都通过这个接口传递数据(单例,指针)
		 */
		task.excute_task(_cache.get_hash_map(), _p_thread_pool->get_index_table()); 

		sleep(1);
	}
}

Cache& WorkThread::get_thread_cache()
{
	return _cache;	
}
