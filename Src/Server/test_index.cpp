/*************************************************************************
	> File Name: test_index.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月11日 星期日 16时41分13秒
 ************************************************************************/

#include "Index.h"
using namespace std;

int main()
{
	Index index;
	index.read_dictionary();
	index.debug();
	return 0;
}
