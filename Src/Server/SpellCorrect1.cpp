/*************************************************************************
	> File Name: SpellCorrect.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 20时27分10秒
 ************************************************************************/


#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include <fstream>

#include "SpellCorrect.h"
#include "EncodingConverter.h"
#include "MixSegment.hpp"

using namespace std;

inline int min(int a, int b, int c)
{
	int t = a < b ? a : b;
	return t < c ? t : c;
}

inline int count_size(const string &str)
{
	int size = 0;
	string::size_type ix = 0;
	while(ix != str.length())
	{
		if(str[ix] & 0x80)	//第一位为1，说明是gbk码
		{
			ix = ix + 2;	//两个字节为一个汉字
			size ++;
		}
		else	//第一位为0,说明是ascii码
		{
			ix ++;
			size ++;
		}
	}
	return size;
}

inline uint16_t * change_to_short(const string &str, int len)
{
	uint16_t *arr = new uint16_t[len];	//申请一段字符长度的空间
	int count = 0;
	string::size_type ix = 0;
	while(ix != str.length() && count != len)
	{
		if(str[ix] & 0x80)	//gbk码
		{
			arr[count ++] = (str[ix] << 8) + str[ix + 1];
			ix = ix + 2;
		}
		else	//ascii码
		{
			arr[count ++] = str[ix];
			ix ++;
		}
	}
	return arr;
}

SpellCorrect::SpellCorrect():dict_path("DATA_PATH/jieba.dict.gbk"),model_path("DATA_PATH/hmm_model.gbk"),
	segment(dict_path, model_path)
{
	get_dictionary();
}

SpellCorrect::~SpellCorrect()
{

}

void SpellCorrect::get_dictionary()
{
	string dict1 = "DATA_PATH/jieba.dict.gbk";  //Chinese
	_dictionary_paths.push_back(dict1);
	string dict2 = "DATA_PATH/dictionary.txt";	//English
	_dictionary_paths.push_back(dict2);
}


//Compute the Chinese & English edit_distance 
int SpellCorrect::edit_distance(const string &a, const string &b)
{
	int len1 = count_size(a);
	int len2 = count_size(b);
	uint16_t *short_a = change_to_short(a, len1);
	uint16_t *short_b = change_to_short(b, len2);

	int **mem = new int *[len1 + 1];
	for(int k = 0; k <= len1; ++k)
	{
		mem[k] = new int[len2 + 1];
	}
	//initilize
	for(int i = 0; i <= len1; ++i)
	{
		mem[i][0] = i;
	}
	for(int j = 0; j <= len2; ++j)
	{
		mem[0][j] = j;
	}

	//DP
	for(int i = 1; i <= len1; ++i)
	{
		for(int j = 1; j <= len2; ++j)
		{
			int cost = (short_a[i-1] == short_b[j-1] ? 0 : 1);
			int deletion = mem[i-1][j] + 1;
			int insertion = mem[i][j-1] + 1;
			int substitution = mem[i-1][j-1] + cost;
			mem[i][j] = min(deletion, insertion, substitution);
		}
	}
	int ret = mem[len1][len2];
	for(int k = 0; k <= len1; ++k)
	{
		delete [] mem[k];
	}
	//delete [] short_a;
	//delete [] short_b;
	delete [] mem;
	return ret;
}

static ifstream& open_file(ifstream &is, const string &filename)
{
	is.close();
	is.clear();
	is.open(filename.c_str());
	return is;
}


bool SpellCorrect::is_ascii(const string &str)
{
	string::size_type ix = 0;
	if(str[ix] & 0x80)	//first position is 1 --this is a GBK
		return 	false;
	else
		return true;
}

void clear_queue(priority_queue<CorrectWord, vector<CorrectWord>, compare> &prior_queue)
{
	while(!prior_queue.empty())
	prior_queue.pop();
}

//Find the correct word in the dictionary
void SpellCorrect::correct_word(const string &word)
{
	
	EncodingConverter trans;
	vector<string> cut_words;
	cut_words.clear();

	string gbk_word = trans.utf8_to_gbk(word);
	segment.cut(gbk_word, cut_words);  //use the cut tool to cut word

	ifstream infile;

	vector<string>::iterator iter = cut_words.begin();
	while(iter != cut_words.end())
	{
		string directory_word;
		string m;
		int frequency;
		
		if(is_ascii(*iter))	//this is an English word, open english dictionary
		{
			if(!open_file(infile, _dictionary_paths[1]))
			{
				LogFatal("open file %s error!", _dictionary_paths[1].c_str());
				throw runtime_error("open directory.txt error!");
			}
			while(infile >> directory_word >> frequency >> m)
			{
				int distance = edit_distance(*iter, directory_word);
			
			#ifdef DEBUG
				cout << directory_word << " " << distance << endl;
			#endif	
	
				if(distance < DISTANCE_DISTRICT)
				{
//					outfile << directory_word << " " << distance << endl; 
					_correct_word_queue.push(CorrectWord(distance, directory_word, frequency));
				}
			}
			_correct_word_vector.push_back(_correct_word_queue);
			clear_queue(_correct_word_queue);
		}

		else 	//Chinese, open Chinese dictionary
		{
			if(!open_file(infile, _dictionary_paths[0]))
			{
				LogFatal("open file %s error!", _dictionary_paths[0].c_str());
				throw runtime_error("open directory.txt error!");
			}
			while(infile >> directory_word >> frequency >> m)
			{
				int distance = edit_distance(*iter, directory_word);
				if(distance < DISTANCE_DISTRICT)
				{
//					outfile << directory_word << " " << distance << endl; 
					_correct_word_queue.push(CorrectWord(distance, directory_word, frequency));
				}
			}
			_correct_word_vector.push_back(_correct_word_queue);
			clear_queue(_correct_word_queue);

		}
		infile.close();
		infile.clear();
	}

#ifdef DEBUG
	cout << endl << "result is :" << endl;
	for(int i = 0; i != 3; ++i)
	{
		if(_correct_word_queue.empty())
			break;
		cout << _correct_word_queue.top()._word << endl;
		_correct_word_queue.pop();
	}
#endif

	infile.close();
	infile.clear();
}

string SpellCorrect::get_correct_word()
{ 
	string ret;
	while(vector<priority_queue<CorrectWord, vector<CorrectWord>, compare> >::iterator iter = _correct_word_vector.begin();
				iter != _correct_word_vector.end(); ++iter)
	{
		ret += iter->top()._word;
	}
	EncodingConverter trans;
	ret = trans.gbk_to_utf8(ret);

#ifdef DEBUG
	cout << "return string:" << ret << endl;
#endif
	return ret;
}

bool SpellCorrect::is_queue_empty()
{
	return _correct_word_queue.empty();
}
