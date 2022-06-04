#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const int MX = 2e7;
bool isPrime[MX];
vector<int> primes;

void sieve() { // O(MX log log MX)
    fill(isPrime, isPrime + MX, true);
    isPrime[0] = isPrime[1] = false;
    for (Long i = 2; i < MX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (Long j = i * i; j < MX; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
