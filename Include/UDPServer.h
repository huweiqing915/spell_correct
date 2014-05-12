/*************************************************************************
	> File Name: UDPServer.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月24日 星期四 20时17分15秒
 ************************************************************************/
/*
 *  服务器类，负责接受客户端client的数据
 */

#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include <stdexcept>
#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "ThreadPool.h"
#include "Log.h"

#define MAX_BUF_SIZE 1024

class UDPServer {
public:
	UDPServer(const std::string &ip, const std::string &port); //初始化须提供ip，port
	virtual ~UDPServer();
	
//	void start_pool(ThreadPool::max_thread_num);
	void open_thread_pool();	
	void send(Task&);
private:
	int _fd;
	struct sockaddr_in _server_addr;
	std::string _ip;
	std::string _port;
	void server_bind();
	ThreadPool tp;

	void receive();	//负责收信息
};

#endif 
