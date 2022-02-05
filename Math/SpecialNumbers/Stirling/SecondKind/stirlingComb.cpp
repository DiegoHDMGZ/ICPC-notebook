#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//count the number of ways of partitioning n distinct objects into k non-empty sets.
const Long MX = 1e5;
const Long MOD = 1e9 + 7;
struct ModInt {
	Long val;
	ModInt(Long val = 0) {
		val %= MOD;
		if (val < 0) val += MOD;
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
	ModInt operator -=(const ModInt &other) {
		*this = *this - other;
		return *this;
	}
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
	ModInt operator +=(const ModInt &other) {
		*this = *this + other;
		return *this;
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

ModInt fact[MX];
ModInt inv[MX];

ModInt comb(int n, int k) {
	return fact[n] * inv[k] * inv[n - k]; 
}

ModInt stirling(Long n, Long k) { //O(k log n)
	ModInt ans = 0;
	for (int i = 0; i <= k; i++) {
		if ((i & 1) == 0) ans += ModInt(k - i).pow(n) * comb(k, i);
		else ans -= ModInt(k - i).pow(n) * comb(k, i);
		
	}
	return ans * inv[k];
}

void calculate() {
	fact[0] = inv[0] = 1;
	for (int i = 1; i < MX; i++) {
		fact[i] = fact[i - 1] * i;
	}
	inv[MX - 1] = fact[MX - 1].invert();
	for (int i = MX - 2; i >= 1; i--) {
		inv[i] = inv[i + 1] * (i + 1);
	}
}
