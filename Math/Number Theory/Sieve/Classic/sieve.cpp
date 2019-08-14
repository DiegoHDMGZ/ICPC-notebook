#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 2e7;
bool isPrime[MAX];
vector<Long> primes;

//pending system test

void sieve(){ //O(MAX log log MAX)
	fill(isPrime, isPrime + MAX , true);
	isPrime[0] = isPrime[1] = false;
	for(Long i = 2; i  < MAX; i++){
		if(isPrime[i]) {
			primes.pb(i);
			if(i * i < MAX){
				for(Long j = i * i; j < MAX; j += i){
					isPrime[j] = false;
				}
			}
		}
	}
}

int main() {
	sieve();
	return 0;
}


