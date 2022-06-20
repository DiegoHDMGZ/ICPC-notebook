#include <bits/stdc++.h>
using namespace std;

using Long = long long;

int getBit(int mask, int i) {
    return (mask >> i) & 1;
}

Long countMultiples(Long N, vector<Long> &v) {
    // Count the numbers of integers in [1 , n]
    // that are multiples of at least one of the v[i]
    int sz = v.size();
    Long ans = 0;
    for (int mask = 1; mask < (1 << sz); mask++) {
        Long cnt = 0;
        Long den = 1;
        for (int i = 0; i < sz; i++) {
            if (getBit(mask, i) == 1) {
                cnt++;
                den = lcm(den, v[i]);
            }
        }
        if (cnt % 2 == 0) ans -= N / den;
        else ans += N / den;
    }
    return ans;
}