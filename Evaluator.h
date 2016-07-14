//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <string>
#include <stack>
#include "list.h"
#include "list_iterator.h"
#include "list_const_iterator.h"

using namespace std;

class Evaluator
{
private:
	list <int> int_stack;
	list <char> char_stack;
	
	// Data fields
		static const string OPERATORS;
		std::stack<int> operand_stack;
		static const int PRECEDENCE[];


	/** Evaluates the current operator.
	This function pops the two operands off the operand
	stack and applies the operator.
	@param op A character representing the operator
	@throws Syntax_Error if top is attempted on an empty stack
	*/
	int eval_op(char op);
	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/
	bool is_operator(char ch) const {
		return OPERATORS.find(ch) != string npos;	
	}
	/** Determines the precedence of an operator.
	@param op The operator
	@return The precedence
	*/
	int precedence(char op) const {
		return PRECEDENCE[OPERATORS.find(op)];
	}


public:
	Evaluator();
	
	bool check_bool(string expression);
	bool eval_bool(string expression);
	int eval_int(string expression);
	int parse_expression(string expression);
	void parse_expression(string expression);
	//Michelle Got this from GitHub by kartikkukreja
	bool hasLowerPriority(char op1, char op2);
	bool check_valid();
	int convert_to_int(string number);
};


#endif
