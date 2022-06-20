#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long MX = 1e5;

bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

void extSieve() { // O(MX)
    // x = i * p. p is the smallest prime factor
    fill(isPrime, isPrime + MX, true);
    isPrime[1] = false;
    for (Long i = 2; i < MX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            fact[i] = i;
        }
        for (Long j = 0; j < primes.size() && i * primes[j] < MX; j++) {
            isPrime[i * primes[j]] = false;
            fact[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

Long mu[MX];
// mu[x] = 0 if x is not square free (divisible by a square factor)
// mu[x] = 1 if x is square free with even number of prime factors
// mu[x] = -1 if x is square free with odd number of prime factors

void mobius() { // O(MX)
    mu[1] = 1;
    for (Long i = 2; i < MX; i++) {
        if (fact[i] == i) mu[i] = -1;
        else {
            Long nx = i / fact[i];
            if (nx % fact[i] == 0) mu[i] = 0;
            else mu[i] = -mu[nx];
        }
    }
}