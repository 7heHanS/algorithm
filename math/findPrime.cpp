#include <iostream>
#include <vector>

using namespace std;

// Sieve of Eratosthenes function to find all prime numbers up to a given limit
vector<int> sieveOfEratosthenes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false; // 0과 1은 소수가 아님

    for (int i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int limit;
    cout << "Enter the limit: ";
    cin >> limit;

    vector<int> primes = sieveOfEratosthenes(limit);

    cout << "Prime numbers up to " << limit << " are:" << endl;
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}