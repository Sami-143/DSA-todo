/*---Task 1---*/
#include <iostream>
#include <stack>
#include <cmath> // Changed from math.h to cmath
using namespace std;

int postfix_Evaluation(string str)
{
    stack<int> stack;
    for (int i = 0; i < str.length(); i++) // Changed i++ to i++
    {
        if (str[i] >= '0' && str[i] <= '9') // Changed condition to check for digits
        {
            stack.push(str[i] - '0'); // Convert character to integer
        }
        else
        {
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            switch (str[i])
            {
            case '+':
                stack.push(operand1 + operand2);
                break;

            case '-':
                stack.push(operand1 - operand2);
                break;

            case '/':
                stack.push(operand1 / operand2);
                break;

            case '*':
                stack.push(operand1 * operand2);
                break;

            case '^':
                stack.push(pow(operand1, operand2)); // Fixed the order of operands for exponentiation
                break;
            }
        }
    }
    return stack.top();
}

int main()
{
    string expression = "23*5+"; // Example input expression
    int result = postfix_Evaluation(expression);
    cout << "Result: " << result << endl; // Output the result
    return 0;
}

// /*---Task 2---*/
// #include <iostream>
// #include <stack>
// #include <cmath>
// using namespace std;

// int prefix_Evaluation(string str)
// {
//     stack<int> stack;
//     for (int i = str.length() - 1; i >= 0; i--)
//     {
//         if (str[i] >= '0' && str[i] <= '9')
//         {
//             stack.push(str[i] - '0');
//         }
//         else
//         {
//             int operand1 = stack.top();
//             stack.pop();
//             int operand2 = stack.top();
//             stack.pop();

//             switch (str[i])
//             {
//             case '+':
//                 stack.push(operand1 + operand2);
//                 break;

//             case '-':
//                 stack.push(operand1 - operand2);
//                 break;

//             case '/':
//                 stack.push(operand1 / operand2);
//                 break;

//             case '*':
//                 stack.push(operand1 * operand2);
//                 break;

//             case '^':
//                 stack.push(pow(operand1, operand2));
//                 break;
//             }
//         }
//     }
//     return stack.top();
// }

// int main()
// {
//     string expression = "46+2/5*7+";
//     int result = prefix_Evaluation(expression);
//     cout << "Result: " << result << endl;
//     return 0;
// }

// /*---Task 3---*/
// #include<iostream>
// #include<stack>
// #include<algorithm>
// using namespace std;

// int Operator_precedence(char c)
// {
// 	if (c == '^')
// 	{
// 		return 3;
// 	}
// 	else if (c == '*' || c == '/')
// 	{
// 		return 2;
// 	}
// 	else if (c == '+' || c == '-')
// 	{
// 		return 1;
// 	}
// 	return -1;
// }

// string infixToPrefixEvaluation(string str)
// {
// 	reverse(str.begin(), str.end());
// 	stack<char> stack;
// 	string resultant_string;

// 	for (int idx = 0; idx < str.length(); idx++)
// 	{
// 		if ((str[idx] >= 'a' && str[idx] <= 'z') || (str[idx] >= 'A' && str[idx] <= 'Z'))
//         {
//             resultant_string += str[idx];
//         }
// 		else if (str[idx] == ')')
// 		{
// 			stack.push(str[idx]);
// 		}
// 		else if (str[idx] == '(')
// 		{
// 			while (!stack.empty() && stack.top() != ')')
// 			{
// 				resultant_string += stack.top();
// 				stack.pop();
// 			}
// 			if (!stack.empty())
// 			{
// 				stack.pop();
// 			}
// 		}
// 		else {
// 			while (!stack.empty() && Operator_precedence(stack.top()) >= Operator_precedence(str[idx]))
// 			{
// 				resultant_string += stack.top();
// 				stack.pop();
// 			}
// 			stack.push(str[idx]);
// 		}
// 	}

// 	while (!stack.empty())
// 	{
// 		resultant_string += stack.top();
// 		stack.pop();
// 	}

// 	reverse(resultant_string.begin(), resultant_string.end());
// 	return resultant_string;
// }

// int main()
// {
// 	cout << infixToPrefixEvaluation("(a-b/c)*(a/k-l)");
// 	return 0;
// }


// /*---Task 4---*/

// #include<iostream>
// #include<stack>
// using namespace std;

// int Operator_precedence(char c)
// {
//     if(c == '^')
//     {
//         return 3;
//     }
//     else if(c == '/' || c == '*')
//     {
//         return 3;
//     }
//     else if(c == '+' || c == '-')
//     {
//         return 3;
//     }
    
//     return -1;
// }

// string infixtoPostfixEvaluation(string str)
// {
//     string resultant_string = "";
//     stack <char> stack;

//     for(int idx = 0;idx<str.length();idx ++)
//     {
//         if((str[idx]  >= 'a' && str[idx] <= 'z') || (str[idx]  >= 'A' && str[idx] <= 'Z'))
//         {
//             resultant_string+= str[idx];
//         }
        
//         else if(str[idx] == '(')
//         {
//             stack.push(str[idx]);
//         }

//         else if (str[idx] == ')')
//         {
//             while(!stack.empty() && stack.top() != '(')
//             {
//                 resultant_string+=stack.top();
//                 stack.pop();
//             }
//             if(!stack.empty())
//             {
//                 stack.pop();
//             }
//         }

//         else
//         {
//             while(!stack.empty() && Operator_precedence(stack.top())>= Operator_precedence(str[idx]))
//             {
//                 resultant_string+=stack.top();
//                 stack.pop();
//             }
//             stack.push(str[idx]);
//         }
        
//     }

//     while(!stack.empty())
//     {
//         resultant_string+=stack.top();
//         stack.pop();
//     }  
//     return resultant_string;
// }

// int main()
// {

//     cout<<infixtoPostfixEvaluation("(a*b)*(a*c)/d")<<endl;
//     return 0;
// }