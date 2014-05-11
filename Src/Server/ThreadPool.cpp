/*************************************************************************
	> File Name: ThreadPool.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时40分51秒
 ************************************************************************/

#include "ThreadPool.h"
#include <iostream>

using namespace std;

ThreadPool::ThreadPool():_thread_vector(THREAD_NUM), _cond(_lock), _is_pool_started(false)
{
	std::vector<WorkThread>::iterator iter = _thread_vector.begin();
	for(; iter != _thread_vector.end(); ++iter)
	{
		iter->register_thread_pool(this);
	}
	_cache_manage_thread.get_related(this);
}

void ThreadPool::start_thread_pool()
{
	if(_is_pool_started)
	{
		return ;
	}
	_is_pool_started = true;
	std::vector<WorkThread>::iterator iter = _thread_vector.begin();
	while(iter != _thread_vector.end())	//依次打开线程
	{
		iter->start();
		++iter;
	}
	_cache_manage_thread.start();	//启动管理线程
	LogInfo("Start the thread pool");
	cout << "Server already started." << endl;

}

void ThreadPool::stop_thread_pool()
{
	if(_is_pool_started)
	{
		_is_pool_started = false;
		_cond.notify_all();
		while(!_task_queue.empty())
		{
			_task_queue.pop();
		}
	}
	LogInfo("Stop thread pool.");
}

void ThreadPool::add_task(Task &task)
{
	_lock.lock();
	_task_queue.push(task);
	_lock.unlock();
	LogInfo("Add a task to queue.");
	cout << "Add a task" << endl;
	_cond.notify_all();
}

bool ThreadPool::get_task(Task &task)
{
	_lock.lock();
	while(_is_pool_started && _task_queue.empty())
	{
		_cond.wait();
	}
	if(_is_pool_started == false)
	{
		_cond.notify_all();
		return false;
	}
	task = _task_queue.front();
	_task_queue.pop();
	_lock.unlock();
	_cond.notify_all();
	LogInfo("Get a task from queue.");
	cout << "Get a task" << endl;
	return true;
}

vector<WorkThread>& ThreadPool::get_thread_vector()
{
	return _thread_vector;
}

ThreadPool::~ThreadPool()
{
	stop_thread_pool();
}
