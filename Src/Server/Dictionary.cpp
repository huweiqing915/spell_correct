/*************************************************************************
	> File Name: Dictionary.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月07日 星期三 20时16分50秒
 ************************************************************************/

#include "Dictionary.h"
#include <stdexcept>


using namespace CppJieba;

Dictionary::Dictionary():dict_path("dict/jieba.dict.gbk"),model_path("dict/hmm_model.gbk"),
      			exclude_path("remove.txt"),segment(dict_path, model_path)
{
	build_exclude_set();
}

Dictionary::~Dictionary()
{
	
}

ifstream& Dictionary::open_file(ifstream &is, const char *filename)
{
	is.close();
	is.clear();
	is.open(filename);
	return is;
}

ofstream& Dictionary::open_file(ofstream &os, const char *filename)
{
	os.close();
	os.clear();
	os.open(filename);
	return os;
}

void Dictionary::traversal_dir(const string &dirname)
{
	DIR *dir_ptr;
	struct dirent *entry;
	struct stat stat_buf;
	if((dir_ptr = opendir(dirname.c_str())) == NULL)
	{
		throw std::runtime_error("open directory error!");		
	}	
	chdir(dirname.c_str());
	while((entry = readdir(dir_ptr)) != NULL)
	{
		stat(entry->d_name, &stat_buf);
		if(S_ISDIR(stat_buf.st_mode))
		{
		#ifndef NDEBUG
			cout << "directory:" << entry->d_name << endl;
		#endif
			//found a directory, but ignore . and ..
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
			traversal_dir(entry->d_name);
		}
		else
		#ifndef NDEBUG
			cout << "file:" << entry->d_name << endl;
		#endif 
			read_file(entry->d_name);
	}
	chdir("..");
	closedir(dir_ptr);
}


void Dictionary::read_file(const string &filename)
{
	ifstream infile;
	if(!open_file(infile, filename.c_str()))
	{
		throw runtime_error("open file error!");
	}

	string line;
	while(getline(infile, line))
	{
		string::size_type ix = 0;
		while(ix != line.length())
		{
			if(isascii(line[ix]))
			{
				line[ix] = ' ';
			}
			++ix;
		}
		build_word_map(line);
	}
	infile.close();
	infile.clear();
}


//build a chinese punctuation
void Dictionary::build_exclude_set()
{
	ifstream infile;
	if(!open_file(infile, exclude_path))
	{
		throw std::runtime_error("open excluded file error");
	}
	string remove_word;
	while(infile >> remove_word)
	{
		_exclude.insert(remove_word);
	}
	infile.close();
	infile.clear();
}

void Dictionary::build_word_map(string &line)
{
	vector<string> words;
	words.clear();
	segment.cut(line, words);
	for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
	{
		if(!_exclude.count(*iter))
		{
			++_word_map[*iter];
		}
	}
}

void Dictionary::write_dictionary(const string &dictionary_path)
{
	ofstream output;
	if(!open_file(output, dictionary_path.c_str()))
	{
		throw std::runtime_error("open file dictionary.txt error");
	}
	for(map<string, int>::iterator iter = _word_map.begin(); iter != _word_map.end(); ++iter)
	{
		output << iter->first << "\t" << iter->second << std::endl;
	}
	output.close();
	output.clear();
}


