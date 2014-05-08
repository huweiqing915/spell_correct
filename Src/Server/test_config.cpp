/*************************************************************************
	> File Name: test_config.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 19时56分50秒
 ************************************************************************/

#include <iostream>
#include <string>
#include "Config.h"
using namespace std;

int main()
{
	Config config("config.txt");
	string filename = "a.txt";
	string path;
	config.get_file_path(filename, path);
	cout << path << endl;
	return 0;
}
