/*************************************************************************
	> File Name: Dictionary.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月07日 星期三 20时17分37秒
 ************************************************************************/

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
	void build_word_map(std::string &);

	void traversal_dir(const std::string &dirname);

	void write_dictionary(const std::string &dirname);
private:
	const char * const dict_path;
	const char * const model_path;
	const char * const exclude_path;

	void build_exclude_set();

	std::map<std::string, int> _word_map;
	std::set<std::string> _exclude;
	CppJieba::MixSegment segment;
};

//const char * const dict_path = "dict/jieba.dict.gbk";

#endif
