/*************************************************************************
	> File Name: Index.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月11日 星期日 12时42分47秒
 ************************************************************************/

#ifndef INDEX_H_
#define INDEX_H_

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
#include <string.h>

#define DICT_PATH  "/var/www/spell_correct/Data/jieba.dict.gbk"
#define DEBUG_INDEX_PATH "/var/www/spell_correct/Data/index.txt"

class Index {
public:
	void divided_single_word(const std::string &, std::vector<std::string> &);
	void build_index(const std::string &word, int freq);
	void read_dict();
	void debug();
private:
	std::unordered_map<std::string, std::map<std::string, int> > _index;
//	SpellCorrect _sc;
};

#endif
