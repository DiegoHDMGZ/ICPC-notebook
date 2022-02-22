#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Min array partition cost - Second optimization (similar to knuth's)
Quadrangle Inequality in cost also guarantees the following property:
opt[i][k - 1] <= opt[i][k] <= opt[i + 1][k]
*/

const int MX = 3000;
Long dp[MX][MX + 1];
int opt[MX][MX + 1];
Long cost(Long l, Long r);

const Long INF = 1e18;

Long minCost(int n, int K) { //O(n^2)
	for (int i = 0; i < n; i++) {
		dp[i][1] = cost(0, i);
		opt[i][1] = 0;
	}
	K = min(K, n);
	for (int k = 2; k <= K; k++) {
		opt[n][k] = n - 1;
		for (int i = n - 1; i >= k - 1; i--) {
			dp[i][k] = INF; //change this for maximization
			int l = max(opt[i][k - 1], k - 2);
			int r = min(opt[i + 1][k], i - 1);
			for (int p = l; p <= r; p++) {
				Long curCost = dp[p][k - 1] + cost(p + 1, i);
				if (curCost < dp[i][k]) { //change sign for maximization
					dp[i][k] = curCost;
					opt[i][k] = p;
				}
			}
		}
	}
	return dp[n - 1][K];
}
