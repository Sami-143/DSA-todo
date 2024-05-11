#include <iostream>
using namespace std;
// Function to compute A/B and A%B recursively
void divideAndMod(int A, int B, int &quotient, int &remainder) {
    if (B == 0) {
        cout << "Division by zero is undefined." << endl;
        return;
    }

    if (A < B) {
        // Base case: A is less than B
        quotient = 0;
        remainder = A;
        return;
    }

    // Recursive case: Subtract B from A and call the function recursively
    int tempQuotient, tempRemainder;
    divideAndMod(A - B, B, tempQuotient, tempRemainder);

    // Update quotient and remainder
    quotient = tempQuotient + 1;
    remainder = tempRemainder;
}

int main() {
    int A, B;

    // Input values of A and B
    cout << "Enter A: ";
    cin >> A;
    cout << "Enter B: ";
    cin >> B;

    int quotient, remainder;

    divideAndMod(A, B, quotient, remainder);

    // At this point, quotient contains A / B and remainder contains A % B
    cout << "A / B = " << quotient << endl;
    cout << "A % B = " << remainder << endl;

    return 0;
}
