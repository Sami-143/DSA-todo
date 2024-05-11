#include <iostream>
#include <vector>
using namespace std;

int fast_triSum(vector<int> &Ts, int n) {
    if (Ts[n] != -1) {
        return Ts[n];
    }
    return fast_triSum(Ts, n - 1) + fast_triSum(Ts, n - 2) + fast_triSum(Ts, n - 3);
}

int mem_triSum(int n) {
    vector<int> Ts(n + 1, -1); // Initialize with -1
    Ts[0] = 1;
    Ts[1] = 2;
    Ts[2] = 3;

    return fast_triSum(Ts, n);
}

int main() {
    int n;
    cout << "Enter the value of n for TriSum: ";
    cin >> n;

    int result = mem_triSum(n);

    cout << "TriSum(" << n << ") = " << result << endl;

    return 0;
}
