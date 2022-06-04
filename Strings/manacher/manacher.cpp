#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

void findPalindromes(string &s, vector<int> &d1, vector<int> &d2) {
    // d1[i] odd number of palindromes centered at i
    // d2[i] even number of palindromes centered at (i, i + 1)
    int n = s.size();
    d1 = vector<int>(n);
    d2 = vector<int>(n, 0);
    int l = -1;
    int r = -1;
    for (int i = 0; i < n; i++) {
        d1[i] = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - d1[i] >= 0 && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
            d1[i]++;
        }
        if (i + d1[i] - 1 > r) {
            r = i + d1[i] - 1;
            l = i - (d1[i] - 1);
        }
    }
    l = -1;
    r = -1;
    for (int i = 0; i < n - 1; i++) {
        d2[i] = (i >= r) ? 0 : min(d2[l + r - i - 1], r - i);
        while (i - d2[i] >= 0 && i + d2[i] + 1 < n && s[i - d2[i]] == s[i + d2[i] + 1]) {
            d2[i]++;
        }
        if (i + d2[i] > r && d2[i] > 0) {
            r = i + d2[i];
            l = i - d2[i] + 1;
        }
    }
}
