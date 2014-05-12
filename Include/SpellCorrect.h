/*************************************************************************
	> File Name: SpellCorrect.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月09日 星期五 15时18分01秒
 ************************************************************************/

#ifndef SPELL_CORRECT_H_
#define SPELL_CORRECT_H_ 

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <vector>

#include <string.h>
#include <stdint.h>

#include "EncodingConverter.h"
#include "Log.h"

#define MAX_DISTANCE_DISTRICT 5  //编辑距离阈值，大于这个值就不进入优先级队列 

struct CorrectWord {
	int _edit_distance;
	std::string _word;
	int _frequency;

	CorrectWord(int distance, const std::string &word, int frequency):_edit_distance(distance), _word(word), _frequency(frequency)
	{
		//construct
	}

	bool operator<(const CorrectWord &other) const //给后面用到的set提供比较方法
	{
		return _word < other._word;
	}
};

struct compare {
	bool operator()(const CorrectWord &a, const CorrectWord &b)
	{
		if(a._edit_distance == b._edit_distance)
		{
			return a._frequency < b._frequency;
		}
		else
			//先比较编辑距离
			return a._edit_distance > b._edit_distance;
	}
};

class SpellCorrect {
public:
	typedef std::unordered_map<std::string, std::map<std::string, int> > _query_index;
	typedef std::unordered_map<std::string, std::map<std::string, int> >::iterator _index_iter;
	int edit_distance(const std::string &, const std::string &);
	void query_word(const std::string &, _query_index &);
	std::string get_correct_word();
	std::string get_word_queue_top(std::string &);
	bool is_queue_empty();

private:
	std::priority_queue<CorrectWord, std::vector<CorrectWord>, compare> _correct_word_queue;
	std::set<CorrectWord> _word_set;
};

#endif

