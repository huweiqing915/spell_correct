/*************************************************************************
	> File Name: UDPServer.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月24日 星期四 20时51分26秒
 ************************************************************************/

#include "UDPServer.h"
#include "Task.h"

using namespace std;

UDPServer::UDPServer(const string &ip, const string &port):_ip(ip), _port(port)
{
	//socket
	_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(_fd == -1)
	{
		LogFatal("Server create socket failed!");
		throw runtime_error("Server create socket fail!");
	}
	//bind
	server_bind();
}

void UDPServer::server_bind()
{
	memset(&_server_addr, 0, sizeof(_server_addr));
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons(atoi(_port.c_str())); //本地转换成网络port
	_server_addr.sin_addr.s_addr = inet_addr(_ip.c_str()); //转换成网络字节序
	if(bind(_fd, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) == -1)
	{
		LogFatal("Server bind port failed!");
		throw runtime_error("Bind port failed!");
	}
}

//打开线程池的另一种方式，可以指定最大的线程数量
/*
void UDPServer::open_pool(ThreadPool::max_thread_num num)
{
	ThreadPool tp(num);
	tp.start_thread_pool();
}
*/

void UDPServer::open_thread_pool()
{
	tp.start_thread_pool();  //开启线程池
	while(true)	//服务器只负责一直收
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
	Task tmp;
	size_t len = sizeof(tmp._client_addr);
	memset(&tmp._client_addr, 0, len);
	char recv_buf[MAX_BUF_SIZE] = "";
	//recvfrom
	int n_read = recvfrom(_fd, recv_buf, 1024, 0, (struct sockaddr*)&tmp._client_addr, &len);
	recv_buf[n_read] = '\0';
	cout << "Receive from client:" << recv_buf << endl;
	LogInfo("Receive from client(query word):%s", recv_buf);
	//set Task
	tmp.recv_word(recv_buf);
	tmp._server_sockfd = _fd;
	tp.add_task(tmp); //把任务放到任务队列里去
}

//发送消息，其他类没有用到这个函数，可以不要
void UDPServer::send(Task &task)
{
	size_t len = sizeof(task._client_addr);
	string send_recv = task.get_word();
	int n_send = sendto(_fd, send_recv.c_str(), send_recv.size(), 0, (struct sockaddr*) &task._client_addr, len);
	if(n_send < 0)
	{
		throw runtime_error("Server send error!");
	}
}

