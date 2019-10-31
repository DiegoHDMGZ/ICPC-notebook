#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

// (a^x)% mod = (a^r) % mod. 
// If a, mod are coprimes
//Fermat's little theorem : r = x % (mod-1) , mod prime
// Euler's theorem : r = x % phi(mod) 

Long mult(Long a, Long b, Long mod){
	a %= mod;
	b %= mod;
	return (a * b ) % mod;
}

Long fastPow(Long a, Long b , Long mod){ //O(logb)
    if(b == 0) {
		return 1;
	}
    Long ans = fastPow( a , b / 2 , mod);
    ans = mult(ans , ans , mod);
    if(b % 2 == 1){
		ans = mult(ans , a , mod);
	}
	return ans;
}    

int main() {
	return 0;
}
