/*************************************************************************
	> File Name: test_textquery.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月04日 星期日 22时46分09秒
 ************************************************************************/

#include "TextQuery.h"
using namespace std;

int main()
{
	TextQuery tq;
	tq.read_file("../../Data/big.txt");
	tq.build_map();
	tq.write_file();
	return 0;
}

