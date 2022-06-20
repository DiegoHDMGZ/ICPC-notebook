#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// count the number of ways of partitioning n distinct objects into k non-empty sets.

const Long MOD = 1e9 + 7;
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
    ModInt operator*(const ModInt &other) const {
        return (val * other.val) % MOD;
    }
};

const Long MX = 1000;
ModInt stirling[MX][MX];

void calculate() { // O(n * k)
    stirling[0][0] = 1;
    for (int n = 1; n < MX; n++) {
        stirling[n][0] = 0;
    }
    for (int n = 1; n < MX; n++) {
        for (int k = 1; k <= n; k++) {
            stirling[n][k] = stirling[n - 1][k - 1] + stirling[n - 1][k] * k;
        }
    }
}
