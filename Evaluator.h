//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <string>
using namespace std;

class Evaluator
{
private:



public:
	Evaluator();
	bool check_bool(string expression);
	bool eval_bool(string expression);
	int eval_int(string expression);
};


#endif
