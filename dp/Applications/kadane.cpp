#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long INF = 1e18;
Long kadane(vector<Long> &v){
	Long maxSoFar = -INF;
	Long maxEndingHere = 0;
	for (Long x : v ) {
		maxEndingHere = max(x, maxEndingHere + x);
		maxSoFar = max(maxSoFar, maxEndingHere);
	}
	return maxSoFar;
}

int main() {
	return 0;
}
