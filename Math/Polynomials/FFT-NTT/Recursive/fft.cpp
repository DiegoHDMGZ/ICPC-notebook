#include <bits/stdc++.h>
using namespace std;

using Long = long long;
using Double = long double;
using Complex = complex<Double>;

const Double PI = acos(-1);

void fft(vector<Complex> &a, const Complex &wn) { // O(n log n)
    // n must be a power of 2
    int n = a.size();
    if (n == 1) return;
    vector<Complex> even(n / 2), odd(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }
    fft(even, wn * wn);
    fft(odd, wn * wn);
    Complex w(1);
    for (int i = 0; 2 * i < n; i++) {
        a[i] = even[i] + w * odd[i];
        a[i + n / 2] = even[i] - w * odd[i];
        w *= wn;
    }
}

using poly = vector<Long>;

poly operator*(const poly &a, const poly &b) { // O(n log n)
    if (a.empty() || b.empty()) return {};
    vector<Complex> fa(a.begin(), a.end());
    vector<Complex> fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    Complex wn = polar((Double)1, 2.0 * PI / n);
    fft(fa, wn);
    fft(fb, wn);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] /= n; // inverse
    }
    wn = polar((Double)1, -2.0 * PI / n); // inverse
    fft(fa, wn);

    poly ans(a.size() + b.size() - 1);
    for (int i = 0; i < ans.size(); i++) ans[i] = round(fa[i].real());
    return ans;
}