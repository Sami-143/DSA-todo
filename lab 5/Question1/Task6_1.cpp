#include <iostream>
#include <cmath>
using namespace std;

int Gemoatric_Of_2(int n){
    if(n==1){
        return 0;
    }
    return n + Gemoatric_Of_2(n/2);
}
int main()
{
    int n =0;
    cout<<"Enter the value of n : "<<endl;
    cin >> n;
    cout<<"Your "<< n <<"th sum of the terms in the geometric series is : "<<Gemoatric_Of_2(n);
    return 0;
}