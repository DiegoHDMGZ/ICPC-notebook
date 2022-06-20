#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// Z[i] = the maximum length of a string that is a prefix and,
// at the same time, a suffix that start at i
vector<int> zFunction(string &s) { // O(n)
    int n = s.size();
    vector<int> Z(n, 0);
    Z[0] = n;
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            Z[i] = min(Z[i - l], r - i + 1);
        }
        while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) {
            Z[i]++;
        }
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
    return Z;
}
