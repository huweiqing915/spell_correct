/*************************************************************************
	> File Name: EditDistance.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 16时53分10秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <fstream>

using namespace std;

inline int min(int a, int b, int c)
{
	int t = a < b ? a : b;
	return t < c ? t : c;
}

int edit_distance(const string &a, const string &b)
{
	int len1 = a.size();
	int len2 = b.size();
	int **mem = new int *[len1 + 1];
	for(int k = 0; k <= len1; ++k)
	{
		mem[k] = new int[len2 + 1];
	}

	for(int i = 0; i <= len1; ++i)
	{
		mem[i][0] = i;
	}
	for(int j = 0; j <= len2; ++j)
	{
		mem[0][j] = j;
	}

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
/*
	for(int i = 0; i <= len1; ++i)
	{
		for(int j = 0; j <= len2; ++j )
		{
			cout << mem[i][j] << "  " ;
		}
		cout << endl;
	}
	cout << endl;
	cout << mem[len1][len2] << endl;
*/
	int ret = mem[len1][len2];
	for(int k = 0; k <= len1; ++k)
	{
		delete [] mem[k];
	}
	delete[] mem;
	return ret;
}

ifstream& open_file(ifstream &is, const string &file)
{
	is.close();
	is.clear();
	is.open(file.c_str());
	return is;
}

void query_word(const string &word)
{
	ifstream infile;
	string filename = "/var/www/spell_correct/Data/directory.txt";
	if(!open_file(infile,filename))
	{
		throw runtime_error("open file error");
	}
	string directory_word;
	string correct_word;
	
	int min_distance = 100;
	int max_frequency = 0;
	int frequency;

	while(infile >> directory_word >> frequency)
	{
//		cout << directory_word <<"\t" << frequency << endl;
		int distance = edit_distance(word, directory_word);
//		cout << distance << endl;
		if(distance < min_distance)
		{
			min_distance = distance;
			max_frequency = frequency;
			correct_word = directory_word;
			cout << min_distance << " " << max_frequency << " " << correct_word << endl;
		}
		else if(distance == min_distance)
		{
			if(frequency > max_frequency)
			{
				max_frequency = frequency;
				correct_word = directory_word;
				cout << min_distance << " " << max_frequency << " " << correct_word << endl;
			}
		}
	}
	cout << correct_word << endl;
}

int main()
{
	string s1;
	while(cin >> s1)
	{
		query_word(s1);
	}
	return 0;
}
