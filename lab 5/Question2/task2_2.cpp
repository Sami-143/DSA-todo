#include<iostream>
#include <cmath>
using namespace std;

string I2S(int n)
{
    if(n==0)
    {
        return "";
    }
    return I2S(n/2) + ((n%2 == 0)? "0":"1");
}
int main()
{
    int n = 0;
    cout<<"Enter the number : ";
    cin>>n;

    cout<< "The Answer is "<< I2S(n);
}