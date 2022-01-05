#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

// (a^x)% mod = (a^r) % mod. 
// If a, mod are coprimes
// Fermat's little theorem : r = x % (mod-1) , mod prime
// Euler's theorem : r = x % phi(mod) 

const int MOD = 1e9 + 7;
Long mult(Long a, Long b) {
	return (a * b) % MOD;
}

Long fastPow(Long a, Long b) { //O(log b)
	Long ans = 1;
	while (b > 0) {
		if (b & 1) { //b % 2 == 1
			ans = mult(ans, a);
		}
		a = mult(a, a);
		b >>= 1; //b /= 2;
	}
	return ans;
}

int main() {
	return 0;
}
