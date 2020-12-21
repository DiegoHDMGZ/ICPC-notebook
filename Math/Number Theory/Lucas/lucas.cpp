#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//Luchas Theorem :
//For non-negative integers m and n, and a prime integer p
//C(m , n) = Prod (mi, ni) (mod p)
//where mi , ni are the p-expansions of m and n respectively.

const Long MX = 100;
Long fact[MX];
Long inv[MX];

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

Long modInverse(Long a, Long m){ //O(logm) , m prime , a , m coprimes
	return fastPow(a,m-2,m);
}

void init(Long mod) { //O(mod)
	fact[0] = 1;
	inv[0] = 1;
	
	for(Long i = 1; i <= mod; i++) {
		fact[i] = (fact[i-1] * i) % mod;
		inv[i] = modInverse(fact[i] , mod);
	}
}

Long comb(Long N, Long M, Long mod) { //O(1)
	if(N < M){
		return 0;
	}
	return ( (fact[N] * inv[M]) % mod ) * inv[N-M] % mod; 
}

Long lucas(Long N, Long M, Long mod) { //O(log N + log M)
	//mod is prime
	Long resp = 1;
	while(N > 0 || M > 0) {
		resp = (resp * comb(N % mod, M % mod , mod)) % mod;
		N /= mod;
		M /= mod; 
	}
	
	return resp;
}

const Long MOD = 1e9 + 7;

int main() {
	init(MOD);
	return 0;
}
