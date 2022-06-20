#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const int MX = 1e5;

struct DifferenceArray {
    Long dif[MX + 1];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            dif[i] = 0;
        }
    }

    void build(vector<Long> &v) {
        dif[0] = 0;
        for (int i = 0; i < v.size(); i++) {
            dif[i + 1] = 0;
            update(i, i, v[i]);
        }
    }

    void update(int l, int r, Long delta) { // O(1)
        // a[i] += delta
        dif[l] += delta;
        dif[r + 1] -= delta;
    }

    void update(int n) { // O(n)
        // last update before answering queries
        for (int i = 1; i < n; i++) {
            dif[i] += dif[i - 1];
        }
    }

    Long query(int pos) { // O(1)
        return dif[pos];
    }
} df;
