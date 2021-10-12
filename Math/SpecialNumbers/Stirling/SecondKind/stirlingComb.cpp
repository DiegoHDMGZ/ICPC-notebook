#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//count the number of ways of partitioning n distinct objects into k non-empty sets.
const Long MX = 1e5;
const Long MOD = 1e9 + 7;

Long mult(Long a, Long b) {
	return (a * b ) % MOD;
}

Long add(Long a, Long b) {
	return (a + b) % MOD;
}

Long sub(Long a, Long b) {
	return (a - b + MOD) % MOD;
}

Long fastPow(Long a, Long b) { //O(logb)
	Long ans = 1;
	while (b > 0) {
		if (b & 1 == 1) { 
			ans = mult(ans , a);
		}
		a = mult(a , a);
		b >>= 1; 
	}
	return ans;
}

Long modInverse(Long a) { //O(log mod) , mod prime , (a , mod) coprimes
	return fastPow(a, MOD - 2);
}

Long fact[MX];
Long inv[MX];

Long comb(Long n, Long k) {
	return mult(mult(fact[n], inv[k]) , inv[n - k]); 
}

Long stirling(Long n, Long k) { //O(k log n)
	Long ans = 0;
	for (Long i = 0; i <= k; i++) {
		if ((i & 1) == 0) {
			ans = add(ans , mult(fastPow(k - i, n), comb(k, i)));
		} else {
			ans = sub(ans , mult(fastPow(k - i, n), comb(k, i)));
		}
	}
	return mult(ans, inv[k]);
}

void precalc() {
	fact[0] = inv[0] = 1;
	for (Long i = 1; i < MX; i++) {
		fact[i] = mult(i, fact[i - 1]);
		inv[i] = modInverse(fact[i]);
	}
}

int main() {
	return 0;
}
