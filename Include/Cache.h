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

#define CACHE_FILE_PATH "/var/www/spell_correct/Data/cache.txt"

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

	// bool add_hash(_hash_map &hash, const std::string &key, const std::string &value);
	// void add_thread_hash(_hash_map &hash_a, _hash_map &hash_b);
	void add_thread_hash(_hash_map &src_hash);
	
	void get_disk_cache();
	void write_to_disk();

	_hash_map& get_hash_map();

private:
	std::unordered_map<std::string, std::string> _hash;
};

#endif
