#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
struct ModInt {
	Long val;
	ModInt(Long val = 0) {
		/*if (abs(val) >= MOD) val %= MOD;
		if (val < 0) val += MOD;*/
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
	ModInt operator -() const { return MOD - val;}
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
	ModInt operator +=(const ModInt &other) {
		*this = *this + other;
		return *this;
	}
	ModInt operator -=(const ModInt &other) {
		*this = *this - other;
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

istream & operator >> (istream &in, ModInt &A){
	Long val;
	in >> val;
	A = ModInt(val);
	return in;
}

ostream & operator << (ostream &out, const ModInt &A){
	out << A.val;
	return out;
}

typedef vector<ModInt> poly;

poly operator *(const poly &a, const poly &b) {
	int n = a.size();
	int m = b.size();
	poly ans(n + m - 1 , 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans[i + j] += a[i] * b[j];
		}
	}
	return ans;
} 

poly operator +(const poly &a, const poly &b) {
	poly ans(max(a.size(), b.size()), 0);
	for(int i = 0; i < ans.size(); i++){
		ans[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
	}
	return ans;
}

ModInt derivative(poly &p, ModInt &x) {
	if (p.size() == 1) return 0;
	ModInt ans = 0;
	ModInt cur = 1;
	for(int i = 1; i < p.size(); i++){
		ans += ModInt(i) * p[i] * cur;
		cur *= x;
	}
	return ans;
}

poly ruffini(poly &p, ModInt &c) {
	int n = p.size();
	poly ans(n - 1);
	ModInt r = 0;
	for (int i = n - 2; i >= 0; i--) {
		ans[i] = p[i + 1] + r;
		r = ans[i] * c;
	}
	return ans;
}

poly interpolate(vector<ModInt> &X, vector<ModInt> &Y){ //O(n^2)
	//get the polynomial interpolation
	poly ans(X.size(), 0);
	poly f = {1};
	for(int i = 0; i < X.size(); i++){
		f = f * poly({-X[i] , 1});
	}
	for(int i = 0; i < X.size(); i++){
		poly cur = poly({Y[i] / derivative(f, X[i])}) * f;
		cur = ruffini(cur, X[i]);
		ans = ans + cur;
	}
	return ans;
}

ModInt interpolate(ModInt x, vector<ModInt> &xSample, vector<ModInt> &ySample){ //O(n^2)
	//interpolate for just one value
	ModInt y = 0;
	for(int i = 0; i < xSample.size(); i++) {
		ModInt cur = ySample[i];
		ModInt den = 1;
		for (int j = 0; j < xSample.size(); j++) {
			if (i == j) continue;
			den *= xSample[i] - xSample[j];
			cur *= x - xSample[j];
		}
		cur /= den;
		y += cur;
	}
	return y;
}
