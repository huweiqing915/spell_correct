/*************************************************************************
	> File Name: test_log.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 14时34分17秒
 ************************************************************************/

#include "Log.h"

int main()
{
	int a = 2;
	if(a > 1)
	{
		LogFatal("line[%d:%s] is illegal.", a, "hello");
	}
	return 0;
}
