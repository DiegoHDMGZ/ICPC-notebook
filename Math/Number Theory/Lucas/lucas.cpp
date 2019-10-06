#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 100;
Long fact[MX];
Long inv[MX];

Long fastPow(Long a, Long b, Long c){ //O(logb)
	if(b == 0){
		return 1;
	}
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	
	return (b%2 == 0)? temp : (a%c*temp)%c;
}

Long modInverse(Long a, Long m){ //O(logm)
	//m debe ser primo
	//if(__gcd(a,m) != 1) return -1;
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



