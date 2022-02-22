#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1000;
const Long MOD = 1e9 + 7;
Long add(Long a, Long b) {
	if (a + b < MOD) return a + b;
	return a + b - MOD;
}

Long dp[MX][MX];
bool used[MX][MX];
Long comb(Long n , Long m) {
	if (n < m) return 0;
	if(n == m) return 1;
	if(m == 0) return 1;
	if(used[n][m]) return dp[n][m];
	used[n][m] = true;
	return dp[n][m] = add(comb(n - 1, m - 1), comb(n - 1, m));
}

int main() {
	return 0;
}
