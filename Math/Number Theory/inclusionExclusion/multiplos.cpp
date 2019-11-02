#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long LCM(Long a, Long b){
	return a/__gcd(a,b) * b;
}

Long getBit(Long x, Long i){
	return (x >> i) & 1LL;
}

Long multiplos(Long N , vector<Long> &v) { 
//Count the numbers of integers in [1 , N] that are multiples of at least
//one of the v[i]
	Long sz = v.size();
	Long resp = 0;
	for(Long mask = 1; mask < (1LL << sz); mask++ ) {
		Long cnt = 0;
		Long den = 1;
		for(Long i = 0; i < sz; i++){
			
			if(getBit(mask, i) == 1) {
				cnt ++;
				den = LCM(den , v[i]);
			}
		}
		
		if(cnt % 2 == 0){
			resp -= N / den;
		}
		else{
			resp += N / den;
		}
	}
	
	return resp;
}

int main() {

	return 0;
}



