/*************************************************************************
	> File Name: main.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 14时42分11秒
 ************************************************************************/

#include "ThreadPool.h"
#include "UDPServer.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
//	cout << "input server config file:"<< endl;
//	string server_conf;
//	cin >> server_conf;
//	UDPServer server(server_conf);
	ifstream fin("/var/www/spell_correct/Conf/server.conf");
	string ip , port ;
	fin >> ip >> port ;
//	cout << ip << " " << port << endl;
	fin.close();
	
	UDPServer server(ip, port);
	server.open_thread_pool();

	return 0;
}
