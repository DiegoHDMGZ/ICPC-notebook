#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MX = 2e7;
bool isPrime[MX];
vector<Long> primes;

void sieve(){ //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MX , true);
	isPrime[0] = isPrime[1] = false;
	for (Long i = 2; i < MX; i++) {
		if (isPrime[i]) primes.push_back(i);
		for (Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++) {
			isPrime[i * primes[j]] = false;
			if (i % primes[j] == 0) break;
		}
	}
}
