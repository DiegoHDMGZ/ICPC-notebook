#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// MOD = 2^k * c + 1
// r = primitive root of MOD
// wn = r^c

const Long MOD = 998244353;     // MOD = 2^23 * 119 + 1
const Long root = 3;            // primitive root of MOD
const Long rootInv = 332748118; // modular inverse of root

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

int bitReverse(int x, int lg) { // O(lg)
    int ans = 0;
    for (int i = 0; i < lg; i++) {
        ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}

void ntt(vector<ModInt> &a, const vector<ModInt> &wn) { // O(n log n)
    // n must be a power of 2
    int n = a.size();
    int lg = 31 - __builtin_clz(n);
    for (int i = 0; i < n; i++) {
        int target = bitReverse(i, lg);
        if (i < target) swap(a[i], a[target]);
    }
    int e = 0;
    for (int len = 2; len <= n; len *= 2) {
        for (int l = 0; l < n; l += len) {
            ModInt w(1);
            for (int d = 0; d < len / 2; d++) {
                ModInt even = a[l + d];
                ModInt odd = a[l + d + len / 2] * w;
                a[l + d] = even + odd;
                a[l + d + len / 2] = even - odd;
                w *= wn[e];
            }
        }
        e++;
    }
}

using poly = vector<Long>;

poly operator*(const poly &a, const poly &b) { // O(n log n)
    if (a.empty() || b.empty()) return {};
    vector<ModInt> fa(a.begin(), a.end());
    vector<ModInt> fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    int lg = 31 - __builtin_clz(n);
    vector<ModInt> wn(lg);
    wn[lg - 1] = ModInt(root).pow((MOD - 1) / n);
    for (int i = lg - 2; i >= 0; i--) wn[i] = wn[i + 1] * wn[i + 1];
    ntt(fa, wn);
    ntt(fb, wn);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] /= n;
    }
    wn[lg - 1] = ModInt(rootInv).pow((MOD - 1) / n);
    for (int i = lg - 2; i >= 0; i--) wn[i] = wn[i + 1] * wn[i + 1];
    ntt(fa, wn);

    poly ans(a.size() + b.size() - 1);
    for (int i = 0; i < ans.size(); i++) ans[i] = fa[i].val;
    return ans;
}
