/*************************************************************************
	> File Name: CacheThread.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月10日 星期六 01时37分56秒
 ************************************************************************/

#ifndef CACHE_THREAD_H_
#define CACHE_THREAD_H_ 

#include "Cache.h"
#include "Thread.h"

#include <vector>

class WorkThread;
class ThreadPool;

class CacheManageThread : public Thread {
public:
	CacheManageThread() {}
	~CacheManageThread() {}
	void get_related(ThreadPool * p);
	void scan_thread_map();
	void get_threadpool_vector();
	void run();

private:
	ThreadPool *_p_thread_pool;
	std::vector<WorkThread> _threadpool_vector;
	std::unordered_map<std::string, std::string> _thread_map;	//属于该线程的map，用于收集所有其他线程的cache
};

#endif

