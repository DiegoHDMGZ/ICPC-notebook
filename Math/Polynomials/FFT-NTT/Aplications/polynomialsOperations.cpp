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
	
	friend ostream & operator <<(ostream &out, const Field &c);
	friend istream & operator >>(istream &in,  Field &c);
};

ostream & operator <<(ostream &out, const Field &number){
	out << number.val;
	return out;
}

istream & operator >>(istream &in, Field &number){
	in >> number.val;
	return in;
}

int bitReverse(int x, int lg) { //O(lg)
	int ans = 0;
	for (int i = 0; i < lg; i++) {
		ans = ans * 2 + x % 2;
		x /= 2;
	}
	return ans;
}

void ntt(vector<Field> &a, vector<Field> wn) { //O(n log n)
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

typedef vector<Field> poly;

poly operator +(const poly &a, const poly &b) { //O(n)
	int n = max(a.size(), b.size());
	poly ans(n);
	for (int i = 0; i < n; i++) {
		Field valA = (i < a.size()) ? a[i] : 0;
		Field valB = (i < b.size()) ? b[i] : 0;
		ans[i] = valA + valB;
	}
	return ans;
} 

poly operator -(const poly &a, const poly &b) { //O(n)
	int n = max(a.size(), b.size());
	poly ans(n);
	for (int i = 0; i < n; i++) {
		Field valA = (i < a.size()) ? a[i] : 0;
		Field valB = (i < b.size()) ? b[i] : 0;
		ans[i] = valA - valB;
	}
	return ans;
} 


poly operator *(const poly &a, const poly &b) { //O(n log n)
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
	
	poly ans((int)a.size() + (int)b.size() - 1);
	for (int i = 0; i < ans.size(); i++) ans[i] = fa[i].val;
	return ans;
} 

poly truncate(const poly &a, int n) { //O(n)
	n = min(n, (int)a.size());
	return poly(a.begin(), a.begin() + n);
}

poly getRange(const poly &a, int l, int r) { //O(r - l)
	l = min(l, (int)a.size());
	r = min(r, (int)a.size());
	return poly(a.begin() + l, a.begin() + r);
}

poly shift(const poly &a, int k) { //O(k)
	//multiply poly by x^k
	auto ans = a;
	ans.insert(ans.begin(), k, 0);
	return ans;
}

poly invert(poly &a, int n) { //O(n log n)
	assert(!a.empty() && a[0].val != 0);
	poly ans = {Field(1) / a[0]};
	int sz = 1;
	while (sz < n) {
		//ans <- ans + (ans - a * ans * ans)
		//key observation: first sz elements of a * ans will be
		//(1, 0 , ... , 0), so simplifying:
		//ans <- ans - ((a * ans)[sz...2sz - 1] * x^sz * ans)
		auto c = getRange(ans * truncate(a, 2 * sz), sz, 2 * sz);
		ans = ans - shift(truncate(ans * c, sz), sz);
		sz <<= 1;
	}
	return truncate(ans, n);
}

void normalize(poly &a) {
	while (a.size() > 1 && a.back().val == 0) a.pop_back();
}

poly operator /(const poly &a, const poly &b) { //O(n log n)
	int n = a.size();
	int m = b.size();
	if (m > n) return poly({});
	assert(b[m - 1].val != 0);
	poly aR = a;
	reverse(aR.begin(), aR.end());
	poly bR = b;
	reverse(bR.begin(), bR.end());
	poly ans = truncate(aR, n - m + 1) * invert(bR, n - m + 1);
	ans = truncate(ans, n - m + 1);
	reverse(ans.begin(), ans.end());
	normalize(ans);
	return ans;
} 

poly operator %(const poly &a, const poly &b) { //O(n log n)
	int n = a.size();
	int m = b.size();
	if (m > n) return a;
	poly ans = a - b * (a / b);
	normalize(ans);
	return ans;
}

void buildEvaluate(vector<poly> &ans, int id, int l, int r, const vector<Long> &X) {
	//O(n log^2 n)
	if (l == r) {
		ans[id] = {-X[l], 1};
	} else {
		int m = (l + r) / 2;
		int left = id + 1;
		int right = id + 2 * (m - l + 1);
		buildEvaluate(ans, left, l, m, X);
		buildEvaluate(ans, right, m + 1, r, X);
		ans[id] = ans[left] * ans[right];
	}
}

void evaluate(int id, int l, int r, const poly &a, const vector<poly> &tree, vector<Long> &ans) {
	//O(n log^2 n)
	if (l == r) {
		assert(a.size() == 1);
		ans[l] = a[0].val;
	} else {
		int m = (l + r) / 2;
		int left = id + 1;
		int right = id + 2 * (m - l + 1);
		evaluate(left, l, m, a % tree[left], tree, ans);
		evaluate(right, m + 1, r, a % tree[right], tree, ans);
	}
}

const int threshold = 30;
vector<Long> evaluate(const poly &a, const vector<Long> &X) {
	//O(n log^2 n)
	int n = X.size();
	if (n <= threshold) {
		vector<Long> ans(n);
		for (int k = 0; k < n; k++) {
			Field x = X[k];
			for (int i = (int)a.size() - 1; i >= 0; i--) {
				ans[k] = (Field(ans[k]) * x + a[i]).val;
			}
		}
		return ans;
	}
	vector<poly> tree(2 * n);
	buildEvaluate(tree, 1, 0, n - 1, X);
	vector<Long> ans(n);
	evaluate(1, 0, n - 1, a, tree, ans);
	return ans;
}

int main() {
	return 0;
}
