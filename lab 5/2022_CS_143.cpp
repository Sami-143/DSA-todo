#include<iostream>
#include <cmath>
using namespace std;

int Sum_of_Nth_Series(int n){
    if(n == 0)
    {
        return 0;
    }

    return n + Sum_of_Nth_Series(n - 1 );
}

int main()
{
    int n = 0;
    cin>>n;

    cout<< "The Sum of "<< n << " Terms is : "<< Sum_of_Nth_Series(n);
}


#include<iostream>
#include <cmath>
using namespace std;

int Sum_of_Odd_Series(int n){
    if(n == 0)
    {
        return 0;
    }

    return (2* n - 1) + Sum_of_Odd_Series( n - 1 );
}

int main()
{
    int n = 0;
    cout<<"Enter the Odd number of the terms : "; 
    cin>>n;

    cout<< "The Sum of "<< n << " Terms is : "<< Sum_of_Odd_Series(n);
}


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


#include <iostream>
#include <cmath>
using namespace std;

int Geometric_Series_Sum(int n) {
    if (n == 0) {
        return 1;  
    }

    return pow(3, n) + Geometric_Series_Sum(n - 1);
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative integer for N." << endl;
    } else {
        int result = Geometric_Series_Sum(n);
        cout << "The sum of the geometric series 1 + 3 + 9 + 27 + 81 +...+ 3^ " << n << " is: " << result << endl;
    }

    return 0;
}


#include <iostream>
#include <cmath>
using namespace std;

int Gemoatric_Of_3(int n){
    if(n==1){
        return 0;
    }
    return n + Gemoatric_Of_3(n/3);
}
int main()
{
    int n = 0;
    cout<<"Enter the value of n : "<<endl;
    cin >> n;
    cout<<"Your "<< n <<"th sum of the terms in the geometric series is : "<<Gemoatric_Of_3(n);
    return 0;
}


#include <iostream>
#include <cmath>
using namespace std;

int Gemoatric_Of_2(int n){
    if(n==1){
        return 0;
    }
    return n + Gemoatric_Of_2(n/2);
}
int main()
{
    int n =0;
    cout<<"Enter the value of n : "<<endl;
    cin >> n;
    cout<<"Your "<< n <<"th sum of the terms in the geometric series is : "<<Gemoatric_Of_2(n);
    return 0;
}



#include<iostream>
#include <cmath>
using namespace std;

int D2B(int n){
    if(n == 0)
    {
        return 0;
    }

    return n%2 + D2B(n/2)*10;
}

int main()
{
    int n = 0;
    cout<<"Enter the number : ";
    cin>>n;

    cout<< "The Answer is "<< D2B(n);
}



#include<iostream>
#include <cmath>
using namespace std;

string I2S(int n)
{
    if(n==0)
    {
        return "";
    }
    return I2S(n/2) + ((n%2 == 0)? "0":"1");
}
int main()
{
    int n = 0;
    cout<<"Enter the number : ";
    cin>>n;

    cout<< "The Answer is "<< I2S(n);
}


#include<iostream>
using namespace std;

int GCD(int A, int B) {
    if (B == 0) {
        return A;
    }

    return GCD(B, A % B);
}

int main() {
    int A = 0;
    cout<<"ENTER THE VALUE OF A : ";
    cin>>A;
    int B = 0;
    cout<<"ENTER THE VALUE OF B : ";
    cin>>B;
    cout << "The GCD of " << A << " and " << B << " is: " << GCD(A, B) << endl;
    return 0;
}


#include <iostream>
using namespace std;

int first_Occurance(int arr[], int n, int i, int key)
{

    if (i == n)
    {
        return -1;
    }
    if(arr[i] == key)
    {
        return i;
    }

    return first_Occurance(arr,n,i+1,key);
}


int main()
{
    int arr[] = {4,2,5,7,2,4,2};
    cout<<first_Occurance(arr,7,0,2);
    return 0;
}


#include <iostream>
using namespace std;

int last_Occurance(int arr[], int n, int i, int key)
{
    if (i == n)
    {
        return -1;
    }

    int rest_Array = last_Occurance(arr, n, i + 1, key);

    if (rest_Array != -1)
    {
        return rest_Array;
    }

    if (arr[i] == key)
    {
        return i;
    }

    return -1;
}

int main()
{
    int arr[] = {4, 2, 5, 7, 2, 4, 2};
    cout << last_Occurance(arr, 7, 0, 2);
    return 0;
}



#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

int binary_search_recursive(vector<int>& arr, int s, int e, int key) {
    if (s > e) {
        return -1;  
    }

    int mid = (s + e) / 2;

    if (arr[mid] == key) {
        return mid;  
    } 
    else if (arr[mid] < key) {
        return binary_search_recursive(arr, mid + 1, e, key);
    } 
    else {
        return binary_search_recursive(arr, s, mid - 1, key);
    }
}

int main() {

    vector<int> large_data;
    for (int i = 0; i < 1000; ++i) {
        large_data.push_back(rand() % 10000);
    }
    sort(large_data.begin(), large_data.end());

    int key = large_data[rand() % large_data.size()]; 

    int index = binary_search_recursive(large_data, 0, large_data.size() - 1, key);

    if (index != -1) {
        cout << "Element " << key << " found at index " << index << endl;
    }
    else {
        cout << "Element " << key << " not found in the dataset" << endl;
    }

    return 0;
}


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

string MULT(string A, string B) {
    string result = "0";

    int n = A.length();
    int m = B.length();

    for (int j = m - 1; j >= 0; j--) {
        if (B[j] == '1') {
            result = ADD(result, A + string(m - 1 - j, '0'));
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


#include <iostream>
#include <cmath>
using namespace std;

#include <iostream>

int fibonacciIterative(int n) {
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int fib(int n){
    if(n==0 || n==1){
        return n;
    }

    return fib(n-1) + fib(n-2);
}
int main()
{
    int n = 0;
    cout<<"Enter the term you want in the fabonocii series : "<<endl;
    cin >> n;
    cout<<"Your "<< n <<"th term in the series is : "<<fib(n);
    return 0;

    int N = 10; 
    cout << "Fibonacci(" << N << ") = " << fibonacciIterative(N) << endl;
    return 0;
}



#include<iostream>
#include<vector>
using namespace std;

int fast_fib(vector<int> &Fs,int n)
{
    if(Fs[n] != -1)
    {
        return Fs[n];
    }
    return fast_fib(Fs,n-1) + fast_fib(Fs,n-2);
}

int mem_fib(int n)
{
    vector<int> Fs(n+1,{-1});
    Fs[0] = 0;
    Fs[1] = 1;

    return fast_fib(Fs,n);

}

int main()
{
    int n;
    cout << "Enter the value of n for Fibonacci: ";
    cin >> n;

    int result = mem_fib(n);

    cout << "Fibonacci(" << n << ") = " << result << endl;

    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

int bottom_up_fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    vector<int> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main()
{
    int n;
    cout << "Enter the value of n for Fibonacci: ";
    cin >> n;
    int result = bottom_up_fib(n);
    cout << "Fibonacci(" << n << ") = " << result << endl;
    return 0;
}



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


#include <iostream>
#include <vector>
using namespace std;

void generateSubarrays(const vector<int>& arr, vector<int>& current, vector<vector<int>>& result, int index = 0) {
    if (index == arr.size()) {
        result.push_back(current);
        return;
    }

    generateSubarrays(arr, current, result, index + 1); // Exclude the current element
    current.push_back(arr[index]);
    generateSubarrays(arr, current, result, index + 1); // Include the current element
    current.pop_back(); // Backtrack
}

vector<vector<int>> generateAllSubarrays(const vector<int>& arr) {
    vector<vector<int>> result;
    vector<int> current;
    generateSubarrays(arr, current, result);
    return result;
}

int main() {
    vector<int> input1 = {1, 2, 3};
    vector<int> input2 = {1, 2};

    vector<vector<int>> output1 = generateAllSubarrays(input1);
    vector<vector<int>> output2 = generateAllSubarrays(input2);

    // Print the results
    for (const auto& subarray : output1) {
        for (int num : subarray) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (const auto& subarray : output2) {
        for (int num : subarray) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}

