/*************************************************************************
	> File Name: Task.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时38分24秒
 ************************************************************************/

#include "Task.h"

#include <iostream>
#include <unordered_map>

using namespace std;

void Task::excute_task(unordered_map<string, string> &_hash, _temp_index &index)
{
	string jsonstr;
	unordered_map<string, string>::iterator iter = _hash.find(_word);
	if(iter != _hash.end())	//如果在cache里面就直接发，不用query_word
	{
	#ifndef NDEBUG
		cout << "Send from cache..." << endl;
	#endif
		jsonstr = in_cache_json_string(iter->second);
	}
	else
	{
	#ifndef NDEBUG
		cout << "Send not in cache..." << endl;
	#endif
		_sc.query_word(_word, index);
		_hash.insert(make_pair(_word, _sc.get_word_queue_top(_word)));  //不在cache里面就增加新的
		jsonstr = json_string();
	}
	sendto(_server_sockfd, jsonstr.c_str(), jsonstr.size(), 0, (struct sockaddr*)&_client_addr, sizeof(_client_addr));
}

//在cache中查找到的发送的json格式
string Task::in_cache_json_string(const string &str)
{
	Json::Value root ;
	Json::Value arr ;
	Json::Value elem ;

	elem["title"] = "In cache:" ;
	elem["summary"] = str;
	arr.append(elem);
	root["files"]=arr ;

	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);
}

//在词典（或index）中查找到的发送的json格式
string Task::json_string()
{
	Json::Value root ;
	Json::Value arr ;
//	set<TextQuery::_line_no> line_set = _tq.get_line_num(_word);
//	set<TextQuery::_line_no>::iterator iter = line_set.begin();
//	while(iter != line_set.end())
	for(int i = 0; i != CANDIDATE_WORD_NUM; ++i)	
	{
		if(_sc.is_queue_empty())
			break;
		Json::Value elem ;
		char line[64] = "";
		sprintf(line , "Candidate word[%d]:", i + 1);
		elem["title"] = line ;
		elem["summary"] = _sc.get_correct_word();
		arr.append(elem);
	}
	root["files"]=arr ;
	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);
}
