#include<iostream>
#include<vector>
using namespace std;

int fast_fib(vector<int> &Fs,int n)
{
    if(Fs[n] != -1)
    {
        return Fs[n];
    }
    return fast_fib(Fs,n-1) + fast_fib(Fs,n-2);
}

int mem_fib(int n)
{
    vector<int> Fs(n+1,{-1});
    Fs[0] = 0;
    Fs[1] = 1;

    return fast_fib(Fs,n);

}

int main()
{
    int n;
    cout << "Enter the value of n for Fibonacci: ";
    cin >> n;

    int result = mem_fib(n);

    cout << "Fibonacci(" << n << ") = " << result << endl;

    return 0;
}