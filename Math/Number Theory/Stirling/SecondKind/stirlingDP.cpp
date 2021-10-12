#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 1000;

Long stirling[MX][MX];

const Long MOD = 1e9 + 7;
Long add(Long a, Long b) {
	return (a + b) % MOD;
}

Long mult(Long a, Long b) {
	return (a * b) % MOD;
}

void calculate() { //O(n * k)
	stirling[0][0] = 1;
	for (Long n = 1; n < MX; n++) {
		stirling[n][0] = 0;
	}
	for (Long n = 1; n < MX; n++) {
		for (Long k = 1; k <= n; k++) {
			stirling[n][k] = add(stirling[n - 1][k - 1], mult(k , stirling[n - 1][k]));
		}
	}
}

int main() {
	return 0;
}
