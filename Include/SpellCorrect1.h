/*************************************************************************
	> File Name: SpellCorrect.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 20时34分36秒
 ************************************************************************/

#ifndef SPELL_CORRECT_H_
#define SPELL_CORRECT_H_ 

#include <string>
#include <stdexcept>
#include <fstream>
#include <queue>
#include <vector>

#include <string.h>
#include <stdint.h>

#include "Log.h"
#include "MixSegment.hpp"

#define DATA_PATH /var/www/spell_correct/Data
#define DISTANCE_DISTRICT 5

struct CorrectWord 
{
	int _edit_distance;
	std::string _word;
	int _frequency;

	CorrectWord(int distance, const std::string &word, int frequency):
		_edit_distance(distance), _word(word), _frequency(frequency)
	{
		//default construct
	}
};

struct compare 
{
	bool operator()(const CorrectWord &a, const CorrectWord &b)
	{
		if(a._edit_distance == b._edit_distance)
		{
			return a._frequency < b._frequency;
		}
		else
			//first compare edit distance
			return a._edit_distance > b._edit_distance;
	}
};

class SpellCorrect {
public:
	SpellCorrect();
	virtual ~SpellCorrect();

	int edit_distance(const std::string &, const std::string &);
	void correct_word(const std::string &);
	std::string get_correct_word();
	bool is_queue_empty();

private:
	const char * const dict_path;
	const char * const model_path;
	std::priority_queue<CorrectWord, std::vector<CorrectWord>, compare>  _correct_word_queue;
	std::vector<std::priority_queue<CorrectWord, std::vector<CorrectWord>, compare> > _correct_word_vector;
	CppJieba::MixSegment segment;
	std::vector<std::string> _dictionary_paths;

	void get_dictionary();
	inline bool is_ascii(const std::string &str);
};

#endif
