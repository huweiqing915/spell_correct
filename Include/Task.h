/*************************************************************************
	> File Name: Task.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月28日 星期一 23时32分33秒
 ************************************************************************/

#ifndef TASK_H_
#define TASK_H_

#include "SpellCorrect.h"
#include "json/json.h"

#include <string>
#include <unordered_map>
#include <netinet/in.h>

#define CANDIDATE_WORD_NUM 5	//发送给客户端候选词的数量

class Task {
public:
	typedef std::unordered_map<std::string, std::map<std::string, int> > _temp_index;
	struct sockaddr_in _client_addr;
	int _server_sockfd;

	void excute_task(std::unordered_map<std::string, std::string> &, _temp_index &);
//	void excute_task();

	void recv_word(const char *str)
	{
		_word = std::string(str);
	}

	std::string& get_word()
	{
		return _word;
	}

private:
	std::string _word;
	SpellCorrect _sc;
	std::string json_string();
	std::string in_cache_json_string(const std::string &);
};

#endif
