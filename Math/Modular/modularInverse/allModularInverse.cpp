#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;

const Long MOD = 1e9;

Long mult(Long a, Long b){
	a %= MOD;
	b %= MOD;
	return (a * b ) % MOD;
}

Long subs(Long a, Long b){
	a %= MOD;
	b %= MOD;
	return (a - b + MOD) % MOD;
}

Long inv[MX];

void precalc(){
	inv[0] = 0;
	inv[1] = 1;
	for(Long i = 2; i < MOD; i++){
		inv[i] = subs(0 , mult(MOD / i , inv[MOD % i] ) );
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}
