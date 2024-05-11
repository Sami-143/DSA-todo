#include <iostream>
#include <string>
#include <vector>
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

string MULT(string A, string B) {
    int n = A.length();
    int m = B.length();

    vector<string> partialProducts(m, "");
    string result = "0";

    for (int j = m - 1; j >= 0; j--) {
        if (B[j] == '1') {
            partialProducts[j] = A + string(m - 1 - j, '0');
            result = ADD(result, partialProducts[j]);
        }
    }

    return result;
}

int main() {
    string A = "101";
    string B = "110";

    string result = MULT(A, B);
    cout << "Multiplication result: " << result << endl;

    return 0;
}
