#include <iostream>
#include <cmath>
using namespace std;

int Geometric_Series_Sum(int n) {
    if (n == 0) {
        return 1;  
    }

    return pow(2, n) + Geometric_Series_Sum(n - 1);
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative integer for N." << endl;
    } else {
        int result = Geometric_Series_Sum(n);
        cout << "The sum of the geometric series 1 + 2 + 4 + ... + 2^" << n << " is: " << result << endl;
    }

    return 0;
}
