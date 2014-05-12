/*************************************************************************
	> File Name: Index.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月11日 星期日 12时42分57秒
 ************************************************************************/

#include "Index.h"
#include "Config.h"
#include "Log.h"
#include <iostream>

using namespace std;

ifstream& open_file(ifstream &is, const string &filename)
{
	is.close();
	is.clear();
	is.open(filename.c_str());
	return is;
}

//把汉字或者ascii分为单个的字
void Index::divided_single_word(const string &str,vector<string> &vec)
{
	vec.clear();
	char *tmp = new char[3];
	string::size_type ix = 0;
	while (ix != str.length())
	{
		if(str[ix] & 0x80)	//gbk，占两个字节
		{
			if(ix + 1 == str.size())	//检查越界的情况
			{
				LogFatal("invalid gbk string");
			 	throw runtime_error("invalid gbk string");
			}
			tmp[0] = str[ix];
			tmp[1] = str[ix + 1];
			tmp[2] = '\0';
			ix = ix + 2;
		}
		else	//ascii，占一个字节
		{
			tmp[0] = str[ix];
			tmp[1] = '\0';
			++ix;
		}
		vec.push_back(string(tmp));
	}
	delete tmp;
}

//After read_dict, can build a index;
void Index::build_index(const string &word, int freq)
{
	vector<string> vec;
	divided_single_word(word, vec);    //把word分开
	for(auto &x : vec)	//std=c++11	,存入index中
	{
		(_index[x])[word] = freq;
	}
}

void Index::read_dictionary()
{
	ifstream infile;
	string dict_path;
	Config *p = Config::get_instance();
	p->get_file_name("dict_path", dict_path);
	LogInfo("open %s", dict_path.c_str());
	if(!open_file(infile, dict_path))
	{
		LogError("open dictionary failed!");
		throw runtime_error("open dictionary failed!");
	}
	
	string word;
	string m;
	int frequency;
	while(infile >> word >> frequency >> m)
	{
		build_index(word, frequency);
	}
	infile.close();
	infile.clear();
}

void Index::debug()
{
	ofstream outfile;
	Config *p = Config::get_instance();
	string debug_index_path;
	p->get_file_name("debug_index_path", debug_index_path);
	outfile.open(debug_index_path);
	for(auto &x : _index)
	{
		map<string, int> temp_map = x.second;
		outfile << x.first << "\t";
		for(auto & y : temp_map)
		{
			outfile << y.first << " " << y.second << "\t";
		}
		outfile << endl;
	}
	outfile.close();
	outfile.clear();
}

Index::_index_map& Index::get_index()
{
	return _index;
}



