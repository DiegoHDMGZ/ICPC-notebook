#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 2e7;
bool isPrime[MAX];
vector<Long> primes;

void sieve(){ //O(MAX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MAX , true);
	isPrime[0] = isPrime[1] = false;
	for(Long i = 2; i  < MAX; i++){
		if(isPrime[i]) {
			primes.pb(i);
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MAX; j++){
			isPrime[i * primes[j]] = false;
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

int main() {
	sieve();
	return 0;
}


