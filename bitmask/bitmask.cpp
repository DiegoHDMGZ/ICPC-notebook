#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

int getBit(Long mask, int i){
	return (mask >> i) & 1;
}

void turnOn(Long &mask, int i){
	mask |= (1LL << i);
}

void turnOff(Long &mask, int i){
	mask &= (~(1LL << i));
}

void changeBit(Long &mask, int i){
	mask ^= (1LL << i);
}

//__builtin_popcount() : number of bits on

int main() {
	Long n = 8;

	for (Long mask = 0; mask < (1LL << n); mask++) {
		cout << mask << " : ";
		for (Long i = 0; i < n; i++) {
			if (getBit(mask, i) == 1) cout << " " << i;
		}
		cout << endl;
	}
	//transverse all submask
	for (Long mask = 0; mask < (1LL << n); mask++) {
		//s 0 is present in all submask
		for (Long s = mask; s > 0; s = (s - 1) & mask) {
			
		}
	}
	return 0;
}
