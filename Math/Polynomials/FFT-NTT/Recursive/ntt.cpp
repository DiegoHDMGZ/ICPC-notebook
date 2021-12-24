#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//MOD = 2^k * c + 1
//r = primitive root of MOD
//wn = r^c

const Long MOD = 998244353; //MOD = 2^23 * 119 + 1

const Long root = 3;//primitive root of MOD
const Long rootInv = 332748118;//modular inverse of root

Long mult(Long a, Long b) {
	return (a * b) % MOD;
}

Long fastPow(Long a, Long b) { //O(log b)
	Long ans = 1;
	while (b > 0) {
		if (b & 1) ans = mult(ans, a);
		a = mult(a, a);
		b >>= 1;
	}
	return ans;
}

Long invert(Long a) {
	return fastPow(a, MOD - 2);
}

Long divide(Long a, Long b) {
	return mult(a, invert(b));
}

struct Field{
	Long val;
	Field(Long val = 0) {
		this->val = val % MOD;
	}
	
	Field operator +(const Field &F) const {
		return (val + F.val) % MOD;
	}
	
	Field operator -(const Field &F) const {
		return (val - F.val + MOD) % MOD;
	}
	
	Field operator *(const Field &F) const {
		return mult(val, F.val);
	}
	
	Field operator *=(const Field &F)  {
		val = mult(val, F.val);
		return *this;
	}
	
	Field operator /(const Field &F) const {
		return divide(val, F.val);
	}
	
	Field operator /=(const Field &F)  {
		val = divide(val, F.val);
		return *this;
	}
};

void ntt(vector<Field> &a, const Field &wn) { //O(n log n)
	//n must be a power of 2
	int n = a.size();
	if (n == 1) return;
	vector<Field> even(n / 2), odd(n / 2);
	for (int i = 0; 2 * i < n; i++) {
		even[i] = a[2 * i];
		odd[i] = a[2 * i + 1];
	}
	ntt(even, wn * wn);
	ntt(odd, wn * wn);
	Field w(1);
	for (int i = 0; 2 * i < n; i++) {
		a[i] = even[i] + w * odd[i];
		a[i + n / 2] = even[i] - w * odd[i];
		w *= wn;
	}
}

typedef vector<Long> polynomial;

polynomial operator *(const polynomial &a, const polynomial &b) {
	int n = 1;
	vector<Field> fa(a.begin(), a.end());
	vector<Field> fb(b.begin(), b.end());
	while(n < a.size() + b.size()) n <<= 1;
	fa.resize(n);
	fb.resize(n);
	
	Field wn(fastPow(root , (MOD - 1) / n));
	ntt(fa, wn);
	ntt(fb, wn);
	
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
		fa[i] /= n;
	}
	wn = Field(fastPow(rootInv , (MOD - 1) / n));
	ntt(fa, wn);
	
	polynomial ans((int)a.size() + (int)b.size() - 1);
	for (int i = 0; i < ans.size(); i++) ans[i] = fa[i].val;
	return ans;
} 

int main() {
	return 0;
}
