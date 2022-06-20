#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// g is a primitive root modulo n if and only if for any integer "a"
// such that gcd(a, n) = 1, there exists an integer k such that:
//(g ^ k) = a (mod n).

Long fastPow(Long a, Long b, Long mod) { // O(log b)
    Long ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        a *= a;
        a %= mod;
        b >>= 1;
    }
    return ans;
}

Long primitiveRoot(Long mod) {
    // O(ans log mod log phi(mod) + |factorization|)
    // ans = O(mod) but if mod is prime and we assume the
    // generelized Riemann hypothesis, then ans = O(log^6 p)
    Long phi = mod - 1; // phi = euler(mod) for not prime mods
    // if (mod < 1e7) we can use extended Sieve to factorize
    Long n = phi;
    Long i = 2;
    vector<Long> v;
    while (i * i <= n) {
        if (n % i == 0) {
            v.push_back(phi / i);
            while (n % i == 0) n /= i;
        }
        i++;
    }
    if (n > 1) v.push_back(phi / n);
    for (Long ans = 2; ans <= mod; ans++) {
        bool ok = true;
        for (int i = 0; i < v.size(); i++) {
            if (fastPow(ans, v[i], mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return ans;
    }
    return -1;
}
