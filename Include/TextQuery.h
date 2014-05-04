/*************************************************************************
	> File Name: TextQuery.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月29日 星期二 22时48分50秒
 ************************************************************************/

#ifndef TEXT_QUERY_H_
#define TEXT_QUERY_H_

#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class TextQuery {
public:
	typedef std::string _word;
	typedef std::string _single_line;
	typedef std::vector<std::string>::size_type _line_no;
	typedef std::map<_word, std::set<_line_no> >::iterator _map_iterator;

	void read_file(const std::string&);
	void build_map();

	std::set<_line_no> get_line_num(const std::string&);
	std::string get_line(_line_no pos);
	void query_word(const std::string&);

	void debug();
private:
	std::vector<std::string> _lines;
	std::map<_word, std::set<_line_no> > _word_map;
};

#endif
