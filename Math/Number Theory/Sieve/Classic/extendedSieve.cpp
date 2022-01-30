#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
const Long MX = 2e7;
bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

void sieve() { //O(MX log log MX)
	fill(isPrime, isPrime + MX , true);
	isPrime[0] = isPrime[1] = false;
	for (Long i = 2; i  < MX; i++) {
		if (isPrime[i]) {
			primes.push_back(i);
			fact[i] = i;
			for (Long j = i * i; j < MX; j += i) {
				isPrime[j] = false;
				fact[j] = i;
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
	//not necessarily sorted
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
