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
