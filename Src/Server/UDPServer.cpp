/*************************************************************************
	> File Name: UDPServer.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月24日 星期四 20时51分26秒
 ************************************************************************/

#include "UDPServer.h"
#include "Task.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

UDPServer::UDPServer(const string &ip, const string &port):_ip(ip), _port(port)
{
	_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(_fd == -1)
	{
		throw runtime_error("Create socket fail!");
	}
	server_bind();
}

void UDPServer::server_bind()
{
	memset(&_server_addr, 0, sizeof(_server_addr));
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons(atoi(_port.c_str()));
	_server_addr.sin_addr.s_addr = inet_addr(_ip.c_str());
	if(bind(_fd, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) == -1)
	{
		throw runtime_error("Bind port failed!");
	}
}
/*
void UDPServer::open_pool(ThreadPool::max_thread_num num)
{
	ThreadPool tp(num);
	tp.start_thread_pool();
}
*/

void UDPServer::open_thread_pool()
{
	tp.start_thread_pool();
	while(true)
	{
		receive();
	}
}

UDPServer::~UDPServer()
{
	close(_fd);
}

void UDPServer::receive()
{
//	const std::size_t SIZE = 1024;
//	char buf[SIZE];
	Task tmp;
	size_t len = sizeof(tmp._client_addr);
	memset(&tmp._client_addr, 0, len);
	char recv_buf[1024] = "";
	int n_read = recvfrom(_fd, recv_buf, 1024, 0, (struct sockaddr*)&tmp._client_addr, &len);
	recv_buf[n_read] = '\0';
	
	cout << "Receive from client:" << recv_buf << endl;
	tmp.recv_word(recv_buf);
	tmp._server_sockfd = _fd;
//	return string(buf);
//	return tmp;
	tp.add_task(tmp);
}

void UDPServer::send(Task &task)
{
	size_t len = sizeof(task._client_addr);
//	const size_t SIZE = 1024;
//	char buf[SIZE];
//	strcpy(buf, s.c_str());
	string send_recv = task.get_word();
	int n_send = sendto(_fd, send_recv.c_str(), 1024, 0, (struct sockaddr*)& task._client_addr, len);
	if(n_send < 0)
	{
		throw runtime_error("Server send error!");
	}
}










