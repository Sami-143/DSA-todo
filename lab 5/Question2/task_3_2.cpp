#include<iostream>
using namespace std;

int GCD(int A, int B) {
    if (B == 0) {
        return A;
    }

    return GCD(B, A % B);
}

int main() {
    int A = 0;
    cout<<"ENTER THE VALUE OF A : ";
    cin>>A;
    int B = 0;
    cout<<"ENTER THE VALUE OF B : ";
    cin>>B;
    cout << "The GCD of " << A << " and " << B << " is: " << GCD(A, B) << endl;
    return 0;
}