#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

using Long = long long;

const int MOD = 1e9 + 7;

struct ModInt {
    Long val;
    ModInt(Long val = 0) {
        if (abs(val) >= MOD) val %= MOD;
        if (val < 0) val += MOD;
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
    ModInt operator-() const {
        return MOD - val;
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

    ModInt pow(Long b) const {
        ModInt ans = 1;
        ModInt a = val;
        while (b > 0) {
            if (b & 1) ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }

    ModInt invert() const {
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

ostream &operator<<(ostream &out, const ModInt &number) {
    out << number.val;
    return out;
}

istream &operator>>(istream &in, ModInt &number) {
    in >> number.val;
    return in;
}

using poly = vector<ModInt>;

poly operator+(const poly &a, const poly &b) { // O(n)
    poly ans = a;
    ans.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) {
        ans[i] = ans[i] + b[i];
    }
    return ans;
}

poly operator-(const poly &a, const poly &b) { // O(n)
    poly ans = a;
    ans.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) {
        ans[i] = ans[i] - b[i];
    }
    return ans;
}

poly operator*(const poly &a, const poly &b) { // O(n^2)
    if (a.empty() || b.empty()) return {};
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

poly div(const poly &a, const poly &b, poly &r) { // O(n^2)
    int n = a.size();
    int m = b.size();
    poly q(max(n - m + 1, 1));
    r = a;

    for (int i = n - m; i >= 0; i--) {
        q[i] = r.back() / b.back();
        for (int j = 0; j < b.size(); j++) {
            r[i + j] -= b[j] * q[i];
        }
        r.pop_back();
    }

    return q;
}

void normalize(poly &a) {
    while (!a.empty() && a.back().val == 0) a.pop_back();
}
