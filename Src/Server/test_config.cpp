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
	Config *p_config = Config::get_instance();
	string ip, port;
	p_config->get_file_name(string("server_ip"), ip);
	p_config->get_file_name(string("server_port"), port);
	cout << ip << " " << port << endl;
	return 0;
}
