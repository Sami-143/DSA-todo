#include<iostream>
#include <cmath>
using namespace std;

int Sum_of_Odd_Series(int n){
    if(n == 0)
    {
        return 0;
    }

    return (2* n - 1) + Sum_of_Odd_Series( n - 1 );
}

int main()
{
    int n = 0;
    cout<<"Enter the Odd number of the terms : "; 
    cin>>n;

    cout<< "The Sum of "<< n << " Terms is : "<< Sum_of_Odd_Series(n);
}