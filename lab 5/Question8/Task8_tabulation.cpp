#include <iostream>
#include <vector>
using namespace std;

int bottom_up_triSum(int n) {
    if (n < 3) {
        return n + 1; // TriSum(0) = 1, TriSum(1) = 2, TriSum(2) = 3
    }
    vector<int> triSum(n + 1);
    triSum[0] = 1;
    triSum[1] = 2;
    triSum[2] = 3;

    for (int i = 3; i <= n; i++) {
        triSum[i] = triSum[i - 1] + triSum[i - 2] + triSum[i - 3];
    }

    return triSum[n];
}

int main() {
    int n;
    cout << "Enter the value of n for TriSum: ";
    cin >> n;
    int result = bottom_up_triSum(n);
    cout << "TriSum(" << n << ") = " << result << endl;
    return 0;
}
