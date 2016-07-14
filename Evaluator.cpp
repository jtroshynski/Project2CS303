//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#include "Syntax_Error.h"
#include "Evaluator.h"
#include <string>
#include <iostream>
#include <sstream>

using std::istringstream;

using namespace std;

const string Evaluator::OPERATORS = "^*/%+-&|!=<>";
const int Evaluator::PRECEDENCE[] = { 7,6,6,6,5,5,2,3,3,4 };
// The set of opening parentheses.
const string OPEN = "([{";
// The corresponding set of closing parentheses.
const string CLOSE = ")]}";

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

//Need condition to handle decrement and increment
//(expression[i] == '-' && expression[i + 1] == '-') || (expression[i] == '+' && expression[i + 1] == '+') ||

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
int Evaluator::parse_expression(string expression)
{
	istringstream tokens(expression);
	char next_char;
	while (tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operand_stack.push(value);
		}
		else if (is_operator(next_char)) {
			int result = eval_op(next_char);
			
	//add--if the next char is '--', '++', '&&', ||, '=='//hold off for now 7-14jeh

			
			operator_stack.push(result);
		}
		else {
			throw Syntax_Error("Invalid character encountered");
		}
	}
	if (!operand_stack.empty()) {
		int answer = operand_stack.top();
		operand_stack.pop();
		if (operand_stack.empty()) {
			return answer;
		}
		else {
			throw Syntax_Error("Stack should be empty");
		}
	}
	else {
		throw Syntax_Error("Stack is empty");
	}
}
/*void Evaluator::parse_expression(string expression)
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
}*/

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


bool is_open(char ch) {
	return OPEN.find(ch) != string::npos;
}

bool is_close(char ch) {
	return CLOSE.find(ch) != string::npos;
}

bool Evaluator::is_balanced(const string expression) {
	// A stack for the open parentheses that haven't been matched
	
	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end())) {
		char next_ch = *iter;
		if (is_open(next_ch)) {
			operator_stack.push(next_ch);
		}
		else if (is_close(next_ch)) {
			if (operator_stack.empty()) {
				balanced = false;
			}
			else {
				char top_ch = operator_stack.top();
				operator_stack.pop();
				balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
			}
		}
		++iter;
	}
	return balanced && operator_stack.empty();
}



bool Evaluator::check_valid(int characterPositionOfError, string expression)
{
	char firstToken = expression[0];
	char nextToken, currentToken;
	
	
	
	
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
		for (int i = 0; i < expression.length(); i++){
			currentToken = expression[i];
				if (currentToken == '&&&&' || '||||') {
					throw 003;
				}
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Two binary operators in a row @ char: "
			 << x << "." << endl;
	}

//Expression cannot contain two operands in a row (15 + 2 3)//////need to fix
	try {
		for (int i = 0; i < expression.length(); i++){
			currentToken = expression[i];
			nextToken = expression[i + 1];
			if (isdigit(currentToken) && isdigit(nextToken)) {
				throw 004;
			}
		}
		//else run
	}
	catch (int x) { //x is specific character location
		cout << "Two operands in a row @ char: "
			 << x << "." << endl;
	}
	
// A unary operand cannot be followed by a binary operator (++>3)
	try {
		for (int i = 0; i < expression.length(); i++){
			currentToken = expression[i];
			nextToken = expression[i + 1];
			while (currentToken == '+' || '-' || '*' || '/') {
				if (nextToken == '<' || '>' || '&' || '|') {
					throw 005;
				}
			}
		}//else run
	}
	catch (int x) { //x is specific character location
		cout << "A unary operand cannot be followed by a binary operator @ char: "
			 << x << "." << endl;
	}

//Simple Division by zero	//Jeremy is working on the extension of this as a function
	try {
		for (int i = 0; i < expression.length(); i++){
			currentToken = expression[i];
			nextToken = expression[i + 1];
			while (currentToken == '/') {
				if (nextToken == '0' || 0) {
					throw 006;
				}
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
		for (int i = 0; i < expression.length(); i++){
			currentToken = expression[i];

			if (isalpha(currentToken)) {

				throw 004;
			}
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

bool Evaluator::divide_by_zero(char opp, int num2)
{
	//return false if second int is zero
	if( (opp == '/' || opp == '%') && (num2 == 0))
	{
		return false;
	}
	return true;
}    
