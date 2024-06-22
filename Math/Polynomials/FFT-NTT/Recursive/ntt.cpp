#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// MOD = 2^k * c + 1
// r = primitive root of MOD
// wn = r^((MOD - 1) / n)

const Long MOD = 998244353; // MOD = 2^23 * 119 + 1
const Long ROOT = 3;        // primitive root of MOD

struct ModInt {
    Long val;
    ModInt(Long val = 0) {
        /*if (abs(val) >= MOD) val %= MOD;
        if (val < 0) val += MOD;*/
        this->val = val;
    }
    ModInt operator+(const ModInt &other) const {
        if (val + other.val < MOD) return val + other.val;
        return val + other.val - MOD;
    }
    ModInt operator-(const ModInt &other) const {
        if (val - other.val >= 0) return val - other.val;
        return val - other.val + MOD;
    }
    ModInt operator*(const ModInt &other) const {
        return (val * other.val) % MOD;
    }
    ModInt operator*=(const ModInt &other) {
        *this = *this * other;
        return *this;
    }
    ModInt pow(Long b) const { // O(log b)
        ModInt ans = 1;
        ModInt a = val;
        while (b > 0) {
            if (b & 1) ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }
    ModInt invert() const { // O(log mod)
        // mod prime
        return pow(MOD - 2);
    }
    ModInt operator/(const ModInt &other) const {
        return *this * other.invert();
    }
    ModInt operator/=(const ModInt &other) {
        *this = *this / other;
        return *this;
    }
};

void ntt(vector<ModInt> &a, const ModInt &wn) { // O(n log n)
    // n must be a power of 2
    int n = a.size();
    if (n == 1) return;
    vector<ModInt> even(n / 2), odd(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }
    ntt(even, wn * wn);
    ntt(odd, wn * wn);
    ModInt w(1);
    for (int i = 0; 2 * i < n; i++) {
        a[i] = even[i] + w * odd[i];
        a[i + n / 2] = even[i] - w * odd[i];
        w *= wn;
    }
}

using poly = vector<ModInt>;

poly operator*(const poly &a, const poly &b) { // O(n log n)
    if (a.empty() || b.empty()) return {};
    vector<ModInt> fa(a.begin(), a.end());
    vector<ModInt> fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    ModInt wn = ModInt(ROOT).pow((MOD - 1) / n);
    ntt(fa, wn);
    ntt(fb, wn);

    ModInt nInv = ModInt(n).invert();

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] *= nInv;
    }
    wn = ModInt(ROOT).invert().pow((MOD - 1) / n);
    ntt(fa, wn);

    fa.resize(a.size() + b.size() - 1);
    return fa;
}
