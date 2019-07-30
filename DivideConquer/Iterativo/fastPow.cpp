#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

// (a^x)% mod = (a^r) % mod. Donde r = x % (mod-1) , mod prime

Long mult(Long a, Long b, Long mod){
	a %= mod;
	b %= mod;
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

Long fermat(Long a, Long b , Long mod){ //O(logb) 
	a = a %mod;
	
	b = b%(mod-1);
	
	return fastPow(a,b,mod);
}

int main() {
	return 0;
}


