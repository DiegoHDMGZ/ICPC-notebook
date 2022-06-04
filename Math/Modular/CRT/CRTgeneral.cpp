#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

// https://codeforces.com/blog/entry/61290
// Ec. : res[i] = x % mods[i] . We need to find x

Long normalize(Long x, Long mod) { return (x + mod) % mod; }

Long gcd(Long a, Long b, Long &x, Long &y) { // O(min(log a, log b))
    if (b == 0) {
        if (a >= 0) x = 1;
        else x = -1;
        y = 0;
        return abs(a);
    }
    Long x2, y2;
    Long g = gcd(b, a % b, x2, y2);
    x = y2;
    y = x2 - (a / b) * y2;
    return g;
}

bool CRT(pair<Long, Long> p1, pair<Long, Long> p2, pair<Long, Long> &ans) {
    if (p1.second < p2.second) swap(p1, p2);
    Long r = p1.second - p2.second;
    Long x, y;
    Long g = gcd(p1.first, p2.first, x, y);
    x *= -1;

    if (r % g != 0) return false;

    Long lcm = (p1.first / g) * p2.first;
    // a1 + d1 * k1 = a2 + d2 * k2
    // num = (a1 + x * r * d1 / g) % lcm
    // Property : (ca) % (cb) = c * (a % b)
    //=> num = (a1 + ((x * r / g) % (d2 / g)) * d1) % lcm
    Long aux = x * (r / g);
    Long den = p2.first / g;
    aux = (aux % den) * p1.first % lcm;
    aux = normalize(aux, lcm);
    aux = (aux + p1.second) % lcm;
    ans = make_pair(lcm, aux);
    return true;
}

pair<Long, Long> CRT(vector<Long> &mods, vector<Long> &res) {
    // O(|d| log LCM(d1, d2, ...))
    // answer -> (lcm , mod)
    pair<Long, Long> ans = make_pair(mods[0], res[0]);
    Long sz = mods.size();
    for (Long i = 1; i < sz; i++) {
        if (!CRT(ans, make_pair(mods[i], res[i]), ans)) {
            return {-1, -1}; // no solution
        }
    }
    return ans;
}