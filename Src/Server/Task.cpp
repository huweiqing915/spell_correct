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
}


void Task::excute_task()
{
	_sc.correct_word(_word);
	string jsonstr = json_string();
	sendto(_server_sockfd, jsonstr.c_str(), jsonstr.size(), 0, (struct sockaddr*)&_client_addr, sizeof(_client_addr));
}

string Task::json_string( )
{
	Json::Value root ;
	Json::Value arr ;
//	set<TextQuery::_line_no> line_set = _tq.get_line_num(_word);
//	set<TextQuery::_line_no>::iterator iter = line_set.begin();
//	while(iter != line_set.end())
	for(int i = 0; i != 3; ++i)
	{
		if(_sc.is_queue_empty())
			break;
		Json::Value elem ;
		char line[64] = "";
		sprintf(line , "Candidate word(%d):", i + 1);
		elem["title"] = line ;
		elem["summary"] = _sc.get_correct_word();
		arr.append(elem);
	}
	root["files"]=arr ;
	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);
}
