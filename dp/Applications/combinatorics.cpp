#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long MX = 1000;
const Long MOD = 1e9 + 7;
struct ModInt {
    Long val;
    ModInt(Long val = 0) : val(val) {}
    ModInt operator+(const ModInt &other) const {
        if (val + other.val < MOD) return val + other.val;
        return val + other.val - MOD;
    }
};

ModInt comb[MX][MX];

void init() {
    for (int n = 0; n < MX; n++) {
        comb[n][0] = 1;
        comb[n][n] = 1;
        for (int m = 1; m < n; m++) {
            comb[n][m] = comb[n - 1][m - 1] + comb[n - 1][m];
        }
    }
}
