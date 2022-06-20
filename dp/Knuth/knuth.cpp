#include <bits/stdc++.h>
using namespace std;

using Long = long long;

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
Ways of proving that that cost satisfies Quadrangle Inequality:
(see D&C dp)
*/

const int MX = 3000;
Long dp[MX][MX];
int opt[MX][MX];

Long cost(Long l, Long r);

const Long INF = 1e18;

Long minCost(int n) { // O(n^2)
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
