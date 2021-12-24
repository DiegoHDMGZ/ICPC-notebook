#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

//String Matching with wildcards: '?' can be any character

typedef long long Long;
typedef double Double;
typedef complex<Double> Complex;

const Double PI = acos(-1);

int bitReverse(int x, int lg) {
	int ans = 0;
	for (int i = 0; i < lg; i++) {
		ans = ans * 2 + x % 2;
		x /= 2;
	}
	return ans;
}

void fft(vector<Complex> &a, bool invert) { //O(n log n)
	//n must be a power of 2
	int n = a.size();
	int lg = 31 - __builtin_clz(n);
	for (int i = 0; i < n; i++) {
		int target = bitReverse(i, lg);
		if (i < target) swap(a[i], a[target]);
	}
	int sgn = 1;
	if (invert) sgn = -1;
	for (int len = 2; len <= n; len *= 2) {
		Complex wn = polar((Double)1 , sgn * 2.0 * PI / len);
		for (int l = 0; l < n; l += len) {
			Complex w(1);
			for (int d = 0; d < len / 2; d++) {
				Complex even = a[l + d];
				Complex odd = a[l + d + len / 2] * w;
				a[l + d] = even + odd;
				a[l + d + len / 2] = even - odd;
				w *= wn; 
			}
		}
	}
}

typedef vector<Long> polynomial;

polynomial operator *(const polynomial &a, const polynomial &b) {
	vector<Complex> fa(a.begin(), a.end());
	vector<Complex> fb(b.begin(), b.end());
	Long n = 1;
	while (n < a.size() + b.size()) n <<= 1;
	fa.resize(n);
	fb.resize(n);
	
	fft(fa, false);
	fft(fb, false);
	
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
		fa[i] /= n; //inverse
	}
	fft(fa, true);
	
	polynomial ans(a.size() + b.size() - 1);
	for (int i = 0; i < ans.size(); i++) ans[i] = round(fa[i].real());
	return ans;
}

polynomial operator *(const Long &k, const polynomial &a) {
	polynomial ans(a.size());
	for (int i = 0; i < a.size(); i++) ans[i] = a[i] * k;
	return ans;
}

polynomial operator +(const polynomial &a, const polynomial &b) {
	polynomial ans(a.size());
	assert(a.size() == b.size());
	for (int i = 0; i < a.size(); i++) ans[i] = a[i] + b[i];
	return ans;
}

polynomial operator -(const polynomial &a, const polynomial &b) {
	polynomial ans(a.size());
	assert(a.size() == b.size());
	for (int i = 0; i < a.size(); i++) ans[i] = a[i] - b[i];
	return ans;
}

int toInt(char c) {
	if (c == '?') return 0;
	return c - 'a' + 1;
}

vector<int> getMatchedPositions(string &p, string &t) {
	//a[i] = int(t[i]), b[i] = int(p[i])
	//d_k = sum(a[k + i] * b[i] (a[k + i] - b[i])^2)
	//d_k = a[k + i] sum(b[i]^3) + sum(b[i] * a[k + i]^3) - 2 * sum(a[k + i]^2 * b[i]^2)
	int n = t.size();
	int m = p.size();
	if (n < m) return {};
	
	polynomial a(n), b(m) , a2(n), b2(m), a3(n), b3(m);
	for (int i = 0; i < n; i++) {
		a[i] = toInt(t[i]);
		a2[i] = a[i] * a[i];
		a3[i] = a[i] * a[i] * a[i];
	}
	for (int i = 0; i < m; i++) {
		int x = m - i - 1;
		b[x] = toInt(p[i]);
		b2[x] = b[x] * b[x];
		b3[x] = b[x] * b[x] * b[x];
	}
	polynomial d = a * b3 + b * a3 - 2 * a2 * b2;
	vector<int> ans;
	for (int k = 0; k < n - m + 1; k++) {
		if (d[k + m - 1] == 0) ans.push_back(k);
	}
	return ans;
}

int main() {
	return 0;
}
