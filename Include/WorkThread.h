/*************************************************************************
	> File Name: WorkThread.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时21分28秒
 ************************************************************************/

#ifndef WORK_THREAD_H_
#define WORK_THREAD_H_

#include <unordered_map>
#include <map>
	
#include "Thread.h"
#include "Cache.h"
#include "Log.h"

class ThreadPool;	//因为本文件与ThreadPool类相互include，所以在此处要用前向声明

class WorkThread : public Thread {	//继承父类Thread
public: 
	void register_thread_pool(ThreadPool *);	//与线程池取得联系
	Cache& get_thread_cache();
private:
	void run();	
	ThreadPool *_p_thread_pool;
	std::unordered_map<std::string, std::map<std::string, int> > _index;
};

#endif
