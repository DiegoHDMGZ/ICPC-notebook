#include <bits/stdc++.h>
using namespace std;
using Long = long long;

// Cancelation: c * a = c * b (mod n) => a = b (mod n / gcd(c, n))

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
    /*ModInt operator*(const ModInt &other) const {
        ModInt ans = 0;
        Long b = other.val;
        ModInt a = val;
        while (b > 0) {
            if (b & 1) ans += a;
            a += a;
            b >>= 1;
        }
        return ans;
    }*/

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

    // Exponentiation
    //(a ^ x) % mod = (a ^ r) % mod
    // Fermat's little theorem : r = x % (mod - 1), mod prime
    // Euler's theorem : r = x % phi(mod), (a, mod coprimes)
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

    // Modular inverse only defined when (val, mod) are coprimes
    ModInt invert() const { // O(log mod)
        // mod prime
        return pow(MOD - 2);
    }

    /*ModInt invertGcd() const { // O(log(min(val, mod)))
        //(val , mod) coprimes
        Long x, y;
        // use euclid extended algorithm
        Long g = gcd(val, MOD, x, y);
        assert(g == 1);
        if (x >= 0) return x;
        else return x + MOD;
    }*/

    ModInt operator/(const ModInt &other) const {
        return *this * other.invert();
    }
    ModInt operator/=(const ModInt &other) {
        *this = *this / other;
        return *this;
    }
    bool operator==(const ModInt &other) const {
        return val == other.val;
    }
    bool operator!=(const ModInt &other) const {
        return val != other.val;
    }
};

vector<ModInt> allInverse() { // O(MOD)
    // find the modular inverse for all numbers [1, MOD - 1]
    // MOD has to be prime
    vector<ModInt> inv(MOD);
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = inv[MOD % i] * -(MOD / i);
    }
    return inv;
}

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
