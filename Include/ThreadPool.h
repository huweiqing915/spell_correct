/*************************************************************************
	> File Name: ThreadPool.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时40分42秒
 ************************************************************************/
/*
 *  线程池类，存有所有的工作线程
 */
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "MutexLock.h"
#include "Condition.h"
#include "WorkThread.h"
#include "CacheManageThread.h"
#include "Task.h"
#include "Log.h"
#include "Index.h"

#include <vector>
#include <queue>

#define THREAD_NUM 5	//线程的最大数量

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void start_thread_pool();
	void stop_thread_pool();

	void add_task(Task&);
	bool get_task(Task&);

	std::vector<WorkThread>& get_thread_vector();	//获得WorkThread的Vector，提供给CacheManageThread
	Index::_index_map& get_index_table();	//用来给线程获得索引表
private:
	std::vector<WorkThread> _thread_vector;
	CacheManageThread _cache_manage_thread;
	std::queue<Task> _task_queue;
	bool _is_pool_started;
	MutexLock _lock;
	Condition _cond;
	Index _index;
};

#endif
