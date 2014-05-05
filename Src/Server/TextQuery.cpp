/*************************************************************************
	> File Name: TextQuery.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年04月29日 星期二 23时05分07秒
 ************************************************************************/

#include "TextQuery.h"
#include <iostream>

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
		int ix = 0;
		while(ix != line.length())
		{
			line[ix] = tolower(line[ix]);
			if(ispunct(line[ix]))
			{
				line[ix] = ' ';
			}
			ix ++;
		}
	//	cout << line << endl;
		_lines.push_back(line);
	}
	infile.close();
	infile.clear();
}

//Save content to the map

void TextQuery::build_map()
{
	istringstream sstrm;
	for(TextQuery::_line_no ix = 0; ix != _lines.size(); ++ix)
	{
		string word;
		//use sstream's function str();
		sstrm.str(_lines[ix]);
		while(sstrm >> word)
		{
			_word_map[word]++;
		}
		sstrm.clear();
	}
}

void TextQuery::write_file()
{
	ofstream os("/var/www/spell_correct/Data/directory.txt");
	if(!os)
	{
		cerr << "error:unable to open input file" << endl;
		return;
	}
	map<TextQuery::_word, int>::iterator iter= _word_map.begin();
	while(iter != _word_map.end())
	{
		os << iter->first << "\t" << iter->second << endl;
		iter ++;
	}
	os.clear();
	os.close();
}

/*
static void print_map(const map<TextQuery::_word, int>::value_type &m)
{
	ofstream os("/var/www/spell_correct/Data/process.txt");
	if(!os)
	{
		cerr << "error:unable to open input file" << endl;
		return;
	}
	os << m.first << "\t" << m.second << endl;
	cout << m.first << "\t" << m.second << endl;
}

//For test
void TextQuery::debug()
{
	for_each(_word_map.begin(), _word_map.end(), print_map);
}*/

/*
static void print_map(const map<TextQuery::_word, set<TextQuery::_line_no> >::value_type &m)
{
	cout << m.first << endl;
}
*/

/*
 *This is for search text
 *
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
*/
