#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;

//https://www.codechef.com/problems/GCDMOD

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


Long fastPow(Long a, Long b , Long mod){ //O(logb)
    if(b == 0) {
		return 1;
	}
    Long ans = fastPow( a , b / 2 , mod);
    ans = fastMult(ans , ans , mod);
    if(b % 2 == 1){
		ans = fastMult(ans , a , mod);
	}
	return ans;
}    


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	
	for(Long t = 0; t < T; t++) {
		Long A , B , N;
		cin >> A >> B >> N;
		
		Long answer = 0;
		if(A == B) {
			//(A ^ N + B ^ N ) % MOD
			answer = (fastPow(A % MOD , N , MOD) + fastPow(B % MOD, N , MOD) ) % MOD;
		} else {
			//gcd( A ^ N + B ^ N , | A - B |) = gcd(| A - B | , (A ^ N + B ^ N) % | A - B |)
			
			Long x = abs(A - B);
			Long y = (fastPow(A % x , N , x) + fastPow(B % x, N , x) ) % x;
			
			answer = __gcd(x , y) % MOD;
			
		}
		
		cout << answer << endl;
	}

	return 0;
}

