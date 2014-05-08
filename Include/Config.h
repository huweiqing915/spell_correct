/*************************************************************************
	> File Name: Config.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 15时08分58秒
 ************************************************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include "Log.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>

class Config {
public:
	Config(const char * const config_path);
	virtual ~Config();

	bool get_file_path(const std::string &key, std::string &value) const;
private:
	bool load_file(const char * const file_path);
	std::map<std::string, std::string> _config_map;
};

#endif
