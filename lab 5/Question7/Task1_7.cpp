#include <iostream>
#include <cmath>
using namespace std;

#include <iostream>

int fibonacciIterative(int n) {
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int fib(int n){
    if(n==0 || n==1){
        return n;
    }

    return fib(n-1) + fib(n-2);
}
int main()
{
    int n = 0;
    cout<<"Enter the term you want in the fabonocii series : "<<endl;
    cin >> n;
    cout<<"Your "<< n <<"th term in the series is : "<<fib(n);
    return 0;

    int N = 10; 
    cout << "Fibonacci(" << N << ") = " << fibonacciIterative(N) << endl;
    return 0;
}