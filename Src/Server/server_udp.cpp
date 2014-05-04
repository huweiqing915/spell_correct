#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include "json/json.h"
#include <sys/time.h>
using namespace std;

string json_string( );

int main(int argc, char const *argv[])
{
	int server_fd;
	struct sockaddr_in server_addr, client_addr;
	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd == -1)
	{
		perror("Server socket");
		exit(-1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 ==  bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		perror("Server bind");
		close(server_fd);
		exit(-1);
	}
	while(1)
	{
		char *recv_buf;
		recv_buf = (char *)malloc(sizeof(char)*512);
		bzero(recv_buf, 512);
		memset(&client_addr, 0, sizeof(client_addr));
		socklen_t len = sizeof(client_addr);
		int recv_size = recvfrom(server_fd, recv_buf, 512, 0, (struct sockaddr*)&client_addr, &len);
		if(recv_size == -1)
		{
			perror("Server recieve");
			break;
		}
		recv_buf[recv_size] = '\0';
		printf("Receive from client:%s\n", recv_buf);
		
	//	char send_buf[]="hello client!";
		string jsonstr = json_string();
		int send_size = sendto(server_fd, jsonstr.c_str(),jsonstr.size(), 0, (struct sockaddr*)&client_addr, len);
		if(send_size == -1)
		{
			perror("Server send to client");
			break;
		}
	}
	close(server_fd);
	return 0;
}

string json_string( )
{
	srand(time(NULL));
	int size ;
	while(1)
	{
		size = rand() % 100 ;
		if(size > 0)
		{
			break ;
		}
	}
	Json::Value root ;
	Json::Value arr ;
	while(size)
	{
		Json::Value elem ;
		char title[128] = "";
		char summary[128]="";
		sprintf(title , "tile_%d", size);
		sprintf(summary, "summary_%d", size);
		elem["title"] = title ;
		elem["summary"] = summary ;
		arr.append(elem);
		size -- ;
	}
	root["files"]=arr ;
	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);

}
