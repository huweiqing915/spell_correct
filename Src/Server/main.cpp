/*************************************************************************
	> File Name: main.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时42分11秒
 ************************************************************************/

#include "ThreadPool.h"
#include "UDPServer.h"
#include "Config.h"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	string ip , port ;
	Config *p_server = Config::get_instance();
	p_server->get_file_name(string("server_ip"), ip);
	p_server->get_file_name(string("server_port"), port);
	//开启服务器
	UDPServer server(ip, port);
	//开启线程池
	server.open_thread_pool();

	return 0;
}
