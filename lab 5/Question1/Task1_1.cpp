#include<iostream>
#include <cmath>
using namespace std;

int Sum_of_Nth_Series(int n){
    if(n == 0)
    {
        return 0;
    }

    return n + Sum_of_Nth_Series(n - 1 );
}

int main()
{
    int n = 0;
    cin>>n;

    cout<< "The Sum of "<< n << " Terms is : "<< Sum_of_Nth_Series(n);
}