#include "InfixEval.h"
#include "Error.h"
#include <sstream>
#include <cctype>
#include <cmath>
using std::stack;
using std::string;
using std::istringstream;
using std::isdigit;

const string InfixEval::OPERATORS = { "&|=!><+-*/%^-{}()[]" };
const int InfixEval::Preced[] = { 2, 1, 4, 8, 3, 3, 5, 5, 6, 6, 6, 6, 4, -1, -1, -1, -1, -1, -1 };

InfixEval::InfixEval()
{
	//Constructor	
	int infix = 0;
	int answer = 0;
	operator_stack = {};
	integer_stack = {};
}

int InfixEval::eval(const string expression)
{
	answer = 0,
		infix = 0;
	/*
	To be completed by John.
	*/
	// Be sure the stack is empty
	while (!operator_stack.empty())
	{
		operator_stack.pop();
	}
	// Process each token
	istringstream tokens(expression);
	char next_char;
	while (tokens >> next_char)
	{
		if (isdigit(next_char))
		{
			//
			// add to integer_stack
			//
			tokens.putback(next_char);
			int value;
			tokens >> value;
			integer_stack.push(value);
		}
		else if (is_operator(next_char))
		{
			//
			// add to operator stack
			// and check precedence
			//
			tokens.putback(next_char);
			char data;
			tokens >> data;
			process_OP(data);		
		}
		else
		{
			throw Syntax_Error("Invalid character encountered");
		}
	}
	if (operator_stack.empty() && bool_stack.empty())
	{
		throw Syntax_Error("Stack is empty");
	}
	while (!bool_stack.empty() || !operator_stack.empty())
	{
		if (!operator_stack.empty())
		{
			answer = eval_op(operator_stack.top());
			infix += answer;
			integer_stack.push(infix);
		}
		else if (!bool_stack.empty())
		{
			char boolHolder = bool_stack.top();
			bool_stack.pop();
			answer = eval_bool(boolHolder);
		}
		if (operator_stack.empty() && bool_stack.empty())
		{
			return answer;
		}
	}
}

void InfixEval::process_OP(char op)
{
	if ((operator_stack.empty() && bool_stack.empty()) || (op == '(') || (op == '[') || (op == '{'))
	{
		if (op == ')' || op == ']' || op == '}')
			throw Syntax_Error("Unmatched close parenthesis");
		else if (!is_bool(op))
			operator_stack.push(op);
		else
			bool_stack.push(op);
	}
	else
	{
		if ((is_bool(op) && !(bool_stack.empty())) && (precedence(op) >= precedence(bool_stack.top())))
		{
			bool_stack.push(op);
		}
		else if ((is_bool(op) && !(operator_stack.empty())) && (precedence(op) >= precedence(operator_stack.top())))
		{
			operator_stack.push(op);
		}
		else
		{
			// Pop all stacked operators with equal
			// or higher precedence than op.
			while (!operator_stack.empty()
				&& (operator_stack.top() != '(')
				&& (operator_stack.top() != '[')
				&& (operator_stack.top() != '{')
				&& (precedence(op) <= precedence(operator_stack.top())))
			{
				infix += eval_op(operator_stack.top());
				integer_stack.push(infix);
				infix = 0;
			}
			while (!bool_stack.empty()
				&& (operator_stack.top() != '(')
				&& (operator_stack.top() != '[')
				&& (operator_stack.top() != '{')
				&& (precedence(op) <= precedence(bool_stack.top())))
			{
				infix += eval_bool(bool_stack.top());
				integer_stack.push(infix);
				infix = 0;
			}
			// assert: Operator stack is empty or 
			//         top of stack is '(' or current
			//         operator precedence > top of stack operator
			//         precedence;
			if (op == ')')
			{
				if (!operator_stack.empty() && (operator_stack.top() == '('))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else if (op == ']')
			{
				if (!operator_stack.empty() && (operator_stack.top() == '['))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else if (op == '}')
			{
				if (!operator_stack.empty() && (operator_stack.top() == '{'))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else if (is_bool(op))
				bool_stack.push(op);
			else
				operator_stack.push(op);
		}
	}
}

int InfixEval::eval_bool(char op)
{
	bool result = true;
	char boolVar = op;
	int rghtSolution = integer_stack.top();
	integer_stack.pop();
	if (integer_stack.empty())
	{
		switch (boolVar)
		{
		case '!':
			result = !(rghtSolution);
			break;
		}
		if (result == true)
			return 1;
		if (result == false)
			return 0;
	}
	int	lftSolution = integer_stack.top();
	integer_stack.pop();

	switch (boolVar)
	{
	case '=':
		if (!bool_stack.empty())
		{
			char boolNxt = bool_stack.top();
			bool_stack.pop();

			if (boolNxt == '<')
			{
				result = (lftSolution <= rghtSolution);
			}
			if (boolNxt == '>')
			{
				result = (lftSolution >= rghtSolution);
			}
			if (boolNxt == '=')
			{
				result = (lftSolution == rghtSolution);
			}
			if (boolNxt == '!')
			{
				result = (lftSolution != rghtSolution);
			}
		}
		else
		{
			result = (lftSolution < rghtSolution);
			bool_stack.pop();
		}
		break;
	case '>':
		result = (lftSolution > rghtSolution);
		break;
	case '<':
		result = (lftSolution < rghtSolution);
		break;
	case '&':
		if (bool_stack.empty())
			throw exception("Syntax Error: Improper use of AND opperator.");
		if (!bool_stack.empty())
		{
			char boolNxt = bool_stack.top();
			if (boolNxt != '&')
				throw exception("Syntax Error: Improper use of AND opperator.");
			else
			{
				result = (lftSolution == rghtSolution);
				bool_stack.pop();
			}
		}
		break;
	case '|':
		if (bool_stack.empty())
			throw exception("Syntax Error: Improper use of AND opperator.");
		if (!bool_stack.empty())
		{
			char boolNxt = bool_stack.top();
			bool_stack.pop();
			if (boolNxt != '|' || integer_stack.empty())
				throw exception("Syntax Error: Improper use of OR opperator.");
			else if (boolNxt == '|')
			{
				result = (lftSolution || rghtSolution);
			}
		}
		break;
	}
	if (result == true)
		return 1;
	if (result == false)
		return 0;
}

int InfixEval::eval_op(char op) {

	if (operator_stack.empty())
		throw Syntax_Error("Stack is empty");
	int rhs = integer_stack.top();
	integer_stack.pop();
	char oper = operator_stack.top();
	operator_stack.pop();
	int lhs = integer_stack.top();
	integer_stack.pop();
	int result = 0;
	switch (oper) {
	case '+': result = lhs + rhs;
		break;
	case '-': result = lhs - rhs;
		break;
	case '*': result = lhs * rhs;
		break;
	case '/': result = lhs / rhs;
		break;
	case '%': result = lhs % rhs;
		break;
	case '^': result = pow(lhs, rhs);
		break;
	}
	return result;
}