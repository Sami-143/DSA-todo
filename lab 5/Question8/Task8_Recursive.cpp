#include <iostream>
using namespace std;

int triSumRecursive(int n) {
    if (n == 0 || n == 1 || n == 2) {
        return n+1;
    } 
    else {
        return triSumRecursive(n - 1) + triSumRecursive(n - 2) + triSumRecursive(n - 3);
    }
}

int main() {
    int n;
    cout << "Enter the term you want in the TriSum sequence: ";
    cin >> n;
    int result = triSumRecursive(n);
    cout << "TriSum(" << n << ") = " << result << endl;
    return 0;
}
