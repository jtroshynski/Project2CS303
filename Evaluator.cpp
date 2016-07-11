//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#include "Evaluator.h"
#include <string>
using namespace std;

Evaluator::Evaluator(){};

bool Evaluator::check_bool(string expression)
{
	//if expression contains boolean characters, return true
}

bool Evaluator::eval_bool(string expression)
{
	parse_expression(expression); //parse string into two stacks, one for integers and another for characters
	//
}

int Evaluator::eval_int(string expression)
{
	parse_expression(expression); //parse string into two stacks, one for integers and another for characters
	//
}

void Evaluator::parse_expression(string expression)
{
	//parse string into two stacks, int_stack and char_stack
	//check next char, if space, skip. if 0-9, convert to integer and add to int_stack. if anything else, add to char_stack.
	
	//if next char is 0-9, convert to integer
	string number; // == current position in expression <- also have to account for larger numbers
	convert_to_int(number);
}

// To check for Priority Got this from GitHub by kartikkukreja
bool Evaluator::hasLowerPriority(char op1, char op2)
{
	//PEMDAS
	switch (op1)
	{
	case '(': 
		return false;
		break;
	case '-':
		return op2 == '-';
		break;
	case '+':
		return op2 == '-' || op2 '+' ;
		break;
	case '*':
		return true;
		break;
	case '/':
		return true;
		break;
	default:
		error = true; 
		return false;
	}
}

bool Evaluator::check_valid()
{
	/*
	check for the following:
	Expression cannot start with a closing parenthesis
	Expression cannot start with a binary operator
	Expression cannot contain two binary operators in a row
	Expression cannot contain two operands in a row (15 + 2 3)
	A unary operand cannot be followed by a binary operator (++>3)
	Division by zero
	Expression cannot contain letters
	Expression must have correct parenthesis
	*/
}

int Evaluator::convert_to_int(string number)
{
	//convert a string to an integer value 
}
