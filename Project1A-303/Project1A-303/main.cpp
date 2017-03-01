#include "InfixEval.h"
/**
*@Author Jeff Morgan, John Widner, Murad Isgandarli
*
*/

int main()
{
	//Create random pieces of code to run self-generated Scripts
	InfixEval eval,eval1,eval2,eval3,eval4;
	
	int result = eval.eval("1+2*3");
	cout << result << endl;
	
	int result2 = eval1.eval("2+2 ^2* 3");
	cout << result2 << endl;
	
	int result3 = eval2.eval("1==2");
	cout << result3 << endl;

	int result4 = eval3.eval("1+3 > 2");
	cout << result4 << endl;

	int result5 = eval4.eval("(1+2) * 3");
	cout << result5 << endl;

	system("pause");
	return 0;

}