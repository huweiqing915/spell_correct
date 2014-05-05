/*************************************************************************
	> File Name: test_spell.cpp
	> Author: huwq
	> Mail:huweiqing915@gmail.com 
	> Created Time: 2014年05月05日 星期一 23时31分10秒
 ************************************************************************/

#include "SpellCorrect.h"
#include <iostream>
using namespace std;

int main()
{
	string s1 = "beautiful";
	SpellCorrect sc;
	sc.correct_word(s1);
	for(int i = 0 ; i != 3; i++)
	{
		cout << sc.get_correct_word() << endl;
	}
	return 0;
}
