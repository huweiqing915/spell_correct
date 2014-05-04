/*************************************************************************
	> File Name: Task.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时38分24秒
 ************************************************************************/

#include "Task.h"
#include <iostream>

using namespace std;

Task::Task()
{
	_tq.read_file("/var/www/spell_correct/Data/test.txt");
	_tq.build_map();
}

void Task::excute_task()
{
	string jsonstr = json_string();
	sendto(_server_sockfd, jsonstr.c_str(), jsonstr.size(), 0, (struct sockaddr*)&_client_addr, sizeof(_client_addr));
//	close(_server_sockfd);
}

string Task::json_string( )
{
	Json::Value root ;
	Json::Value arr ;
	set<TextQuery::_line_no> line_set = _tq.get_line_num(_word);
	set<TextQuery::_line_no>::iterator iter = line_set.begin();
	while(iter != line_set.end())
	{
		Json::Value elem ;
		char line[64] = "";
		sprintf(line , "line_%d:", *iter + 1);
		elem["title"] = line ;
		elem["summary"] = _tq.get_line(*iter).c_str() ;
		arr.append(elem);
		++ iter;
	}
	root["files"]=arr ;
	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);
}
