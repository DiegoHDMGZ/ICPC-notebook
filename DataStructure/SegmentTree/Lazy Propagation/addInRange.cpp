#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct SegmentTree {
    Long t[2 * MX];
    int n;

    void clear(int n) {
        for (int i = 0; i < 2 * n; i++) {
            t[i] = 0;
        }
        this->n = n;
    }

    void build(vector<Long> &a, int id, int tl, int tr) { // O(n)
        if (tl == tr) {
            t[id] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            int left = id + 1;
            int right = id + 2 * (tm - tl + 1);
            build(a, left, tl, tm);
            build(a, right, tm + 1, tr);
            t[id] = 0;
        }
    }

    void build(vector<Long> &a) {
        n = a.size();
        build(a, 1, 0, n - 1);
    }

    Long query(int pos, int id, int tl, int tr) { // O(logn)
        if (tl == tr) return t[id];
        int tm = (tl + tr) / 2;
        int left = id + 1;
        int right = id + 2 * (tm - tl + 1);
        if (pos <= tm)
            return t[id] + query(pos, left, tl, tm);
        else
            return t[id] + query(pos, right, tm + 1, tr);
    }

    Long query(int pos) {
        assert(n > 0);
        return query(pos, 1, 0, n - 1);
    }

    void update(int l, int r, Long val, int id, int tl, int tr) { // O(logn)
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            t[id] += val;
        } else {
            int tm = (tl + tr) / 2;
            int left = id + 1;
            int right = id + 2 * (tm - tl + 1);
            update(l, r, val, left, tl, tm);
            update(l, r, val, right, tm + 1, tr);
        }
    }

    void update(int l, int r, Long val) {
        assert(n > 0);
        update(l, r, val, 1, 0, n - 1);
    }
} st;
