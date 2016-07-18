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

const string Evaluator::OPERATORS = "^*/%+-&|!=<>()[]{}";
const int Evaluator::PRECEDENCE[18] = { 7,6,6,6,5,5,2,3,3,4,-1,-1,-1,-1,-1,-1,-1,-1 };
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


//What is the plan with eval_bool and eval_int?
bool Evaluator::eval_bool(string expression)
{
	parse_expression(expression); //parse string into two stacks, one for integers and another for characters
	//
		return false;//temp test value
}

int Evaluator::eval_int(string expression)
{
	parse_expression(expression); //parse string into two stacks, one for integers and another for characters
	//
		return 0;//temp test value

}
//Need condition to handle decrement and increment
//(expression[i] == '-' && expression[i + 1] == '-') || (expression[i] == '+' && expression[i + 1] == '+') ||
//crude increment decrement 
//not sure how to push result onto stack at the appropraite time
void Evaluator::decrementIncrement(string str) {
	char firstToken = str[0];
	char currentToken;
	char nextToken;
	char nextNextToken;
	int count = 0;

	for (unsigned int i = 0; i < str.length()-1; i++) {
		count++;
		currentToken = str[i];
		nextToken = str[i + 1];
		nextNextToken = str[i + 2];
		while (currentToken == '-' && nextToken == '-') {
			nextNextToken = nextNextToken - 1;
			operand_stack.push(nextNextToken);

		}
		while (currentToken == '+' && nextToken == '+') {
			nextNextToken = nextNextToken + 1;
			operand_stack.push(nextNextToken);
		}
	}

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

//is_open and is_close find matching parenthesis in expression
bool is_open(char ch) {
	return OPEN.find(ch) != string::npos;
}

bool is_close(char ch) {
	return CLOSE.find(ch) != string::npos;
}

bool Evaluator::is_balanced(const string expression) {
	// Uses temporary stack  
	//has been tested
	//to determine if parentheses in expression match
	

	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end())) {
		char next_ch = *iter;
		if (is_open(next_ch)) {
			parenthesis_stack.push(next_ch);
			//cout << next_ch << " was pushed onto parenthesis stack " << endl;
		}
		else if (is_close(next_ch)) {
			if (parenthesis_stack.empty()) {
				balanced = false;
				throw Syntax_Error("Unmatched parenthesis entered ");
			}
			else {
				char top_ch = parenthesis_stack.top();
				parenthesis_stack.pop();
				balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
				//cout << top_ch << " Parenthesis in temporary stack are balanced. " << next_char << endl;

			}
		}
		++iter;
	}
	return balanced && parenthesis_stack.empty();
}

//this function is currently called in int parse_expression 
//This function would have popped the two operands off the operand stack and applied the operator.
//So.. it is basically mathing()
int Evaluator::eval_op(char next_char){
	cout << "mathing " << next_char << endl;
	return next_char;
}

/*	//eval_op came from postfix evaluator
	// Jeremy, I only put this here because it looked like a good start . Do with it what you will~James
	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
	int rhs = operand_stack.top();
	//cout << "push rhs " << rhs << endl;
	operand_stack.pop();


	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
	int lhs = operand_stack.top();
	//cout << "push lhs " << lhs << endl;
	operand_stack.pop();

	int result = 0;
	switch (op) {
	case '+': result = lhs + rhs;
		cout << "lhs + rhs = " << lhs << " + " << rhs << " = " << result << endl;
		break;
	case '-': result = lhs - rhs;
		cout << "lhs - rhs = " << lhs << " - " << rhs << " = " << result << endl;
		break;
	case '*': result = lhs * rhs;
		cout << "lhs * rhs = " << lhs << " * " << rhs << " = " << result << endl;
		break;
	case '/': result = lhs / rhs;
		cout << "lhs / rhs = " << lhs << " / " << rhs << " = " << result << endl;
		break;
	case '%': result = lhs % rhs;
		break;
	}
	//cout << result << endl;

	return result;


}*/



bool Evaluator::check_valid(string expression){
/*	//this code has been tested
//check_valid() checks for the following:

//Expression must have correct beginning parenthesis
//Expression cannot contain letters
//Expression cannot start with a binary operator
//Expression cannot contain two binary operators in a row
//Expression cannot contain two operands in a row (15 + 2 3)
//A unary operand cannot be followed by a binary operator (++>3)
//Simpl division by zero

*/

char firstToken = expression[0];
char currentToken;
char nextToken;
char nextNextToken;
int count = 0;



try {

	for (unsigned int i = 0; i < expression.length()-1; i++) {
		count++;
		currentToken = expression[i];
		nextToken = expression[i + 1];
		nextNextToken = expression[i + 2];



		//Expression cannot start with a binary operator
		if (firstToken == '<' || firstToken == '>' || firstToken == '&' || firstToken == '|' ||
			firstToken == '=') {
			cout << "Expression can't start with a binary operator @ char: ";
			count++;
			throw "first";
		}

		//Expression cannot start with a closing parenthesis
		if ((firstToken == ')') || (firstToken == ']') || (firstToken == '}')) {
			cout << "Open parenthesis must come before closing parenthesis @ char: ";
			throw 001;
		}


		// A unary operand cannot be followed by a binary operator (++>3)
		if (((currentToken == '+' || currentToken == '-' || currentToken == '*' || currentToken == '/' ||
			currentToken == '%') && (nextToken == '<' || nextToken == '>' || nextToken == '&' ||
			nextToken == '|'))) {

			cout << "A unary operand cannot be followed by a binary operator @ char: ";
			throw 003;
		}

		//Expression cannot contain two binary operators in a row (&&& or |||)
		if ((currentToken == '&' && nextToken == '&' && nextNextToken == '&') ||
			(currentToken == '|' && nextToken == '|' && nextNextToken == '|') ||
			(currentToken == '&' && nextToken == '|') || (currentToken == '|' && nextToken == '&')) {
			cout << "Too many or wrong successive binary operators starting @ char: ";
			throw 004;
		}

		//Expression cannot contain two operands in a row (15 + 2 3)
		if (isdigit(currentToken) && nextToken == ' ' && isdigit(nextNextToken)) {
			count++;
			cout << "Either an extra space was inputted or you are missing an operator @ char: ";
			throw 005;
		}



		//Simple case division by zero	//Jeremy is working on the extension of this as a function
		if (currentToken == '/') {
			if (nextToken == '0' || 0) {
				cout << "Division by zero @ char: ";
				throw 006;
			}
		}

		//Expression cannot contain letters
		if (isalpha(currentToken)) {
			cout << "Expression cannot contain letters @ char: ";
			throw 007;
		}

	}

	//run code here
////////////////////////////////////////////
	Evaluator::is_balanced(expression);//checks if Parenthesis are balanced. Throws error if unbalanced
	
	//Evaluator::divide_by_zero(opp, num2); //checks expressions after '/' for eval to 0
	
	Evaluator::parse_expression(expression);//adds characters and digits to their appropriate stacks

	Evaluator::check_bool(expression); //check if expression should be evaluated as a boolean or an integer value. True = boolean, False = integer

	if (Evaluator::check_bool(expression)) //boolean
	{
		bool bool_result = Evaluator::eval_bool(expression);
		cout << expression << " = " << bool_result << endl;
	}
	else //integer
	{
		int int_result = Evaluator::eval_int(expression);
		cout << expression << " = " << int_result << endl;
	}

///////////////////////////////////////////

}   //End of try

	catch (...) { //count is specific character location
		cout << count << "." << endl;
	}//end of catch

}

int Evaluator::convert_to_int(string number)
{
	//convert a string to an integer value 
	int result = stoi(number);
	return result;
}

//Is this done?
bool Evaluator::divide_by_zero(char opp, int num2)
{
	//return false if second int is zero
	if( (opp == '/' || opp == '%') && (num2 == 0))
	{
		return false;
	}
	return true;
}   

bool Evaluator::bool_mathing_wrapper()
{
	while (!operator_stack.empty())
	{
		char op = (operator_stack.top());
		operator_stack.pop();
		int rhs = operand_stack.top();
		operand_stack.pop();
		int lhs = operand_stack.top();
		operand_stack.pop();
		bool_mathing(op, rhs, lhs);
	}
	return(operator_stack.top());
}

bool Evaluator::bool_mathing() 
//TO DO:
//ADD UNARY OPERATOR EVALUATIONS
{
	while (!operator_stack.empty())
	{
		int result = 0;

		switch (op) {
		case ')': 
		while (op != '(')
		{
			bool_mathing(operator_stack.top(), rhs, lhs);
		}
		case '+': result = lhs + rhs;
			break;
		case '-': result = lhs - rhs;
			break;
		case '*': result = lhs * rhs;
			break;
		case '/': 
			if (divide_by_zero(op, rhs)) //if expression is valid
			{
				result = lhs / rhs;
				break;
			}
			else
			{
				cout << "ERROR: Cannot divide by zero" << endl; //throw divide by zero error
				break;
			}

		case '%': 
			if (divide_by_zero(op, rhs)) //if expression is valid
			{
				result = lhs % rhs;
				break;
			}
			else
			{
				cout << "ERROR: Cannot divide by zero" << endl; //throw divide by zero error
				break;
			}
		case '<': result = (lhs < rhs);
			break;
		case '>': result = (lhs > rhs);
			break;
		}
		operand_stack.push(result);
	}
	return(operator_stack.top());
}


int Evaluator::int_mathing()
//TO DO:
//Account for ++ and --
{
	while (!operator_stack.empty())
	{
		char op = (operator_stack.top());
		operator_stack.pop();
		int rhs = operand_stack.top();
		operand_stack.pop();
		int lhs = operand_stack.top();
		operand_stack.pop();
		int result = 0;

		switch (op) {
		case '+': result = lhs + rhs;
			break;
		case '-':
			//if next char is also - ?
			//deal with --
			//else
			result = lhs - rhs;
			break;
		case '*': result = lhs * rhs;
			break;
		case '/':
			if (divide_by_zero(op, rhs)) //if expression is valid
			{
				result = lhs / rhs;
				break;
			}
			else
			{
				cout << "ERROR: Cannot divide by zero" << endl; //throw divide by zero error
				break;
			}

		case '%':
			if (divide_by_zero(op, rhs)) //if expression is valid
			{
				result = lhs % rhs;
				break;
			}
			else
			{
				cout << "ERROR: Cannot divide by zero" << endl; //throw divide by zero error
				break;
			}
		}
		operand_stack.push(result);
	}
	return(operator_stack.top());
}
