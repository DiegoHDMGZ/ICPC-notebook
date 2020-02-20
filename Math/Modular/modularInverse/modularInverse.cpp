#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long mult(Long a, Long b, Long mod){
	return (a * b ) % mod;
}

Long fastPow(Long a, Long b , Long mod){ //O(logb)
	Long ans = 1;
	while(b > 0){
		if(b & 1 == 1){ //b % 2 == 1
			ans = mult(ans ,a , mod);
		}
		a = mult(a , a  , mod);
		b >>= 1; //b /= 2;
	}
	return ans;
}

Long modInverse(Long a, Long mod){ //O(logm) , m prime , a , m coprimes
	return fastPow(a,mod - 2,mod);
}

Long gcd(Long a, Long b, Long & x, Long & y) { //O(min(loga,logb))
	if(b == 0){
		if(a >= 0) {
			x = 1;
		} else {
			x = -1;
		}
		y = 0;
		return abs(a);
	}
	Long x2, y2;
	Long g = gcd(b, a % b , x2, y2);
	x = y2;
	y = x2 - (a / b) * y2;
	return g;
}

Long modInverseGCD(Long a, Long mod){ //O(max(loga,logb))
//a , m coprime
	Long x,y;
	Long g = gcd(a, mod ,x,y);
	if(x >= 0) return x;
	else return x + mod;
}

int main() {
	Long mod = 1e9+7;
	return 0;
}
