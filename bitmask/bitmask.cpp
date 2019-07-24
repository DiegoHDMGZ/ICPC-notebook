#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

Long getBit(Long x, Long i){
	return (x >> i) & 1LL;
}

void turnOn(Long &x, Long i){
	x = x | (1LL << i);
}

void turnOff(Long &x, Long i){
	x = x & (~ (1LL << i));
}

void changeBit(Long &x, Long i){
	x = x ^ (1LL << i);
}

int main() {
	Long n = 8;

	REP(mask, (1LL<<n) ) {
		cout << mask << " : ";
		REP(i , n){
			if( getBit(mask, i) == 1) cout << " " << i;
		}
		cout << endl;
	}
	return 0;
}


