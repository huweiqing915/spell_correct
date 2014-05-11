/*************************************************************************
	> File Name: Index.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月11日 星期日 12时42分57秒
 ************************************************************************/

#include "Index.h"
#include <iostream>

using namespace std;

ifstream& open_file(ifstream &is, const string &filename)
{
	is.close();
	is.clear();
	is.open(filename.c_str());
	return is;
}

void Index::divided_single_word(const string &str,vector<string> &vec)
{
	vec.clear();
	char *tmp = new char[3];
	string::size_type ix = 0;
	while (ix != str.length())
	{
		if(str[ix] & 0x80)	//gbk，占两个字节
		{
			// if(ix + 1 == str.size())	//检查越界的情况
			// {
			// 	throw runtime_error("invalid gbk string");
			// }
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
	divided_single_word(word, vec);    //把word分开，并存入index中
	for(auto &x : vec)
	{
		(_index[x])[word] = freq;
	}
}

void Index::read_dict()
{
	ifstream infile;
	if(!open_file(infile, DICT_PATH))
	{
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
	ofstream outfile(DEBUG_INDEX_PATH);
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




