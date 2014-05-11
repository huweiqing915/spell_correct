/*************************************************************************
	> File Name: Cache.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月09日 星期五 19时25分35秒
 ************************************************************************/

#include "Cache.h"
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

/*bool Cache::add_hash(_hash_map &hash, const string &key, const string &value)
{
	pair<_hashmap_iter, bool> ret = hash.insert(make_pair(key, value));
	if(ret.second)
		return true;
	else
		return false;
}

void Cache::add_thread_hash(_hash_map &src_hash, _hash_map &des_hash)	//把src加到des中
{
	for(auto & x: src_hash)
	{
		add_hash(des_hash, x.first, x.second);
	}
}*/

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

void Cache::get_disk_cache()
{
	ifstream infile;
	if(!open_file(infile, CACHE_FILE_PATH))
	{
		LogError("open %s error!", CACHE_FILE_PATH);
	}
	string key, value;
	while(infile >> key >> value)
	{
		_hash[key] = value;
	}
	infile.close();
	infile.clear();
}

void Cache::write_to_disk()
{
	ofstream outfile;
	if(!open_file(outfile, CACHE_FILE_PATH))
	{
		LogError("open %s error!", CACHE_FILE_PATH);
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
