#include <iostream>
#include <string>
using namespace std;

string ADD(string X, string Y) {
    string result = "";
    int carry = 0;

    int n = X.length();
    int m = Y.length();

    int i = n - 1;
    int j = m - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += X[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += Y[j] - '0';
            j--;
        }
        carry = sum / 2;
        result = to_string(sum % 2) + result;
    }

    return result;
}

string MULT(string X, string Y) {
    string result = "";

    int n = X.length();
    int m = Y.length();

    for (int j = m - 1; j >= 0; j--) {
        if (Y[j] == '1') {
            result = ADD(result, X + string(m - 1 - j, '0'));
        }
    }

    return result;
}

int main() {
    string X = "101";
    string Y = "110";

    string result = MULT(X, Y);
    cout << "Multiplication result: " << result << endl;

    return 0;
}
