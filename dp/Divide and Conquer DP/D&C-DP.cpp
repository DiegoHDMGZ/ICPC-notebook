#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Min array partition cost
dp[i][k]: Min cost to divide the array [0 ... i] into k subarrays
dp[i][k] = min{dp[p][k - 1] + cost(p + 1, i) , p < i}
dp[i][1] = cost(0 , i)
opt[i][k] <= opt[i + 1][k] -> Appyl D&C
A sufficient condition in cost is Quadrangle Inequality:
For all a <= b <= c <= d
cost(a, d) - cost(b, d) >= cost(a, c) - cost(b, c)  
(For maximization is the opposite sign)
--------------------------------------------------
Ways of proving that that cost satisfies Quadrangle Inequality:
It's enough to prove the following, for all l + 1 <= r - 1
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
Long cost(Long l, Long r);

const Long INF = 1e18;

void calculate(int l, int r, int k, int optL, int optR) { //O(n log n)
	if (l > r) return;
	int i = (l + r) / 2;
	dp[i][k] = INF; //change this for maximization
	int opt = optL;
	for (int p = optL; p <= min(optR, i - 1); p++) {
		Long curCost = dp[p][k - 1] + cost(p + 1, i);
		if (curCost < dp[i][k]) { //change sign for maximization
			dp[i][k] = curCost;
			opt = p;
		}
	}
	calculate(l, i - 1, k, optL, opt);
	calculate(i + 1 , r, k, opt, optR);
}

Long minCost(int n, int K) { //O(nK log n)
	for (int i = 0; i < n; i++) dp[i][1] = cost(0, i);
	K = min(K, n);
	for (int k = 2; k <= K; k++) {
		calculate(k - 1, n - 1, k, k - 2, n - 1); 
		//we will only calculate dp[i][k] for k <= i + 1
	}
	return dp[n - 1][K];
}

int main() {
	return 0;
}
