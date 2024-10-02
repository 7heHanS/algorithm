#include <iostream>

using namespace std;

// Function to find the Greatest Common Divisor (GCD) using the Euclidean algorithm
// gcd(a, b) = gcd(b, a % b) by Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the Least Common Multiple (LCM)
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int num1, num2;
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    int gcdResult = gcd(num1, num2);
    int lcmResult = lcm(num1, num2);

    cout << "GCD of " << num1 << " and " << num2 << " is: " << gcdResult << endl;
    cout << "LCM of " << num1 << " and " << num2 << " is: " << lcmResult << endl;

    return 0;
}