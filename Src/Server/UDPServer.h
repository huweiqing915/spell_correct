/*************************************************************************
	> File Name: UDPServer.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月24日 星期四 20时17分15秒
 ************************************************************************/

#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <stdexcept>
#include "ThreadPool.h"

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
	void receive();
};

#endif 
