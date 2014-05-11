/*************************************************************************
	> File Name: CacheManageThread.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月10日 星期六 01时37分32秒
 ************************************************************************/

#include "CacheManageThread.h"
#include "WorkThread.h"
#include "Cache.h"
#include "ThreadPool.h"
using namespace std;

void CacheManageThread::get_related(ThreadPool * p)
{
	_p_thread_pool = p;
}

void CacheManageThread::get_threadpool_vector()
{
	_threadpool_vector = _p_thread_pool -> get_thread_vector();
}

void CacheManageThread::scan_thread_map()
{
	get_threadpool_vector();
	for(vector<WorkThread>::iterator iter = _threadpool_vector.begin(); iter != _threadpool_vector.end(); ++iter)
	{
		//把各个线程的hash_map收集到一起
		_cache.add_thread_hash(iter->get_thread_cache().get_hash_map(), _thread_map);
	}
}

void CacheManageThread::run()
{
	while(true)
	{
		
	}
}