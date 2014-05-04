/*************************************************************************
	> File Name: WorkThread.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时21分28秒
 ************************************************************************/

#ifndef WORK_THREAD_H_
#define WORK_THREAD_H_

#include "Thread.h"

class ThreadPool;
class WorkThread : public Thread {
public:
	void register_thread_pool(ThreadPool*);
private:
	void run();
	ThreadPool *_p_thread_pool;
};

#endif
