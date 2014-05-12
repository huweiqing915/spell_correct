/*************************************************************************
	> File Name: Cache.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月09日 星期五 19时25分35秒
 ************************************************************************/

#include "Cache.h"
#include "Config.h"
#include <iostream>
using namespace std;

bool Cache::find_cache_word(const string &key_word, string &value)
{
		_hashmap_iter got = _hash.find(key_word);
		if(got == _hash.end())  //hash表中没找到单词，返回false
			return false;
		else	//hash表中存在查找的单词，返回true
			value = got->second;
		return true;
}

//提供给CacheManageThread的收集cache的方法
void Cache::add_thread_hash(_hash_map &src_hash)
{
	for(auto & x: src_hash)
	{
		_hash.insert(make_pair(x.first, x.second));
	}
}

static inline ifstream& open_file(ifstream &in, const string &filename)
{
	in.close();
	in.clear();
	in.open(filename.c_str());
	return in;
}

static inline ofstream& open_file(ofstream &os, const string &filename)
{
	os.close();
	os.clear();
	os.open(filename.c_str());
	return os;
}

//线程池开启的时候每个线程都要读取磁盘上的cache文件
void Cache::get_disk_cache()
{
	ifstream infile;
	string cache_filename;
	Config *p_config = Config::get_instance();
	p_config->get_file_name("cache_path", cache_filename);
	if(!open_file(infile, cache_filename))
	{
		LogError("open %s error!", cache_filename.c_str());
	}
	string key, value;
	while(infile >> key >> value)
	{
		_hash[key] = value;
	}
	infile.close();
	infile.clear();
}

//将收集到的各个线程的cache写到磁盘去的方法
void Cache::write_to_disk()
{
	ofstream outfile;
	string cache_filename;
	Config *p_config = Config::get_instance();
	p_config->get_file_name("cache_path", cache_filename);
	if(!open_file(outfile, cache_filename))
	{
		LogError("write %s error!", cache_filename.c_str());
	}

	for(auto & x : _hash)
	{
		outfile << x.first << "\t" << x.second << endl;
	}
	outfile.close();
	outfile.clear();
}

Cache::_hash_map& Cache::get_hash_map()
{
	return _hash;
}
