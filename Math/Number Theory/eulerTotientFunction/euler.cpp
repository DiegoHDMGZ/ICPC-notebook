#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e7;
bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

void extSieve(){ //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MX , true);
	isPrime[1] = false;
	for(Long i = 2; i  < MX; i++){
		if(isPrime[i]) {
			primes.push_back(i);
			fact[i] = i;
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++){
			isPrime[i * primes[j]] = false;
			fact[i * primes[j]] = primes[j];
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

Long euler(Long n) { //O(log n)
	Long ans = n;
	while(n > 1){
		Long f = fact[n];
		while(n % f == 0){
			n /= f;
		}
		ans -= ans / f;
	}
	return ans;
}

/*Long euler(Long n) { //O( sqrt(n))
	Long ans = n;
	Long i = 2;
	while(i * i <= n) {
		if(n % i == 0) {
			while(n % i == 0) {
				n /= i;
			}
			ans -= ans / i;
		}
		i++;
	}
	if(n > 1) {
		ans -= ans / n;
	}
	return ans;
}*/

int main() {
	extSieve();
	while(true) {
		Long x;
		cin >> x;
		debug(euler(x));
	}
	return 0;
}

