#include<iostream>
#include <cmath>
using namespace std;

int D2B(int n){
    if(n == 0)
    {
        return 0;
    }

    return n%2 + D2B(n/2)*10;
}

int main()
{
    int n = 0;
    cout<<"Enter the number : ";
    cin>>n;

    cout<< "The Answer is "<< D2B(n);
}