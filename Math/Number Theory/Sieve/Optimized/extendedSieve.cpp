#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 2e7;
bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

void sieve() { //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MX , true);
	isPrime[1] = false;
	for (Long i = 2; i  < MX; i++) {
		if (isPrime[i]) {
			primes.push_back(i);
			fact[i] = i;
		}
		for (Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++) {
			isPrime[i * primes[j]] = false;
			fact[i * primes[j]] = primes[j];
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
}

vector<pair<Long,Long>> factorize(Long x) { //O(log x)
	vector<pair<Long,Long>> factors;
	while (x > 1) {
		Long f = fact[x];
		Long exp = 0;
		while (x % f == 0) {
			x /= f;
			exp++;
		}
		factors.push_back({f ,exp});
	}
	//sorted factors
	return factors;
}

vector<Long> getDivisors(Long x) {
	vector<Long> ans = {1};
	while (x > 1) {
		Long f = fact[x];
		Long num = 1;
		Long sz = ans.size();
		while (x % f == 0) {
			num *= f;
			x /= f;
			for (Long i = 0; i < sz; i++) {
				ans.push_back(num * ans[i]);
			}
		}
	}
	//sort(ans.begin(), ans.end());
	return ans;
}

int main() {
	sieve();
	return 0;
}
