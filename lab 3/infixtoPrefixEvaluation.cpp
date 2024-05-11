#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

int Operator_precedence(char c)
{
	if (c == '^')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	return -1;
}

string infixToPrefixEvaluation(string str)
{
	reverse(str.begin(), str.end());
	stack<char> stack;
	string resultant_string;

	for (int idx = 0; idx < str.length(); idx++)
	{
		if ((str[idx] >= 'a' && str[idx] <= 'z') || (str[idx] >= 'A' && str[idx] <= 'Z'))
        {
            resultant_string += str[idx];
        }
		else if (str[idx] == ')')
		{
			stack.push(str[idx]);
		}
		else if (str[idx] == '(')
		{
			while (!stack.empty() && stack.top() != ')')
			{
				resultant_string += stack.top();
				stack.pop();
			}
			if (!stack.empty())
			{
				stack.pop();
			}
		}
		else {
			while (!stack.empty() && Operator_precedence(stack.top()) >= Operator_precedence(str[idx]))
			{
				resultant_string += stack.top();
				stack.pop();
			}
			stack.push(str[idx]);
		}
	}

	while (!stack.empty())
	{
		resultant_string += stack.top();
		stack.pop();
	}

	reverse(resultant_string.begin(), resultant_string.end());
	return resultant_string;
}

int main()
{
	cout << infixToPrefixEvaluation("(a-b/c)*(a/k-l)");
	return 0;
}
