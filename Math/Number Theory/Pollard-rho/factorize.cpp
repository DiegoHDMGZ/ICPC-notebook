#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Fast factorization in O(n^(1/3))
//Include pollard-rho and miller-rabin functions

const Long MX = 2e6; //MX = MX_VAL^(1/3)
bool isPrimeSieve[MX];
vector<Long> primes;

void sieve(){ //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrimeSieve, isPrimeSieve + MX , true);
	isPrimeSieve[0] = isPrimeSieve[1] = false;
	for(Long i = 2; i < MX; i++){
		if(isPrimeSieve[i]) {
			primes.push_back(i);
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++){
			isPrimeSieve[i * primes[j]] = false;
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

vector<pair<Long, Long>> factorize(Long n) { 
	//O(n^(1/3) + |miller| + |rho|)
	if (n == 1) return {};
	vector<pair<Long, Long>> factors;
	for (Long f : primes) {
		Long e = 0;
		while (n % f == 0) {
			n /= f;
			e++;
		}
		if (e > 0) {
			factors.push_back({f, e});
		}
	}
	if (n == 1) return factors;
	
	if (isPrime(n)) { //from miller-rabin
		factors.push_back({n, 1});
	} else {
		Long sq = sqrt(n) + .00001;
		if (sq * sq == n) {
			factors.push_back({sq, 2});
		} else {
			Long a = getFactor(n); //from pollard-rho
			factors.push_back({a, 1});
			factors.push_back({n / a, 1});
		}
	}
	return factors;
}
