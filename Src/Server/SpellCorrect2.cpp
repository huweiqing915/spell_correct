/*************************************************************************
	> File Name: SpellCorrect.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 20时27分10秒
 ************************************************************************/
/*
 * 这个是只提供英文纠错的版本
 */


#include "SpellCorrect.h"
#include <iostream>

using namespace std;

inline int min(int a, int b, int c)
{
	int t = a < b ? a : b;
	return t < c ? t : c;
}

int SpellCorrect::edit_distance(const string &a, const string &b)
{
	int len1 = a.size();
	int len2 = b.size();
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
			int cost = (a[i-1] == b[j-1] ? 0 : 1);
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

void SpellCorrect::correct_word(const string &word)
{
	ifstream infile;
	string file_name = "/var/www/spell_correct/Data/directory.txt";
	if(!open_file(infile, file_name))
	{
		throw runtime_error("open directory.txt error!");
	}
//	ofstream outfile;
//	outfile.open("/var/www/spell_correct/Data/output.txt");

	string directory_word;
	int frequency;

	while(infile >> directory_word >> frequency)
	{
		int distance = edit_distance(word, directory_word);
	#ifdef DEBUG
		cout << directory_word << " " << distance << endl;
	#endif	
		if(distance < 5)
		{
//			outfile << directory_word << " " << distance << endl; 
			_correct_word_queue.push(CorrectWord(distance, directory_word, frequency));
		}
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
//	outfile.close();
//	outfile.clear();
	infile.close();
	infile.clear();
}

string SpellCorrect::get_correct_word()
{ 
	string ret = _correct_word_queue.top()._word;
//	cout << "return string:" << ret << endl;
	_correct_word_queue.pop();
	return ret;
}

bool SpellCorrect::is_queue_empty()
{
	return _correct_word_queue.empty();
}
