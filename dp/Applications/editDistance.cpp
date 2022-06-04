#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e3;

Long dp[MX][MX];
bool used[MX][MX];
string a, b;

Long editDistance(Long n = a.size(), Long m = b.size()) {
    if (n == 0) return m;
    if (m == 0) return n;
    if (used[n][m]) return dp[n][m];
    used[n][m] = true;
    if (a[n - 1] == b[m - 1]) {
        return dp[n][m] = editDistance(n - 1, m - 1);
    } else {
        return dp[n][m] = 1 + min({editDistance(n - 1, m - 1), editDistance(n, m - 1),
                                   editDistance(n - 1, m)});
    }
}
