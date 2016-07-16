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
		static const int PRECEDENCE[];


		std::stack<int> operand_stack;
		std::stack<char> parenthesis_stack;
		std::stack<char> operator_stack;



	/** Evaluates the current operator.
	This function pops the two operands off the operand
	stack and applies the operator.
	@param op A character representing the operator
	@throws Syntax_Error if top is attempted on an empty stack
	*/
	int eval_op(char op);{
		
	}
	
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
	
	/** Determines if expression has unmatching parenthesis.
	@param op The expression
	@return The precedence
	*/
	bool is_balanced(const string expression) {
		return PRECEDENCE[OPERATORS.find(op)];
	}
	
	/** Determines whether characters in string are operands or aoperators
	  and adds them to their respective appropriate stacks--
	@param op The expression
	@return two separate stacks operator_stack and operand_stack.
	*/
	int parse_expression(string expression); {
	
	}
	bool check_valid(string str); {
	
	}
	
	/** Determines '--' or '++' occur in the expression and adds one
	 * to the successor if so.
	@param op The expression
	@return updated integer.
	*/
	int decrementIncrement(string str); {
	
	}

	
	
public:
	Evaluator();
	
	bool check_bool(string expression);
	bool eval_bool(string expression);
	int eval_int(string expression);

	void parse_expression(string expression);
	//Michelle Got this from GitHub by kartikkukreja
	bool hasLowerPriority(char op1, char op2);
	int convert_to_int(string number);
	bool divide_by_zero(char opp, int num2);
};


#endif
