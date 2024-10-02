#include <iostream>
#include <vector>

using namespace std;

// Function to perform modular exponentiation
// It returns (base^exp) % mod
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod; // Update base if it is more than or equal to mod

    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        // exp must be even now
        exp = exp >> 1; // exp = exp / 2
        base = (base * base) % mod; // Change base to base^2
    }
    return result;
}

// Function to compute nCk % mod using Fermat's Little Theorem
long long mod_binomial_coefficient(long long n, long long k, long long mod) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    vector<long long> fact(n + 1, 1);
    for (long long i = 2; i <= n; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }

    long long inv_k = mod_pow(fact[k], mod - 2, mod);
    long long inv_n_k = mod_pow(fact[n - k], mod - 2, mod);

    long long result = fact[n] * inv_k % mod * inv_n_k % mod;
    return result;
}

// Function to compute nCk % mod using Lucas's Theorem
long long lucas_theorem(long long n, long long k, long long mod) {
    if (k == 0) return 1;

    long long ni = n % mod;
    long long ki = k % mod;

    long long result = lucas_theorem(n / mod, k / mod, mod) * mod_binomial_coefficient(ni, ki, mod) % mod;
    return result;
}

int main() {
    // Example usage of mod_pow
    // base = 2, exp = 10, mod = 1000
    // 2^10 % 1000 = 24
    long long base, exp, mod;
    cout << "Enter base, exponent and modulus: ";
    cin >> base >> exp >> mod;

    long long result = mod_pow(base, exp, mod);
    cout << base << "^" << exp << " % " << mod << " is: " << result << endl;

    // Example usage of mod_binomial_coefficient
    // n is small, mod is big
    // n = 5, k = 2, mod = 13
    // C(5, 2) % 13 = 10
    long long n, k;
    cout << "Enter n, k and modulus to compute nCk % mod: ";
    cin >> n >> k >> mod;

    long long binom_result = mod_binomial_coefficient(n, k, mod);
    cout << "C(" << n << ", " << k << ") % " << mod << " is: " << binom_result << endl;

    // Example usage of lucas_theorem
    // n is big, mod is small
    // n = 1000, k = 300, mod = 13
    // C(1000, 300) % 13 using Lucas's Theorem is: 10
    cout << "Enter n, k and prime modulus to compute nCk % mod using Lucas's Theorem: ";
    cin >> n >> k >> mod;

    long long lucas_result = lucas_theorem(n, k, mod);
    cout << "C(" << n << ", " << k << ") % " << mod << " using Lucas's Theorem is: " << lucas_result << endl;

    return 0;
}