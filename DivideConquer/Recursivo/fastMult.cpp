#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

Long add(Long a, Long b, Long mod){
	a %= mod;
	b %= mod;
	return (a + b ) % mod;
}

Long fastMult(Long a, Long b, Long mod){
	if(b == 0){
		return 0;
	}
	Long ans = fastMult(a , b / 2 , mod);
	ans = add(ans , ans , mod);
	if(b % 2 == 1){
		ans = add(ans ,a , mod);
	}
	return ans;
}

int main() {
	
	cout << fastMult(81 , 75 , 157) << endl;
	return 0;
}
