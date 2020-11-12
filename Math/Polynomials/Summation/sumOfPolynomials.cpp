#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
typedef vector<Long> polynomial;

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
		if (b & 1 == 1) { 
			ans = mult(ans , a);
		}
		a = mult(a , a);
		b >>= 1; 
	}
	return ans;
}

Long modInverse(Long a) { //O(log mod) , mod prime , (a , mod) coprimes
	return fastPow(a, MOD - 2);
}

Long divide(Long a, Long b) {
	return mult(a , modInverse(b));
}

const Long MX = 5002;
Long fact[MX];
Long inv[MX];

Long stirling[MX][MX];

void precalc() {
	fact[0] = inv[0] = 1;
	for (Long i = 1; i < MX; i++) {
		fact[i] = mult(i, fact[i - 1]);
		inv[i] = modInverse(fact[i]);
	}
	
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

polynomial transformFalling(Long c, Long n) { //O(n)
	polynomial p(n + 1, 0);
	for (Long i = 0; i <= n; i++) {
		p[i] = mult(stirling[n][i], c);
	}
	return p;
}

Long falling(Long x, Long n) {
	if (n > x) return 0;
	return mult(fact[x], inv[x - n]);
}

polynomial operator +(const polynomial &A, const polynomial &B) {
	polynomial ans(max(A.size(), B.size()));
	for (Long i = 0; i < max(A.size(), B.size()); i++) {
		Long a = 0;
		if (i < A.size()) {
			a = A[i];
		}
		Long b = 0;
		if (i < B.size()) {
			b = B[i];
		}
		ans[i] = add(a, b);
	}
	return ans;
}

Long summation(polynomial &p, Long r) { //O(n^2)
	polynomial fallings;
	for (Long i = 0; i < p.size(); i++) {
		fallings = fallings + transformFalling(p[i], i);
	}
	Long ans = 0;
	for (Long i = 0; i < fallings.size(); i++) {
		Long coef = divide(fallings[i], i + 1);
		ans = add(ans, mult(coef, falling(r + 1, i + 1))) ;
	}
	return ans;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	precalc();
	Long n;
	cin >> n;
	polynomial p(n + 1);
	for (Long i = n; i >= 0; i--) {
		cin >> p[i];
	}
	while(true) {
		Long x;
		cin >> x;
		if (x < 0) break;
		cout << summation(p, x) << endl;
	}

	return 0;
}
