#include <iostream>
using namespace std;

// Function to compute A/B and A%B recursively
void divideAndMod(int A, int B, int &quotient, int &remainder) {
    if (B == 0) {
        cout << "Division by zero is undefined." << endl;
        return;
    }

    if (A < B) {
        quotient = 0;
        remainder = A;
        return;
    }

    // Find the largest power of 2, 2^k, such that B * 2^k <= A
    int k = 0;
    while ((B << k) <= A) {
        k++;
    }

    k--; // Adjust k to the largest power of 2 less than or equal to B

    // Calculate B * 2^k
    int B_times_2k = B << k;

    // Recursively compute quotient and remainder
    int tempQuotient, tempRemainder;
    divideAndMod(A - B_times_2k, B, tempQuotient, tempRemainder);

    // Update quotient and remainder based on the result of the recursive call
    quotient = (tempQuotient << k) + (A >= B_times_2k);
    remainder = tempRemainder + (A >= B_times_2k) * B;

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
