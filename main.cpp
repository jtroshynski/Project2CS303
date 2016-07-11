//Jeremy Troshynski
//Michelle Gardner
//James Harrison
//CS 303
//Project 2A

#include "Evaluator.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
	Evaluator eval1;
	string expression = ("1+2+3+4"); //enter in any expression in string format
	eval1.check_bool(expression); //check if expression should be evaluated as a boolean or an integer value. True = boolean, False = integer

	if (eval1.check_bool(expression)) //boolean
	{
		bool bool_result = eval1.eval_bool(expression);
		cout << expression << " = " << bool_result << endl;
	}
	else //integer
	{
		int int_result = eval1.eval_int(expression);
		cout << expression << " = " << int_result << endl;
	}

	return 0;
}
