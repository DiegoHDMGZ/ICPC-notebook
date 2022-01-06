#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//Lucas's Theorem :
//For non-negative integers m and n, and a prime integer p
//C(m , n) = Prod (mi, ni) (mod p)
//where mi , ni are the p-expansions of m and n respectively.

const Long MX = 100;
Long fact[MX];
Long inv[MX];

Long mult(Long a, Long b, Long mod) {
	return (a * b) % mod;
}

Long fastPow(Long a, Long b , Long mod) { //O(log b)
	Long ans = 1;
	while (b > 0) {
		if(b & 1) ans = mult(ans ,a , mod);
		a = mult(a , a  , mod);
		b >>= 1;
	}
	return ans;
}

Long invert(Long a, Long m) { //O(log m) , m prime , a , m coprimes
	return fastPow(a, m - 2, m);
}

void init(Long mod) { //O(mod)
	fact[0] = 1;
	inv[0] = 1;
	for (int i = 1; i < mod; i++) {
		fact[i] = mult(fact[i-1], i, mod);
	}
	inv[mod - 1] = invert(fact[mod - 1], mod);
	for (int i = mod - 2; i >= 0; i--) {
		inv[i] = mult(inv[i + 1], i + 1, mod);
	}
}

Long comb(Long N, Long M, Long mod) { //O(1)
	if(N < M) return 0;
	return mult(mult(fact[N], inv[M], mod), inv[N - M], mod); 
}

//call init(MOD) before
Long combLucas(Long N, Long M, Long mod) { //O(log N + log M)
	//mod is prime
	Long ans = 1;
	while (N > 0 || M > 0) {
		ans = mult(ans, comb(N % mod, M % mod , mod), mod);
		N /= mod;
		M /= mod; 
	}
	return ans;
}