/*************************************************************************
	> File Name: SpellCorrect.h
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 20时34分36秒
 ************************************************************************/

#ifndef SPELL_CORRECT_H_
#define SPELL_CORRECT_H_ 

#include <string>
#include <string.h>
#include <stdexcept>
#include <fstream>
#include <queue>
#include <vector>

struct CorrectWord {
	int _edit_distance;
	std::string _word;
	int _frequency;

	CorrectWord(int distance, const std::string &word, int frequency):_edit_distance(distance), _word(word), _frequency(frequency)
	{
		//default construct
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
			//first compare edit distance
			return a._edit_distance > b._edit_distance;
	}
};

class SpellCorrect {
public:
	int edit_distance(const std::string &, const std::string &);
	void correct_word(const std::string &);
	std::string get_correct_word();
	bool is_queue_empty();
private:
	std::priority_queue<CorrectWord, std::vector<CorrectWord>, compare> _correct_word_queue;
};

#endif
