#include <bits/stdc++.h>
using namespace std;

using Long = long long;

int getBit(int mask, int pos) {
    return (mask >> pos) & 1;
}

int changeBit(int mask, int pos) {
    return mask ^ (1 << pos);
}

// dp[mask][i] = sum over submasks that can only differ in the first i bits
// dp[mask][0] = A[mask]
// dp[mask][i] = dp[mask][i - 1] , if (i - 1)-th bit off
// dp[mask][i] = dp[mask][i - 1] + dp[mask xor 2^(i - 1)], if (i - 1)-th bit is on

// if subset == false, would be sum over supersets
vector<Long> sumOverSubsets(vector<Long> &A, bool subset = true) { // O(n * 2^n)
    // A have size 2^n
    int n = __builtin_ctz(A.size());
    vector<Long> ans = A;
    if (!subset) reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (getBit(mask, i)) {
                ans[mask] += ans[changeBit(mask, i)];
            }
        }
    }
    if (!subset) reverse(ans.begin(), ans.end());
    return ans;
}
