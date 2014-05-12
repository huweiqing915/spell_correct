/*************************************************************************
	> File Name: Config.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月08日 星期四 15时08分58秒
 ************************************************************************/
/*
 * 配置文件类，用于读取各个文件的路径。
 * 定义为单例模式，调用只需定义一个Config的指针，节约内存
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <fstream>
#include <map>

#include "MutexLock.h"
#include "Log.h"

#define CONFIG_DAT_PATH "../Conf/config.dat" //配置文件存放的位置
#define MATCH_CHARACTER '='  //配置文件的格式，如server_port = 6688

class Config {
public:
	static Config* get_instance();  //通过这个static函数获得对象的指针
	bool get_file_name(const std::string &key, std::string &value) const;

private:
	Config();	//将构造函数声明为私有，无法在外部构造对象
	virtual ~Config();
	static Config *_p_config; //上面的static函数只能调用static变量
	static MutexLock _lock;

	bool load_config_file();
	std::map<std::string, std::string> _config_map;
};

#endif
