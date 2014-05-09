/*************************************************************************
	> File Name: Log.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 10时51分09秒
 ************************************************************************/

#include "Log.h"
#include <stdexcept>

using namespace std;

void Log::Logging(size_t level, const string &msg, const char *fileName, int lineno)
{
	assert(level <= LL_FATAL);
	FILE *fp;
	char buf[CSTR_BUFFER_SIZE];
	if((fp = fopen("../../Log/log.txt", "a+")) == NULL )
	{
		throw runtime_error("open log.txt failed!");
	}
	time_t timeNow;
	struct tm *tm_ptr;
	(void)time(&timeNow);
	tm_ptr = localtime(&timeNow);
	strftime(buf, sizeof(buf), LOG_TIME_FORMAT, tm_ptr);
	fprintf(fp, LOG_FORMAT, buf, fileName, lineno, LOG_LEVEL_ARRAY[level], msg.c_str());
	fclose(fp);
}


void Log::LoggingF(size_t level, const char *fileName, int lineno, const string &format, ...)
{
#ifdef LOGGER_LEVEL
	if(level < LOGGER_LEVEL) return;
#endif
	int size = 256;
	string msg;
	va_list args;
	while (1) 
	{
		msg.resize(size);
		va_start(args, format);
		int n = vsprintf((char *)msg.c_str(), format.c_str(), args);
		va_end(args);
		if (n > -1 && n < size) 
		{
			msg.resize(n);
			break;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	Logging(level, msg, fileName, lineno);
}