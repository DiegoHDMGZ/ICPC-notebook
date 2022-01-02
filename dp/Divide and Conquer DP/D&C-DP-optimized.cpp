#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Min cost array partition - Second optimization (similar to knuth's)
dp[i][k]: Min cost partition for array [0 ... i] into k subarrays
dp[i][k] = min{dp[p][k - 1] + cost(p + 1, r) , p < i}
dp[i][1] = cost(0 , i)
opt[i][k - 1] <= opt[i][k] <= opt[i + 1][k]
A sufficient condition in cost is also Quadrangle Inequality:
For all a < b < c < d
cost(a, d) - cost(b, d) >= cost(a, c) - cost(b, c)  
(For maximization is the opposite sign)
--------------------------------------------------
Ways of proving that that cost satisfy Quadrangle Inequality:
You can use induction in the following form
cost(l, r) - cost(l + 1, r) >= cost(l, r - 1) - cost(l + 1, r - 1)
Also, if cost(l, r) = f(S_l + ... + S_r) and all S_i are positive
Then we can define cost(l, r) = f(A + x), cost(l + 1 , r) = f(A)
cost(l, r - 1) = f(B + x) , cost(l + 1, r - 1) = f(B), A = B + y
Notice that x = S_l and y = S_r
So we want to prove f(A + x) - f(A) >= f(B + x) - f(B)
Even more, if f''(x) >= 0, then the last inequality is satisfied
*/

const int MX = 3000;
Long dp[MX][MX + 1];
int opt[MX][MX + 1];
Long cost(Long l, Long r) {
	return 0;
}

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

int main() {
	return 0;
}
