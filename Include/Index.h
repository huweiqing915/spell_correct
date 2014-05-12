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

class Index {
public:
	typedef std::unordered_map<std::string, std::map<std::string, int> > _index_map;

	void divided_single_word(const std::string &, std::vector<std::string> &); //把汉字或者ascii分为单个的字
	void read_dictionary();
	void debug();

	_index_map& get_index();
private:
	std::unordered_map<std::string, std::map<std::string, int> > _index;
	void build_index(const std::string &, int);
};

#endif
