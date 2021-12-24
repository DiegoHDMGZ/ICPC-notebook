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

int bitReverse(int x, int lg) {
	int ans = 0;
	for (int i = 0; i < lg; i++) {
		ans = ans * 2 + x % 2;
		x /= 2;
	}
	return ans;
}


void ntt(vector<Field> &a, const vector<Field> &wn) { //O(n log n)
	//n must be a power of 2
	int n = a.size();
	int lg = 31 - __builtin_clz(n);
	for (int i = 0; i < n; i++) {
		int target = bitReverse(i, lg);
		if (i < target) swap(a[i], a[target]);
	}
	int e = 0;
	for (int len = 2; len <= n; len *= 2) {
		for (int l = 0; l < n; l += len) {
			Field w(1);
			for (int d = 0; d < len / 2; d++) {
				Field even = a[l + d];
				Field odd = a[l + d + len / 2] * w;
				a[l + d] = even + odd;
				a[l + d + len / 2] = even - odd;
				w *= wn[e]; 
			}
		}
		e++;
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
	int lg = 31 - __builtin_clz(n);
	vector<Field> wn(lg);
	wn[lg - 1] = Field(fastPow(root , (MOD - 1) / n));
	for (int i = lg - 2; i >= 0; i--) wn[i] = wn[i + 1] * wn[i + 1];
	ntt(fa, wn);
	ntt(fb, wn);
	
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
		fa[i] /= n;
	}
	wn[lg - 1] = Field(fastPow(rootInv , (MOD - 1) / n));
	for (int i = lg - 2; i >= 0; i--) wn[i] = wn[i + 1] * wn[i + 1];
	ntt(fa, wn);
	
	polynomial ans((int)a.size() + (int)b.size() - 1);
	for (int i = 0; i < ans.size(); i++) ans[i] = fa[i].val;
	return ans;
} 

int main() {
	return 0;
}
