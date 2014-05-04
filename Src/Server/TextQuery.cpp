/*************************************************************************
	> File Name: TextQuery.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月29日 星期二 23时05分07秒
 ************************************************************************/

#include "TextQuery.h"

using namespace std;

static ifstream& open_file(ifstream &is, const string filename)
{
	is.close();
	is.clear();
	is.open(filename.c_str());
	return is;
}

void TextQuery::read_file(const string &filename)
{
	ifstream infile;
	if(!open_file(infile, filename))
	{
		throw runtime_error("open file error!");
	}

	string line;
	while(getline(infile, line))
	{
		_lines.push_back(line);
	}
	infile.close();
	infile.clear();
}

//Save content to the map
void TextQuery::build_map()
{
	istringstream sstrm;
	for(_line_no ix = 0; ix != _lines.size(); ++ix)
	{
		string word;
		//use sstream's function str();
		sstrm.str(_lines[ix]);
		while(sstrm >> word)
		{
			for(int iy = 0; iy != word.length(); iy++)
			{
				if(ispunct(word[iy]))
				{
					word[iy] = ' ';
				}
				else if(isupper(word[iy]))
				{
					word[iy] = word[iy] + 32;
				}
				else
				{
					word[iy] = word[iy];
				}
			}
			_word_map[word].insert(ix);
		}
		sstrm.clear();
	}
}

static void print_map(const map<TextQuery::_word, set<TextQuery::_line_no> >::value_type &m)
{
	cout << m.first << endl;
}

//For test
void TextQuery::debug()
{
	for_each(_word_map.begin(), _word_map.end(), print_map);
}

//This function is to return the words' line numbers;
set<TextQuery::_line_no> TextQuery::get_line_num(const string &word)	
{
	//function find()
	_map_iterator iter = _word_map.find(word);
	if(iter != _word_map.end())
		return iter->second;
	else
		return set<_line_no>();   //return empty;
}

//return the content in vector
TextQuery::_single_line TextQuery::get_line(_line_no pos)
{
	if(pos < 0 || pos > _lines.size())
		throw out_of_range("out of query range! ");
	return _lines[pos];
}

void TextQuery::query_word(const string &word)
{
	set<_line_no> line_set = get_line_num(word);
	cout << "(" << word << ")" << " occurs:" << line_set.size() << " times!" << endl;
	set<_line_no>::iterator iter = line_set.begin();
	while(iter != line_set.end())
	{
		cout << "line " << *iter + 1 << ": " << get_line(*iter) << endl;
		++iter;
	}
}
