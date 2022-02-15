#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

//Lucas's Theorem :
//For non-negative integers m and n, and a prime integer p
//C(m , n) = Prod (mi, ni) (mod p)
//where mi , ni are the p-expansions of m and n respectively.

Long MOD;

struct ModInt {
	Long val;
	ModInt(Long val = 0) {
		this->val = val;
	}
	ModInt operator +(const ModInt &other) const {
		if (val + other.val < MOD) return val + other.val;
		return val + other.val - MOD;
	}
	ModInt operator -(const ModInt &other) const {
		if (val - other.val >= 0) return val - other.val;
		return val - other.val + MOD;
	}
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
	ModInt operator *=(const ModInt &other) {
		*this = *this * other;
		return *this;
	}
	ModInt pow(Long b) const { //O(log b)
		ModInt ans = 1;
		ModInt a = val;
		while (b > 0) {
			if (b & 1) ans *= a;
			a *= a;
			b >>= 1;
		}
		return ans;
	}
	ModInt invert() const { //O(log mod) 
		//mod prime
		return pow(MOD - 2);
	}
	ModInt operator /(const ModInt &other) const {
		return *this * other.invert();
	}
	ModInt operator /=(const ModInt &other) {
		*this = *this / other;
		return *this;
	}
};

const int MX = 1e6;
ModInt fact[MX];
ModInt inv[MX];

void init(Long mod) { //O(mod)
	MOD = mod;
	fact[0] = 1;
	for (int i = 1; i < MOD; i++) fact[i] = fact[i - 1] * i;
	inv[MOD - 1] = fact[MOD - 1].invert();
	for (int i = MOD - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1);
}

ModInt comb(Long n, Long m) { //O(1)
	if (n < m) return 0;
	return fact[n] * inv[m] * inv[n - m]; 
}

//call init(MOD) before
ModInt combLucas(Long n, Long m) { //O(log N + log M)
	//mod is prime
	ModInt ans = 1;
	while (n > 0 || m > 0) {
		ans *= comb(n % MOD, m % MOD);
		n /= MOD;
		m /= MOD; 
	}
	return ans;
}
