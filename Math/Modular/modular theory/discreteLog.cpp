#include <bits/stdc++.h>
using namespace std;
using Long = long long;

// Baby step - Giant Step Algorithm
Long discreteLog(Long base, Long rem, Long mod) { // O(sqrt(mod) log mod)
    // returns the smallest x such that (base ^ x) % mod = rem
    // because of Euler's theorem, x < phi(mod)
    /*base %= mod;
    rem %= mod;*/
    // Assumption: 0^0 = 1, otherwise use the following line
    // if (base == 0 && rem == 0) return 1;
    Long g = gcd(base, mod);
    Long add = 0;
    Long k = 1;
    while (g > 1) {
        if (rem == k) return add;
        if (rem % g != 0) return -1;
        rem /= g;
        mod /= g;
        add++;
        k = (k * base / g) % mod;
        g = gcd(base, mod);
    }
    // k * base ^ (x - add) % mod = rem
    Long n = (Long)sqrt(mod) + 1;
    vector<pair<Long, Long>> f1s;
    Long f1 = rem;
    for (Long q = 0; q <= n; q++) {
        f1s.push_back({f1, -q});
        f1 = (f1 * base) % mod;
    }
    sort(f1s.begin(), f1s.end());
    Long giant = 1;
    for (int i = 0; i < n; i++) giant = (giant * base) % mod;
    Long f2 = k;
    for (Long p = 1; p <= n; p++) {
        f2 = (f2 * giant) % mod;
        auto it = lower_bound(f1s.begin(), f1s.end(), make_pair(f2, -n));
        if (it != f1s.end() && it->first == f2) {
            Long q = it->second;
            return n * p + q + add;
        }
    }
    return -1;
}
