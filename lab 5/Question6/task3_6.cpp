#include <iostream>
#include <vector>
using namespace std;
// Function to compute A/B and A%B using memoization
void divideAndMod(int A, int B, int &quotient, int &remainder) {
    if (B == 0) {
        cout << "Division by zero is undefined." << endl;
        return;
    }

    vector<int> dp(B, 0); // Initialize a dynamic programming table with size B
    int temp = B;
    int i = 1;

    // Build the dynamic programming table
    while (temp <= A) {
        temp <<= 1; // Multiply temp by 2 (left shift) to find the next power of 2
        i++;
    }

    temp >>= 1; // Adjust temp back to the largest power of 2 less than or equal to B
    i--;

    while (i >= 0) {
        if (A >= temp) {
            A -= temp; // Subtract the largest power of 2 less than or equal to B from A
            dp[i] = 1; // Set the corresponding bit in the quotient
        }

        temp >>= 1; // Divide temp by 2 (right shift) to consider the next smaller power of 2
        i--;
    }

    // Calculate the quotient and remainder based on the dynamic programming table
    quotient = 0;
    remainder = A;

    for (int j = B - 1; j >= 0; j--) {
        quotient <<= 1; // Left shift quotient by 1 bit
        quotient += dp[j]; // Add the bit from the dynamic programming table
    }
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
