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
	*Determines precedence and assigns Value
	*@Param OPERATORS Precedence.
	*/
	int precedence(char operat) const { return Preced[OPERATORS.find(operat)]; }
	/**
	*Simple Bool Check for OPERATOR
	*@Param next_Char from Tokens.
	*/
	bool is_operator(char ch) const { return OPERATORS.find(ch) != string::npos; }
	bool is_bool(char ch) const
	{
		if (ch == '<' || ch == '>' || ch == '=' || ch == '&' || ch == '|' || ch == '!')
			return true;
		else
			return false;
	}
	/**
	*Process/Eval methods
	*@Param Next_Char from expression and takes info
	*@Param From all 3 stacks.
	*/
	void process_OP(char op);
	int eval_op(char op);
	int eval_bool(char op);

	//DATA Fields
	static const int Preced[];
	static const string OPERATORS;
	static const string BOOLEAN;
	int infix, answer;
	stack<char> operator_stack;
	stack<int> integer_stack;
	stack<char> bool_stack;

};