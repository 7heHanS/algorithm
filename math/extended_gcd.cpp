#include <iostream>
#include <vector>

using namespace std;

// Function to implement the Extended Euclidean Algorithm
// It returns the GCD of a and b, and updates x and y such that ax + by = GCD(a, b)
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Function to find the modular inverse of a under modulo m
// It returns the modular inverse if it exists, otherwise returns -1
int modularInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);
    if (gcd != 1) {
        return -1; // Modular inverse doesn't exist if a and m are not coprime
    } else {
        // Make x positive
        return (x % m + m) % m;
    }
}

// Function to solve the system of congruences using the Chinese Remainder Theorem
// It returns the solution x such that x ≡ a[i] (mod m[i]) for all i
int chineseRemainderTheorem(const vector<int>& a, const vector<int>& m) {
    int prod = 1;
    for (int mod : m) {
        prod *= mod;
    }

    int result = 0;
    for (int i = 0; i < a.size(); i++) {
        int pp = prod / m[i];
        result += a[i] * modularInverse(pp, m[i]) * pp;
        result %= prod;
    }

    return (result + prod) % prod;
}

int main() {
    // Example usage of extendedGCD
    // GCD of 56 and 98 is: 14
    // Coefficients x and y are: -1 and 1
    // Verification: 56*-1 + 98*1 = 14
    int a, b;    
    cout << "Enter two integers: ";
    cin >> a >> b;

    int x, y;
    int gcd = extendedGCD(a, b, x, y);

    cout << "GCD of " << a << " and " << b << " is: " << gcd << endl;
    cout << "Coefficients x and y are: " << x << " and " << y << endl;
    cout << "Verification: " << a << "*" << x << " + " << b << "*" << y << " = " << gcd << endl;

    // Example usage of modularInverse    
    // Modular inverse of 3 under modulus 11 is: 4
    // Verification: 3*4 % 11 = 1
    int num, mod;    
    cout << "Enter a number and modulus to find modular inverse: ";
    cin >> num >> mod;
    int inverse = modularInverse(num, mod);
    if (inverse == -1) {
        cout << "Modular inverse doesn't exist." << endl;
    } else {
        cout << "Modular inverse of " << num << " under modulus " << mod << " is: " << inverse << endl;
    }

    // Example usage of Chinese Remainder Theorem
    // Enter the number of congruences: 3
    // Enter the remainders and moduli:
    // 2 3
    // 3 5
    // 2 7
    // The solution to the system of congruences is: 23
    // Verification: 23 % 3 = 2, 23 % 5 = 3, 23 % 7 = 2

    int n;
    cout << "Enter the number of congruences: ";
    cin >> n;
    vector<int> remainders(n), moduli(n);
    cout << "Enter the remainders and moduli:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> remainders[i] >> moduli[i];
    }
    int crtResult = chineseRemainderTheorem(remainders, moduli);
    cout << "The solution to the system of congruences is: " << crtResult << endl;

    return 0;
}