//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#include "Evaluator.h"
#include <string>
#include <iostream>

using namespace std;

Evaluator::Evaluator(){};

bool Evaluator::check_bool(string expression)
{
	//if expression contains boolean characters, return true
	for (int i = 0; i < expression.length(); i++)
	{
		if ((expression[i] == '>' || '<' || '!' || '&' || '|') || (expression[i] == '=' && expression[i+1] == '='))
		{
			return true;
		}
	}
	return false;
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
//parse string into two stacks, int_stack and char_stacK
	// to parse is to evaluate the string, it can do math
	// check for <= => and full numbers
	//check next char, if space, skip. if 0-9, convert to integer and add to int_stack. if anything else, add to char_stack.
	//if next char is 0-9, convert to integer
	string number; // == current position in expression <- also have to account for larger numbers
	string character; // to hold the char to put it in the char_stack
	convert_to_int(number);
		for (int i = 0; expression.length(); i++)
		{
			if (expression[i] == " ");
			else if (isdigit(expression[i]))
			{
				number = expression[i]; 
				for (int j = i++; expression.length(); j++)
				{
					if (isdigit(expression[j])) 
					{
						//append to number
						i++;
					}
					else
					{
						break;
						 
					}
						
				}
				if(!number.empty())
				{
					add_to_stack(convert_to_int(number), int_stack); //create add_to_stack function gets the number and the int_stack
				}
				number.clear(); 
				
				if(!isdigit(expression[i])) //should go here?
				{
					character = expression[i];
						for (int j = i++; expression.length(); j++)
						{
							if(!isdigit(expression[j]))
							{
								//append to character
								i++;
							}
							else
							{
								break;
							}
						}
					 
				}
				if(!character.empty())
				{
					add_to_stack(convert_to_int(number), char_stack);
				}
				character.clear();
			} 
				
		}
}

// To check for Priority Got this from GitHub by kartikkukreja
bool Evaluator::hasLowerPriority(char op1, char op2)
{
	bool error;
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
		return op2 == '-' || '+' ;
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
	char firstToken, nextToken, currentToken;
	

//still need 'Expression must have correct parenthesis'

	
//Expression cannot start with a closing parenthesis
	try {
		if (firstToken == ')') {
			throw 001;	
		}
		//else run
	}catch (int x) { //x is specific character location
		cout << "Expression can't start with a closing parenthesis @ char: " 
			 << x << "." << endl;
	 }

//	Expression cannot start with a binary operator
	try {
		if (firstToken == '<' || '>' || '&' || '|' || '='){
			throw 002;
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Expression can't start with a binary operator @ char: "
		   	 << x << "." << endl;
	}

//	Expression cannot contain two binary operators in a row
	try {
		if (currentToken == '&&&&' || '||||') {
			throw 003;
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Two binary operators in a row @ char: "
			 << x << "." << endl;
	}

//Expression cannot contain two operands in a row (15 + 2 3)
	try {
		if (isdigit(currentToken) && isdigit(nextToken)) {
			throw 004;
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Two operands in a row @ char: "
			 << x << "." << endl;
	}
	
// A unary operand cannot be followed by a binary operator (++>3)
	try {
		while (currentToken == '+' || '-' || '*' || '/') {
			if (nextToken == '<' || '>' || '&' || '|') {
				throw 005;
			}
			//else run
		}
	}
	catch (int x) { //x is specific character location
		cout << "A unary operand cannot be followed by a binary operator @ char: "
			 << x << "." << endl;
	}

//Division by zero	
	try {
		while (currentToken == '/') {
			if (nextToken == '0' || 0) {
			throw 006;
			}
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Division by zero @ char: "
			 << x << "." << endl;
	}



//Expression cannot contain letters
	try {

		if (isalpha(currentToken)) {

			throw 004;

		}

		//else run

	}

	catch (int x) { //x is specific character location

		cout << "Expression cannot contain letters @ char: "

			<< x << "." << endl;

	}

	
	/*
	check for the following:
	
	Expression must have correct parenthesis
	
	
//below completed
	//Expression cannot contain letters
	//Expression cannot start with a binary operator
	//Expression cannot contain two binary operators in a row
	//Expression cannot contain two operands in a row (15 + 2 3)
	//A unary operand cannot be followed by a binary operator (++>3)
	//Division by zero
	
	*/
}

int Evaluator::convert_to_int(string number)
{
	//convert a string to an integer value 
	int result = stoi(number);
	return result;
}
