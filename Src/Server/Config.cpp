/*************************************************************************
	> File Name: Config.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 15时15分40秒
 ************************************************************************/

#include "Config.h"

using namespace std;

Config::Config(const char * const config_path)
{
	load_file(config_path);
}

Config::~Config()
{

}

static inline bool split(string &src, string &key, string &value,  char pattern)
{
	if(src.empty())
	{
		return false;
	}
	string::size_type pos = 0;
	while((pos = src.find(' ', pos)) != string::npos)
	{
		src.erase(pos, 1);
	}
	pos = src.find_first_of(pattern, 0);
	key = src.substr(0, pos);
	value = src.substr(pos+1, src.size());
	return true;
}


bool Config::load_file(const char * const file_path)
{
	ifstream infile(file_path);
	if(!infile)
	{
		LogFatal("open file[%s] failed!", file_path);
		return false;
	}
	string line;
	vector<string> svec;
	size_t lineno = 0;
	while(getline(infile, line))
	{
		lineno ++;
		string key, value;
		if(!split(line, key, value, '='))
        {
            LogFatal("line[%d:%s] is illegal.", lineno, line.c_str());
            return false;
        }

        pair<map<string, string>::iterator, bool> ret = _config_map.insert(make_pair(key, value));
        if(!ret.second)
        {
        	LogFatal("key[%s] already exists.", key.c_str());
            return false;
        }
        /*
        if(_config_map.find(key) !=  _config_map.end())
        {
            LogFatal("key[%s] already exists.", key.c_str());
            return false;
        }
        _config_map[key] = value;
        */
	}
	infile.close();
    return true;
}


bool Config::get_file_path(const string &key, string &value) const
{
	map<string, string>::const_iterator iter = _config_map.find(key);
	if(iter != _config_map.end())
	{
		value = iter->second;
		return true;
	}
	return false;
}

