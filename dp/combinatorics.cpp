#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1000;
Long dp[MX][MX];
bool used[MX][MX];
Long comb(Long n , Long m) {
	if(n == m){ 
		return 1;
	}
	if(m == 0) {
		return 1;
	}
	
	if(used[n][m]) {
		return dp[n][m];
	}
	used[n][m] = true;
	return dp[n][m] = comb(n - 1 , m - 1) + comb(n - 1 , m );
}

int main() {
	return 0;
}

