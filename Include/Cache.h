/*************************************************************************
	> File Name: Cache.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月09日 星期五 19时24分16秒
 ************************************************************************/

#ifndef CACHE_H_
#define CACHE_H_

#include <string>
#include <unordered_map>
#include <unistd.h>

#include "Log.h"

/*struct CacheWord
{
	std::string _cache_word;
	int _cache_frequency;
};*/

class Cache {
public:
	typedef std::unordered_map<std::string, std::string> _hash_map;
	typedef std::unordered_map<std::string, std::string>::iterator _hashmap_iter;

	bool find_cache_word(const std::string&, std::string&);
	void add_thread_hash(_hash_map &src_hash);	//收集线程的cache的方法
	
	void get_disk_cache();
	void write_to_disk();

	_hash_map& get_hash_map();

private:
	//cache的数据结构，第一个为用户输入的词，第二个为cache中的词
	std::unordered_map<std::string, std::string> _hash;
};

#endif
