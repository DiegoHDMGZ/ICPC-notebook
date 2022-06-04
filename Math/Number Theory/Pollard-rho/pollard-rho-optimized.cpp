#include <bits/stdc++.h>
using namespace std;

// source : https://github.com/peon-pasado/kactl/blob/master/content/number-theory/Factor.h
typedef long long Long;
typedef unsigned long long ULong;
typedef long double Double;

// Works for numbers < 2^63 and a, b < M
ULong mult(ULong a, ULong b, ULong M) {
    // a %= M
    // b %= M
    Long ret = a * b - M * ULong(Double(a) * Double(b) / Double(M));
    return ret + M * (ret < 0) - M * (ret >= (Long)M);
}

/*Long mult(__int128 a, __int128 b, Long mod) {
    //Use fastMult or 128-bit integer
    return (a * b) % mod;
}*/

Long fastPow(Long a, Long b, Long mod) { // O(log b)
    Long ans = 1;
    while (b > 0) {
        if (b & 1) ans = mult(ans, a, mod);
        a = mult(a, a, mod);
        b >>= 1;
    }
    return ans;
}

bool checkComposite(Long a, Long d, Long s, Long n) {
    // O(log n) with 128 bit
    // O(log^2 n) with divide and conquer mult
    Long x = fastPow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int i = 1; i < s; i++) {
        x = mult(x, x, n);
        if (x == n - 1) return false;
    }
    return true;
}

bool isPrime(Long n) {
    // O(log n * |base|) with 128-bit
    // O(log^2 n * |base|) with divide and conquer
    if (n <= 1) return false;
    Long d = n - 1;
    Long s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    // 64-bit integer
    vector<Long> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    // 2 3 5 7 for 32-bit integer
    for (Long a : base) {
        if (a >= n) break;
        if (checkComposite(a, d, s, n)) {
            return false;
        }
    }
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

const int BUCKET = 40;

Long getFactor(Long n) {
    if (isPrime(n)) return n;
    auto f = [n](Long x) { return mult(x, x, n) + 1; };
    // x = 0 will also work
    Long x = random(0, n - 1), y = x;
    int t = 0, i = 1;
    Long product = 2;
    while (true) {
        t++;
        if (x == y) x = ++i, y = f(x);
        Long cum = mult(abs(y - x), product, n);
        if (cum != 0) product = cum;
        x = f(x);
        y = f(f(y));
        if (t == BUCKET) {
            t = 0;
            Long ans = __gcd(product, n);
            if (ans != 1) {
                return getFactor(ans);
            }
        }
    }
}

vector<pair<Long, Long>> factorize(Long n) {
    if (n == 1) return {};
    vector<pair<Long, Long>> factors;
    while (n > 1) {
        Long f = getFactor(n);
        Long e = 0;
        while (n % f == 0) {
            n /= f;
            e++;
        }
        factors.push_back({f, e});
    }
    // sort(factors.begin(), factors.end());
    return factors;
}
