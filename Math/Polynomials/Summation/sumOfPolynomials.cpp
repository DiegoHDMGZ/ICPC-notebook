#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
For a given polynomial, it computes the sum of evaluating the polynomial
from x = 0 to x = n

Usage:
summation.build(polynomial)
summation.query(n)
*/

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

typedef vector<ModInt> poly;

poly operator +(const poly &a, const poly &b) {
	poly ans(max(a.size(), b.size()), 0);
	for(int i = 0; i < ans.size(); i++){
		ans[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
	}
	return ans;
}

const Long MX = 5002;

struct Summation {
	ModInt stirling[MX][MX];
	poly coef;
	
	void precalc() { //O(|poly|^2)
		stirling[0][0] = 1;
		for (int n = 1; n < MX; n++) {
			stirling[n][0] = 0;
		}
		for (int n = 1; n < MX; n++) {
			for (int k = 1; k <= n; k++) {
				stirling[n][k] = stirling[n - 1][k - 1] + stirling[n - 1][k] * k;
			}
		}
	}
	
	Summation() {
		precalc();
	}

	poly transformFalling(ModInt c, int n) { //O(|poly|)
		poly p(n + 1, 0);
		for (Long i = 0; i <= n; i++) {
			p[i] = stirling[n][i] * c;
		}
		return p;
	}
	
	void build(poly &p) { //O(|poly|^2)
		poly fallings;
		for (int i = 0; i < p.size(); i++) {
			fallings = fallings + transformFalling(p[i], i);
		}
		coef = vector<ModInt>(fallings.size());
		for (int i = 0; i < fallings.size(); i++) {
			coef[i] = fallings[i] / (i + 1);
		}
	}

	ModInt query(Long n) {  //O(|poly|)
		ModInt ans = 0;
		ModInt fact = 1;
		Long val = n + 1;
		for (Long i = 0; i < coef.size(); i++) {
			fact *= val;
			val--;
			ans += coef[i] * fact;
		}
		return ans;
	}
}summation;
