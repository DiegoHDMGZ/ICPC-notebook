#include <bits/stdc++.h>
using namespace std;

using Long = long long;

vector<Long> prefixFunction(string &s) { // O(n)
    Long n = s.size();
    vector<Long> b(n);
    // b[i] is the lenght of the longest proper preffix in s[0...i] that is also a suffix
    for (Long i = 1; i < n; i++) {
        Long lastBorder = b[i - 1];
        while (lastBorder > 0 && s[i] != s[lastBorder]) {
            lastBorder = b[lastBorder - 1];
        }
        if (s[i] == s[lastBorder]) {
            lastBorder++;
        }
        b[i] = lastBorder;
    }
    return b;
}

vector<Long> kmp(string &p, string &t) { // O(|p| + |t|)
    // return the position where start an ocurrence of pattern p in t
    Long n = p.size();
    string s = p + "#" + t;
    vector<Long> b = prefixFunction(s);
    vector<Long> ans;
    for (Long i = 1; i < (int)s.size(); i++) {
        if (b[i] == n) {
            ans.push_back(i - (n + 1) - n + 1);
        }
    }
    return ans;
}