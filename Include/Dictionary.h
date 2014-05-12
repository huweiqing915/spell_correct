/*************************************************************************
	> File Name: Dictionary.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月07日 星期三 20时17分37秒
 ************************************************************************/
/*
 * 根据材料生成中文词典
 * 文件路径要在cpp中更改，路径没有提供在配置文件中
 */
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "MixSegment.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	std::ifstream& open_file(std::ifstream &is, const char *filename);
	std::ofstream& open_file(std::ofstream &os, const char *filename);

	void read_file(const std::string &filename);
	void build_word_map(std::string &);	//用map暂存

	void traversal_dir(const std::string &dirname); //遍历文件

	void write_dictionary(const std::string &dirname); //写入磁盘
private:
	const char * const dict_path;
	const char * const model_path;
	const char * const exclude_path;

	void build_exclude_set();

	std::map<std::string, int> _word_map;
	std::set<std::string> _exclude;
	CppJieba::MixSegment segment;
};

#endif
