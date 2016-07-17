//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <string>
#include <stack>

//if we don't need these list files and you guys concur go ahead and delete
//#include "list.h"
//#include "list_iterator.h"
//#include "list_const_iterator.h"

using namespace std;

class Evaluator
{
private:
	////if we don't need this list stuff and you guys concur go ahead and delete
	//list <int> int_stack;
	//list <char> char_stack;
	
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
	int eval_op(char next_char);
		
	
	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/
	bool is_operator(char ch) const {
		return OPERATORS.find(ch) != string::npos;	
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
	@return bool
	*/
	bool is_balanced(const string expression);
	//	return PRECEDENCE[OPERATORS.find(op)];
	
	
	/** Determines whether characters in string are operands or operators
	  and adds them to their respective stacks--
	@param op The expression
	@return two separate stacks operator_stack and operand_stack.
	*/
	int parse_expression(string expression); 
	
	/** Determines '--' or '++' occur in the expression and adds one
	 * to the successor if so.
	@param op The expression
	@return updated integer.
	*/
	int decrementIncrement(string str); 

	
	
public:
	Evaluator();
	
	/** Exception handling:
	//Expression must have correct beginning parenthesis
	//Expression cannot contain letters
	//Expression cannot start with a binary operator
	//Expression cannot contain two binary operators in a row
	//Expression cannot contain two operands in a row (15 + 2 3)
	//A unary operand cannot be followed by a binary operator (++>3)
	//Simple division by zero
	@param op The expression
	@return error*/
	bool check_valid(string expression);
	bool check_bool(string expression);
	bool eval_bool(string expression);
	int eval_int(string expression);

	//void parse_expression(string expression);
	
	//Michelle Got this from GitHub by kartikkukreja
	bool hasLowerPriority(char op1, char op2);
	int convert_to_int(string number);
	bool divide_by_zero(char opp, int num2);
	bool bool_mathing(char op, int rhs, int lhs);
	bool bool_mathing_wrapper();
	int int_mathing();
	
};


#endif
