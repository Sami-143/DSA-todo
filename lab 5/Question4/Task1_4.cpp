#include <iostream>
using namespace std;

int modular_power(int x, int y, int m) {
    if (y == 0) {
        return 1;
    } else if (y % 2 == 0) {
        // If y is even, use the property (x^2)^y/2 = x^y
        int temp = modular_power(x, y / 2, m);
        return (temp * temp) % m;
    } else {
        // If y is odd, use the property x^y = x * x^(y-1)
        int temp = modular_power(x, y - 1, m);
        return (x * temp) % m;
    }
}

int main() {
    int x = 3;
    int y = 4;
    int m = 5;
    int result = modular_power(x, y, m);
    cout << result << endl;  // Output should be 1 (since 3^4 % 5 = 1)
    return 0;
}
