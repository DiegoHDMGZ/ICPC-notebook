#include <bits/stdc++.h>

using namespace std;
typedef long long Long;

const int MOD = 1e9 + 7;

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
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
	/*ModInt operator *(const ModInt &other) const {
		ModInt ans = 0;
		Long b = other.val;
		ModInt a = val;
		while (b > 0) {
			if (b & 1) {
				ans += a;
			}
			a += a;
			b >>= 1;
		}
		return ans;
	}*/
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
	
	//Exponentiation
	//(a ^ x) % mod = (a ^ r) % mod 
	//Fermat's little theorem : r = x % (mod - 1), mod prime
	//Euler's theorem : r = x % phi(mod), (a, mod coprimes)
	ModInt pow(Long b) const { //O(log b)
		ModInt ans = 1;
		ModInt a = val;
		while (b > 0) {
			if (b & 1) {
				ans *= a;
			}
			a *= a;
			b >>= 1;
		}
		return ans;
	}
	
	//Modular inverse only defined when (val, mod) are coprimes
	ModInt invert() const { //O(log mod) 
		//mod prime
		return pow(MOD - 2);
	}
	/*
	ModInt invertGcd() { //O(log(min(val, mod)))
		//(val , mod) coprimes
		Long x, y;
		//use euclid extended algorithm
		Long g = gcd(val, MOD ,x, y);
		assert(g == 1);
		if (x >= 0) return x;
		else return x + MOD;
	}*/
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
