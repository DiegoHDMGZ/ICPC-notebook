#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
Long add(Long a, Long b) {
	if (a + b < MOD) return a + b;
	return a + b - MOD;
}

Long fastMult(Long a, Long b) {
	a %= MOD;
	b %= MOD;
	Long ans = 0;
	while (b > 0) {
		if (b & 1) { //b % 2 == 1
			ans = add(ans, a);
		}
		a = add(a, a);
		b >>= 1; //b /= 2
	}
	return ans;
}

int main() {
	return 0;
}


