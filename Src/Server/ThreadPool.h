/*************************************************************************
	> File Name: ThreadPool.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时40分42秒
 ************************************************************************/

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "MutexLock.h"
#include "Condition.h"
#include "WorkThread.h"
#include "Task.h"
#include <vector>
#include <queue>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void start_thread_pool();
	void stop_thread_pool();

	void add_task(Task&);
	bool get_task(Task&);

private:
	std::vector<WorkThread> _thread_vector;
	std::queue<Task> _task_queue;
	bool _is_pool_started;
	MutexLock _lock;
	Condition _cond;
};

#endif
