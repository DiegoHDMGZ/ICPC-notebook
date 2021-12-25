#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
typedef vector<Long> poly;

const Long MOD = 1e9 + 7;

Long mult(Long a, Long b) {
	return (a * b ) % MOD;
}

Long add(Long a, Long b) {
	return (a + b) % MOD;
}

Long sub(Long a, Long b) {
	return (a - b + MOD) % MOD;
}

Long fastPow(Long a, Long b) { //O(logb)
	Long ans = 1;
	while (b > 0) {
		if (b & 1) ans = mult(ans , a);
		a = mult(a , a);
		b >>= 1; 
	}
	return ans;
}

Long invert(Long a) { //O(log mod) , mod prime , (a , mod) coprimes
	return fastPow(a, MOD - 2);
}

Long divide(Long a, Long b) {
	return mult(a , invert(b));
}

poly operator +(const poly &A, const poly &B) {
	poly ans(max(A.size(), B.size()));
	for (Long i = 0; i < max(A.size(), B.size()); i++) {
		Long a = 0;
		if (i < A.size()) a = A[i];
		Long b = 0;
		if (i < B.size()) b = B[i];
		ans[i] = add(a, b);
	}
	return ans;
}

const Long MX = 5002;

struct Summation {
	Long stirling[MX][MX];
	poly coef;
	
	void precalc() { //O(n^2)
		stirling[0][0] = 1;
		for (Long n = 1; n < MX; n++) {
			stirling[n][0] = 0;
		}
		for (Long n = 1; n < MX; n++) {
			for (Long k = 1; k <= n; k++) {
				stirling[n][k] = add(stirling[n - 1][k - 1] , mult(k , stirling[n - 1][k]));
			}
		}
	}
	
	Summation() {
		precalc();
	}

	poly transformFalling(Long c, Long n) { //O(n)
		poly p(n + 1, 0);
		for (Long i = 0; i <= n; i++) {
			p[i] = mult(stirling[n][i], c);
		}
		return p;
	}
	
	void build(poly &p) { //O(n^2)
		poly fallings;
		for (Long i = 0; i < p.size(); i++) {
			fallings = fallings + transformFalling(p[i], i);
		}
		coef = vector<Long>(fallings.size());
		for (Long i = 0; i < fallings.size(); i++) {
			coef[i] = divide(fallings[i], i + 1);
		}
	}

	Long query(Long x) {  //O(n)
		x %= MOD;
		Long ans = 0;
		Long fact = 1;
		Long val = x + 1;
		for (Long i = 0; i < coef.size(); i++) {
			fact = mult(fact , val);
			val--;
			ans = add(ans, mult(coef[i], fact)) ;
		}
		return ans;
	}
}summation;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	poly p(n + 1);
	for (Long i = n; i >= 0; i--) {
		cin >> p[i];
	}
	summation.build(p);
	while(true) {
		Long x;
		cin >> x;
		if (x < 0) break;
		cout << summation.query(x) << endl;
	}

	return 0;
}
