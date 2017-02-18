#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <ctype.h>

using namespace std;

class InfixEval
{

public:
	
	InfixEval();
	
	int eval(const string expression);

private:
	
	
	/**
		Determines precedence and assigns Value
		@Param OPERATORS Precedence.
	*/
	int precedence(char operat) const 
	{
		return Preced[OPERATORS.find(operat)];
	}
	/**
		Simple Bool Check for OPERATOR
		@Param next_Char from Tokens.
	*/
	bool is_operator(char ch) const 
	{
		return OPERATORS.find(ch) != string::npos;
	}
	
	
	void process_OP(char op);
	int eval_op(char op);

	
	//DATA Fields
	static const int Preced[];
	static const string OPERATORS;
	string infix;
	stack<char> operator_stack;

};
