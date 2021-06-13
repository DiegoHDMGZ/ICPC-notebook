#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//dp[r][g] = min{dp[i][g - 1] + cost(i + 1, r) , i < r }
//dp[r][1] = cost(0 , r)
//opt[r][g] <= opt[r + 1][g] -> Appyl D&C
//Quadrangle Inequality should hold:
//For all a < b < c < d
//cost(a, d) - cost(b, d) >= cost(a, c) - cost(b, c)  
//(For maximization is the opposite sign)
//You can use induction in the following:
//cost(a, c + 1) - cost(a + 1, c + 1) >= cost(a, c) - cost(a + 1, c)
//Also, if cost(l, r) = f(S_l + ... + S_r) and all S_i are positive
//Then if f is convex (f''(x) >= 0), the quadrangle inequality holds
//Also: cost(a, c + 1) = f(A + x), cost(a + 1 , c + 1) = f(A)
//cost(a, c) = f(B + x) , cost(a + 1, c) = f(B), A = B + y
//Notice that x = S_l and y = S_r

const int MX = 3000;
Long dp[MX][MX + 1];
Long pref[MX];
Long cost(Long l, Long r) {
    return (pref[r + 1] - pref[l]) * (pref[r + 1] - pref[l]);
}

const Long INF = 1e18;

void calculate(Long l, Long r, Long g, Long optL, Long optR) {
	if (l > r) return;
	Long mid = (l + r) / 2;
	dp[mid][g] = INF;
	Long opt = optL;
	for (int i = optL; i <= min(optR, mid - 1); i++) {
		Long curCost = dp[i][g - 1] + cost(i + 1, mid);
		if (curCost < dp[mid][g]) {
			dp[mid][g] = curCost;
			opt = i;
		}
	}
	calculate(l, mid - 1, g, optL, opt);
	calculate(mid + 1 , r, g, opt, optR);
}

Long minCost(vector<Long> &S, int k) {
	int n = S.size();
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + S[i];
    }
    for (int i = 0; i < n; i++) {
        dp[i][1] = cost(0, i);
    }
    k = min(k, n);
    for (int g = 2; g <= k; g++) {
        calculate(0, n - 1, g, 0 , n - 1);
    }
    return dp[n - 1][k];
}


int main() {
    return 0;
}
