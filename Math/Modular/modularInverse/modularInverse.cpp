#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;

Long mult(Long a, Long b) {
	return (a * b ) % MOD;
}

Long fastPow(Long a, Long b) { //O(logb)
	Long ans = 1;
	while (b > 0) {
		if (b & 1) { 
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
	return mult(a, modInverse(b));
}

Long gcd(Long a, Long b, Long &x, Long &y) { //O(min(loga,logb))
	if (b == 0){
		if (a >= 0) {
			x = 1;
		} else {
			x = -1;
		}
		y = 0;
		return abs(a);
	}
	Long x2, y2;
	Long g = gcd(b, a % b, x2, y2);
	x = y2;
	y = x2 - (a / b) * y2;
	return g;
}

Long modInverseGCD(Long a) { //O(min(log a,log mod))
	//a , mod coprime
	Long x, y;
	Long g = gcd(a, MOD ,x, y);
	
	if (g != 1) return -1;
	if (x >= 0) return x;
	else return x + MOD;
}

int main() {
	return 0;
}
