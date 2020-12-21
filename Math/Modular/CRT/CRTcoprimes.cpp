#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;
//Chinese Remainder Theorem (CLRS)
//Ec. : res[i] = x % mods[i] . We need to find x
//n = mods[0] * mods[1] * ... * mods[k - 1]
// mods[i] pairwise relatively prime
// Def : m[i] = n / mods[i] , c[i] = m[i] * invMod(m[i] , mods[i])
// => x = sum(res[i] * c[i]) % n + n * t , t = 0, 1 , ...

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

Long modInverseGCD(Long a, Long mod) { //O(min(log a,log mod))
	//a , mod coprime
	Long x, y;
	Long g = gcd(a, mod ,x, y);
	
	if (g != 1) return -1;
	if (x >= 0) return x;
	else return x + mod;
}

Long CRT(vector<Long> &mods, vector<Long> &res) { //O( |d| log n)
	Long n = 1;
	
	Long k = mods.size();
	for(Long i = 0; i < k; i++){
		n *= mods[i];
	}
	
	Long x = 0;
	for(Long i = 0; i < k; i++){
		Long m = n / mods[i];
		Long c = m * modInverseGCD(m , mods[i]) % n;
		Long aux = c * res[i] % n;
		x = (x + aux) % n;
	}
	return x;
}

int main() {
	return 0;
}
