/*************************************************************************
	> File Name: UDPServer.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月24日 星期四 20时17分15秒
 ************************************************************************/

#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include <iostream>
#include <string>
#include <stdexcept>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "ThreadPool.h"
#include "Log.h"

class UDPServer {
public:
	UDPServer(const std::string&, const std::string&);
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
