#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Usage: 
//call sieve()
//call segmentedSieve(L , R)
//For each query X, use isPrimeRange[X - L]

const Long MX = 2e6;
bool isPrime[MX];
vector<Long> primes;

void sieve(){ //O(MX)
	//generate all the primes up to sqrt(R) for the range [L, R]
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MX , true);
	isPrime[0] = false;
	isPrime[1] = false;
	for(Long i = 2; i < MX; i++){
		if(isPrime[i]) {
			primes.push_back(i);
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++){
			isPrime[i * primes[j]] = false;
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

bool isPrimeRange[MX];

void segmentedSieve(Long l, Long r) { //O( (r - l) * log log (r - l) )
	fill(isPrimeRange, isPrimeRange + MX , true);
	for(Long i = 0; i < primes.size(); i++) {
		if(primes[i] * primes[i] > r) {
			break;
		}
		Long k = max(l / primes[i] , 2LL);
		k = max(k , primes[i] );
		for(Long j = k; ; j++) {
			if(primes[i] * j < l) {
				continue;
			}
			if(primes[i] * j > r ) {
				break;
			}
			isPrimeRange[primes[i] * j - l] = false;
		}
	}
	if(l == 1) {
		isPrimeRange[0] = false;
	}
}