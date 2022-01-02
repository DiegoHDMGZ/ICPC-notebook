#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Array Merging DP
dp[l][r]: Min cost of merging elements in [l, r] into a single subarray
dp[l][r] = min{dp[l][m] + dp[m + 1][r] + cost(l, r) , l <= m < r}
dp[l][l + 1] = cost(l, l + 1), usually cost(l, l) = 0
opt[l][r - 1] <= opt[l][r] <= opt[l + 1][r]
A sufficient condition in cost is Quadrangle Inequality and monotonicity:
For all a < b < c < d
QI: cost(a, d) - cost(b, d) >= cost(a, c) - cost(b, c)  
(For maximization is the opposite sign)
Monotonicity: cost(b, c) <= cost(a, d)
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
Long dp[MX][MX];
int opt[MX][MX];

Long cost(Long l, Long r) {
	return 0;
}

const Long INF = 1e18;

Long minCost(int n) { //O(n^2)
	for (int l = 0; l + 1 < n; l++) {
		dp[l][l + 1] = cost(l, l + 1);
		opt[l][l + 1] = l;
	}
	for (int d = 2; d < n; d++) {
		for (int l = 0; l + d < n; l++) {
			int r = l + d;
			dp[l][r] = INF;
			for (int m = opt[l][r - 1]; m <= opt[l + 1][r]; m++) {
				Long curCost = dp[l][m] + dp[m + 1][r] + cost(l, r);
				if (curCost < dp[l][r]) {
					dp[l][r] = curCost;
					opt[l][r] = m;
				}
			}
		}
	}
	return dp[0][n - 1];
}

int main() {
	return 0;
}
