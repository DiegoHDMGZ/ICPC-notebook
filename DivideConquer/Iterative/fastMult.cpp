#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

Long add(Long a, Long b, Long mod) {
	return (a + b ) % mod;
}

Long fastMult(Long a, Long b, Long mod) {
	Long ans = 0;
	while (b > 0) {
		if (b & 1 == 1) { //b % 2 == 1
			ans = add(ans ,a , mod);
		}
		a = add(a , a , mod);
		b >>= 1; //b /= 2
	}
	return ans;
}

int main() {
	return 0;
}


