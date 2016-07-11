//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <string>
#include "list.h"
#include "list_iterator.h"
#include "list_const_iterator.h"
using namespace std;

class Evaluator
{
private:
	list <int> int_stack;
	list <char> char_stack;

public:
	Evaluator();
	bool check_bool(string expression);
	bool eval_bool(string expression);
	int eval_int(string expression);
	void parse_expression(string expression);
	//Michelle Got this from GitHub by kartikkukreja
	bool hasLowerPriority(char op1, char op2);
	bool check_valid();
	int convert_to_int(string number);
};


#endif
