#include <iostream>
#include <vector>
using namespace std;

int bottom_up_fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    vector<int> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main()
{
    int n;
    cout << "Enter the value of n for Fibonacci: ";
    cin >> n;
    int result = bottom_up_fib(n);
    cout << "Fibonacci(" << n << ") = " << result << endl;
    return 0;
}
