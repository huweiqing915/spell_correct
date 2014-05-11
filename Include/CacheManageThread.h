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

#define WRITE_TIME 60

class WorkThread;
class ThreadPool;

class CacheManageThread : public Thread {
public:
	CacheManageThread();
	~CacheManageThread() {}
	void get_related(ThreadPool * p);	//注册到线程池中
	
	void get_threadpool_vector();	//获得线程池中其他工作线程的vector
	void scan_thread_map();		//扫描其他各个线程的cache
	
	void run();

private:
	ThreadPool *_p_thread_pool;
	std::vector<WorkThread> _threadpool_vector;	//用来存储其他的线程
//	std::unordered_map<std::string, std::string> _thread_map;	//属于该线程的map，用于收集所有其他线程的cache
};

#endif

