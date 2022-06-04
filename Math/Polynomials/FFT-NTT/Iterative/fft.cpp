#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;
typedef complex<Double> Complex;

const Double PI = acos(-1);

int bitReverse(int x, int lg) { // O(lg)
    int ans = 0;
    for (int i = 0; i < lg; i++) {
        ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}

void fft(vector<Complex> &a, bool invert) { // O(n log n)
    // n must be a power of 2
    int n = a.size();
    int lg = 31 - __builtin_clz(n);
    for (int i = 0; i < n; i++) {
        int target = bitReverse(i, lg);
        if (i < target) swap(a[i], a[target]);
    }
    int sgn = 1;
    if (invert) sgn = -1;
    for (int len = 2; len <= n; len *= 2) {
        Complex wn = polar((Double)1, sgn * 2.0 * PI / len);
        for (int l = 0; l < n; l += len) {
            Complex w(1);
            for (int d = 0; d < len / 2; d++) {
                Complex even = a[l + d];
                Complex odd = a[l + d + len / 2] * w;
                a[l + d] = even + odd;
                a[l + d + len / 2] = even - odd;
                w *= wn;
            }
        }
    }
}

typedef vector<Long> poly;

poly operator*(const poly &a, const poly &b) { // O(n log n)
    vector<Complex> fa(a.begin(), a.end());
    vector<Complex> fb(b.begin(), b.end());
    Long n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] /= n; // inverse
    }
    fft(fa, true);

    poly ans(a.size() + b.size() - 1);
    for (int i = 0; i < ans.size(); i++) ans[i] = round(fa[i].real());
    return ans;
}