#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long kadane(vector<Long> &v, Long L) {
	Long n = v.size();
	vector<Long> acum(n + 1 , 0);
	for (Long i = 0; i < n; i++) {
		acum[i + 1] = acum[i] + v[i];
	}
	Long maxSoFar = acum[L];
	Long maxEndingHere = acum[L];

	for (Long i = L; i < n; i++) {
		maxEndingHere = max(acum[i + 1] - acum[i + 1 - L], maxEndingHere + v[i]);
		maxSoFar = max(maxSoFar, maxEndingHere);
	}
	return maxSoFar;
}

int main() {
	return 0;
}
