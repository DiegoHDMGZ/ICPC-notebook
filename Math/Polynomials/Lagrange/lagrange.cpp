#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const int MOD = 1e9 + 7;
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
    ModInt operator-() const {
        return MOD - val;
    }
    ModInt operator*(const ModInt &other) const {
        return (val * other.val) % MOD;
    }
    ModInt operator+=(const ModInt &other) {
        *this = *this + other;
        return *this;
    }
    ModInt operator-=(const ModInt &other) {
        *this = *this - other;
        return *this;
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

istream &operator>>(istream &in, ModInt &A) {
    Long val;
    in >> val;
    A = ModInt(val);
    return in;
}

ostream &operator<<(ostream &out, const ModInt &A) {
    out << A.val;
    return out;
}

using poly = vector<ModInt>;

poly operator*(const poly &a, const poly &b) {
    int n = a.size();
    int m = b.size();
    poly ans(n + m - 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i + j] += a[i] * b[j];
        }
    }
    return ans;
}

poly ruffini(poly &p, ModInt &c) { // O(n)
    // Calculates p(x) / (x - c)
    int n = p.size();
    poly ans(n - 1);
    ModInt r = 0;
    for (int i = n - 2; i >= 0; i--) {
        ans[i] = p[i + 1] + r;
        r = ans[i] * c;
    }
    return ans;
}

poly interpolate(vector<ModInt> &X, vector<ModInt> &Y) { // O(n^2)
    // get the polynomial interpolation
    int n = X.size();
    poly ans(n, 0);
    poly f = {1};
    for (int i = 0; i < n; i++) {
        f = f * poly({-X[i], 1});
    }
    for (int i = 0; i < n; i++) {
        poly cur = ruffini(f, X[i]);
        ModInt den = 1;
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            den *= X[i] - X[k];
        }
        ModInt weight = Y[i] / den;
        for (int k = 0; k < cur.size(); k++) ans[k] += weight * cur[k];
    }
    return ans;
}

ModInt interpolate(ModInt x, vector<ModInt> &X, vector<ModInt> &Y) { // O(n^2)
    // interpolate for just one value
    int n = X.size();
    ModInt y = 0;
    for (int i = 0; i < n; i++) {
        ModInt num = Y[i];
        ModInt den = 1;
        for (int k = 0; k < n; k++) {
            if (i == k) continue;
            den *= X[i] - X[k];
            num *= x - X[k];
        }
        y += num / den;
    }
    return y;
}

ModInt interpolate(ModInt x, vector<ModInt> &Y) { // O(n)
    // interpolate for just one value
    // the X vector is not given because it's assumed that you picked x_i = i (0-indexed)
    int n = Y.size();
    vector<ModInt> fact(n), factInv(n);
    vector<ModInt> pref(n), suff(n);
    fact[0] = 1;
    pref[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = fact[i - 1] * i;
        pref[i] = pref[i - 1] * (x - (i - 1));
    }
    factInv[n - 1] = fact[n - 1].invert();
    suff[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        factInv[i] = factInv[i + 1] * (i + 1);
        suff[i] = suff[i + 1] * (x - (i + 1));
    }

    ModInt y = 0;
    for (int i = 0; i < n; i++) {
        ModInt sgn = 1;
        if (i % 2 == n % 2) sgn = -1;
        y += sgn * Y[i] * pref[i] * suff[i] * factInv[i] * factInv[n - i - 1];
    }
    return y;
}
