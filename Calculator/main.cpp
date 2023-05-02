#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <cmath>
#include <cctype>
#include <windows.h>

using namespace std;

void Check(string &, long double &, int &);
bool IsOperand(char);
bool IsOperator(char);
bool TakesPrecedence(char, char);
void Convert(const string &, string &);
double sToDbl(string const&);
void Calculate(const string &, const string &, long double &);
double DoMath(double,double,char);

int main()
{  
	SetConsoleTitle(L"Postfix Calculator.");

	string infix, postfix;
	long double result = 0.0;

	for( int i = 1; i <= 5 ; i++ )
	{
		switch(i)
		{
		case 1:
			postfix.erase();
			infix.erase();
			cout << "Enter equation (\"q\" for quit): ";
			getline(cin, infix);
			cout << endl;
			if (!(infix.compare("q"))) return 0;
			break;
		case 2:
			Check(infix, result, i);
			break;
		case 3:
			Convert(infix, postfix);
			//cout << "Postfix form:" << postfix << endl;
			break;
		case 4:
			Calculate(postfix, infix, result);
			break;
		case 5:
			cout << "\nResult: " << result << endl << endl;
			i = 0;
			break;
		}
	}	

	return 0;
}

void Check(string &infix, long double & result, int &st)
{
	short counter = 0;
	string symbols = "+-*/()^.0123456789";

	for ( int i = 1; i <= 5; i++ )
	{
		switch (i)
		{
		case 1:
			cout << "Letter/s, Blank/s...";
			for ( string::size_type i = 0; i < infix.size(); i++ )
			{
				if ( isalpha(infix[i]) || isspace(infix[i]) )
				{
					infix.erase(i, 1);
					i--;
					counter++;
				}
			}
			if (counter != 0)
			{
				cout << "ERROR!\nThere were letter/s, blank/s in the equation! They were deleted." << endl;
				counter = 0;
			}
			else cout << "OK!" << endl;
			break;

		case 2:
			cout << "Operator/s...";
			for ( string::size_type i = 0; i < infix.size(); i++ )
			{
				if ( IsOperator(infix[i]) && IsOperator(infix[i+1]) )
					counter++;
				else if (IsOperator(infix[infix.size()-1]) || IsOperator(infix[0]))
					counter++;
			}
			if (counter != 0)
			{
				cout << "ERROR!\nThere were error using operators!" << endl;
				counter = 0;
				st = 0;
			}
			else cout << "OK!" << endl;
			break;

		case 3:
			cout << "Parenthesis...";
			for ( string::size_type i = 0; i < infix.size(); i++ )
				if ( infix[i] == '(' || infix[i] == ')' )
					counter++;

			if (counter % 2 != 0)
			{
				cout << "ERROR!\nThere were error placing parenthesis!" << endl;
				counter = 0;
				st = 0;
			}
			else
			{
				cout << "OK!" << endl;
				counter = 0;
			}
			break;

		case 4:
			cout << "Unknown symbol/s...";
			for (size_t i = 0; i < infix.size(); i++)
			{
				for(size_t j = 0; j < symbols.size(); j++)
				{
					if(infix[i] == symbols[j])
					{
						counter++;
					}
				}
			}
			if (counter != infix.size())
			{
				cout << "ERROR!\nThere were unknown symbol/s detected in equation!" << endl;
				st = 0;
				counter = 0;
			}
			else
			{
				cout << "OK!" << endl;
				counter = 0;
			}
			break;

		case 5:// if there is only number entered, convert it to integer and print it as result
			for ( string::size_type i = 0; i < infix.size(); i++ )
				if ( !IsOperand(infix[i]) )counter++;

			if (counter == 0)
			{
				result = sToDbl(infix);
				st = 4;
			}
		}
	}
	cout << endl;
}

bool IsOperand(char ch)
{
	if ((ch >= '0') && (ch <= '9') || (ch == '.'))
		return true;
	else
		return false;
}

bool IsOperator(char ch)
{
	if (((ch == '*') || (ch == '/')) ||
		((ch == '+') || (ch == '-')) || (ch == '^'))
		return true;
	else
		return false;
}


bool TakesPrecedence(char OperatorA, char OperatorB)
{
	if (OperatorA == '(')
		return false;
	else if (OperatorB == '(')
		return false;
	else if (OperatorB == ')')
		return true;
	else if ((OperatorA == '^') && (OperatorB == '^'))
		return false;
	else if (OperatorA == '^')
		return true;
	else if (OperatorB == '^')
		return false;
	else if ((OperatorA == '*') || (OperatorA == '/'))
		return true;
	else if ((OperatorB == '*') || (OperatorB == '/'))
		return false;
	else
		return true;
}

void Convert(const string & infix, string & postfix)
{
	stack <char> OperatorStack;
	const string BLANK = " ";
	char TopSimbol, Simbol;

	for (string::size_type i = 0; i < infix.length(); i++)
	{
		Simbol = infix[i];
		if (IsOperand(Simbol))
		{
			postfix += BLANK + Simbol;
			while ( IsOperand(infix[i+1]))
			{
				postfix.append(1, infix[i+1]);
				i++;
			}
		}
		else
		{
			while ((!OperatorStack.empty()) &&
				(TakesPrecedence(OperatorStack.top(), Simbol)))
			{
				TopSimbol = OperatorStack.top();
				OperatorStack.pop();
				postfix += BLANK + TopSimbol;
			}

			if ((! OperatorStack.empty()) && (Simbol == ')'))
				OperatorStack.pop();
			else
				OperatorStack.push(Simbol);
		}
	}
	while (!OperatorStack.empty())
	{
		TopSimbol = OperatorStack.top();
		OperatorStack.pop();
		postfix += BLANK + TopSimbol;
	}
}

double sToDbl(string const& str) {

	istringstream ss(str);
	long double d;
	ss >> d;

	return d;
}

void Calculate(const string &postfix, const string &infix, long double &result)
{

	stack <long double> NumberStack;

	for (string::size_type i = 0; i < postfix.length(); i++)
	{
		char ch = postfix[i];
		string number;
		number.clear();

		if (IsOperand(postfix[i]))
		{
			number.append(1, ch);

			while (!isspace(postfix[i+1]))
			{
				number.append(1, postfix[i+1]);
				i++;
			}

			NumberStack.push(sToDbl(number));
		}
		else if (isspace(postfix[i])) continue;
		else
		{
			long double c2 = NumberStack.top();
			NumberStack.pop();
			long double c1 = NumberStack.top();
			NumberStack.pop();

			//cout << c1 << " " << ch << endl;
			NumberStack.push(DoMath(c1,c2,ch));
		}
	}

	result = NumberStack.top();
}

double DoMath(double a, double b, char op)
{
	if (op == '+'){return (a + b);}
	else if (op == '-'){return (a - b);}
	else if (op == '*'){return (a * b);}
	else if (op == '/'){return (a / b);}
	else if (op == '^'){return (pow(a,b));}
	else return 0;
}