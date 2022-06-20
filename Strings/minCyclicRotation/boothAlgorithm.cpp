#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// Booth's Algorithm

string minRotation(string s) { // O(n)
    int n = s.size();
    string t = s + s;
    int opt = 0;
    int i = 1;
    while (i < n) {
        for (int k = 0; k < n; k++) {
            if (t[i + k] < t[opt + k]) {
                opt = i;
                break;
            }
            if (opt + k == i || t[opt + k] < t[i + k]) {
                i += max(k, 1);
                break;
            }
        }
    }
    rotate(s.begin(), s.begin() + opt, s.end());
    return s;
}
